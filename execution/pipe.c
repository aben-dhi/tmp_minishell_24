/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 16:04:10 by htouil            #+#    #+#             */
/*   Updated: 2023/10/23 07:43:00 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	wait_pid(int *exit_stat, t_token *tmp, int pid)
{
	int	sig;

	waitpid(pid, exit_stat, 0);
	while (tmp->next)
	{
		waitpid(-1, NULL, 0);
		tmp = tmp->next;
	}
	g_signal = 0;
	if (WIFSIGNALED(*exit_stat))
	{
		sig = *exit_stat >> 8;
		return (WEXITSTATUS(sig) + 128);
	}
	return (*exit_stat >> 8);
}

int	parent_proc(int *pipefd, int stdin_dup)
{
	close(pipefd[1]);
	if (stdin_dup)
		close(stdin_dup);
	stdin_dup = pipefd[0];
	return (stdin_dup);
}

int	child_proc(int *pipefd, int stdin_dup, t_token *token, t_list *env)
{
	dup2(stdin_dup, STDIN_FILENO);
	if (stdin_dup)
		close(stdin_dup);
	close(pipefd[0]);
	if (token->next)
		dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[1]);
	if (builtin_check(token->args[0]))
		exit(execute_builtin(token, &env));
	if (!ft_cmd(&token->args[0], env))
	{
		display_err(token->args[0], "command not found");
		exit(127);
	}
	exit(ft_execute(token, env));
	return (0);
}

int	piping(t_token *token, t_list *env)
{
	int		pipefd[2];
	int		stdin_dup;
	int		pid;
	int		exit_stat;
	t_token	*tmp;

	if (!token || !token->args || !*token->args)
		return (0);
	if (token->next == NULL && builtin_check(token->args[0]))
		return (execute_builtin(token, &env));
	stdin_dup = 0;
	tmp = token;
	g_signal = 1;
	while (token)
	{
		pipe(pipefd);
		pid = fork();
		if (pid == 0)
			child_proc(pipefd, stdin_dup, token, env);
		else
			stdin_dup = parent_proc(pipefd, stdin_dup);
		token = token->next;
	}
	close(stdin_dup);
	return (wait_pid(&exit_stat, tmp, pid));
}
