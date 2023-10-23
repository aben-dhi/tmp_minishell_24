/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:47:39 by htouil            #+#    #+#             */
/*   Updated: 2023/10/21 09:32:41 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_for_expand(char *str)
{
	int	i;

	if (!str)
		return (0);
	if (ft_strchr(str, '$') == 0)
		return (0);
	i = 0;
	while (str[i])
	{
		if (ft_strchr("\'\"", str[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

char	*remove_quotes(char *str)
{
	char	*tmp;

	if (!str)
		return (NULL);
	if (!ft_strchr(str, '\'') && !ft_strchr(str, '\"'))
		return (str);
	tmp = skip_quotes(str);
	free(str);
	return (tmp);
}

char	*read_heredoc_line(char *heredoc, t_list *env, int expand)
{
	char	*tmp;
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!ft_strcmp(line, heredoc) || !line || g_signal == -2)
		{
			free(line);
			break ;
		}
		if (expand && ft_strchr(line, '$'))
			line = ft_expand(NULL, line, env);
		tmp = join_n_free(tmp, line);
		tmp = join_n_free(tmp, "\n");
		if (line)
			free(line);
	}
	return (tmp);
}

char	*get_heredoc(char *heredoc, t_list *env)
{
	char	*tmp;
	int		flag;

	if (!heredoc || g_signal == -2)
		return (NULL);
	flag = 1;
	if (check_for_expand(heredoc))
		flag = 0;
	heredoc = remove_quotes(heredoc);
	tmp = read_heredoc_line(heredoc, env, flag);
	return (tmp);
}
