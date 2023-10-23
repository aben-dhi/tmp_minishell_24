/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 00:12:48 by htouil            #+#    #+#             */
/*   Updated: 2023/10/23 09:11:35 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	dup_std_fd(int *stdin_dup, int *stdout_dup)
{
	*stdin_dup = dup(STDIN_FILENO);
	*stdout_dup = dup(STDOUT_FILENO);
}

void	restore_std_fd(int stdin_dup, int stdout_dup)
{
	dup2(stdin_dup, STDIN_FILENO);
	dup2(stdout_dup, STDOUT_FILENO);
	close(stdin_dup);
	close(stdout_dup);
}

char	**ft_array(t_list *env)
{
	char	**env_arr;
	int		i;

	i = 0;
	if (!env)
		return (NULL);
	env_arr = ft_calloc(sizeof(char *), (ft_lstsize(env) + 1));
	if (!env_arr)
		return (NULL);
	while (env)
	{
		if (ft_strchr(env->content, '='))
		{
			env_arr[i] = ft_strdup(env->content);
			i++;
		}
		env = env->next;
	}
	return (env_arr);
}

int	ft_execute(t_token *token, t_list *env)
{
	char	**env_dup;
	int		exit_stat;

	exit_stat = 0;
	if (ft_redirect(token->redir_in.file, token->redir_in.type) == -1)
		return (1);
	if (ft_redirect(token->redir_out.file, token->redir_out.type) == -1)
		return (1);
	if (token->args[0])
	{
		env_dup = ft_array(env);
		exit_stat = execve(token->args[0], token->args, env_dup);
	}
	display_err(token->args[0], strerror(errno));
	exit(exit_stat);
	return (1);
}
