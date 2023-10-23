/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_builtins.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 20:02:55 by htouil            #+#    #+#             */
/*   Updated: 2023/10/23 09:06:52 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_redir(t_token *token, int *in, int *out)
{
	dup_std_fd(in, out);
	if (ft_redir(token->redir_in.file, token->redir_in.type) == -1)
		return (1);
	if (ft_redir(token->redir_out.file, token->redir_out.type) == -1)
		return (1);
	return (0);
}

int	builtin_check(char *cmd)
{
	if (!ft_strcmp(cmd, "env"))
		return (1);
	else if (!ft_strcmp(cmd, "pwd"))
		return (1);
	else if (!ft_strcmp(cmd, "cd"))
		return (1);
	else if (!ft_strcmp(cmd, "echo"))
		return (1);
	else if (!ft_strcmp(cmd, "export"))
		return (1);
	else if (!ft_strcmp(cmd, "unset"))
		return (1);
	else if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

int	execute_builtin(t_token *token, t_list **env)
{
	int	stdin_dup;
	int	stdout_dup;
	int	exit_stat;

	exit_stat = 0;
	if (execute_redir(token, &stdin_dup, &stdout_dup))
		return (-1);
	else if (!ft_strcmp(token->args[0], "env"))
		exit_stat = execute_env(*env);
	else if (!ft_strcmp(token->args[0], "pwd"))
		exit_stat = execute_pwd();
	else if (!ft_strcmp(token->args[0], "cd"))
		exit_stat = execute_cd(token->args, *env);
	if (!ft_strcmp(token->args[0], "echo"))
		exit_stat = execute_echo(token->args);
	else if (!ft_strcmp(token->args[0], "export"))
		exit_stat = execute_export(token->args, *env);
	else if (!ft_strcmp(token->args[0], "unset"))
		exit_stat = execute_unset(token->args, env);
	else if (!ft_strcmp(token->args[0], "exit"))
		exit_stat = execute_exit(token->args);
	else
		exit_stat = 127;
	restore_std_fd(stdin_dup, stdout_dup);
	return (exit_stat);
}
