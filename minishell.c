/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 16:49:31 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/23 09:23:47 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	g_signal;

char	*ft_get_line(t_list *env)
{
	char	*line;
	char	*tabless;

	line = NULL;
	tabless = NULL;
	if (!env || !env->content)
	{
		ft_putstr_fd("minishell: fatal error: ", 2);
		exit(1);
	}
	line = readline(GREY "minishell $> " CX);
	if (!line)
	{
		printf("exit\n");
		exit(0);
	}
	if (line[0] != '\0')
		add_history(line);
	tabless = ft_strtrim(line, " \t");
	if (line)
		free(line);
	return (tabless);
}

int	main(int ac, char **av, char **envp)
{
	t_token	*token;
	t_list	*env;
	int		exit_stat;
	int		pipefd[2];

	(void)ac;
	(void)av;
	exit_stat = 0;
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);
	env = ft_env_fill(envp);
	while (1)
	{
		g_signal = 0;
		dup_std_fd(&pipefd[0], &pipefd[1]);
		token = ft_parse(&exit_stat, ft_get_line(env), env);
		if (g_signal == 0 && exit_stat == 0)
			exit_stat = piping(token, env);
		restore_std_fd(pipefd[0], pipefd[1]);
		if (token)
			free_token_all(token);
	}
	ft_lstclear(&env, free);
	return (0);
}
