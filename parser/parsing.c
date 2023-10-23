/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 19:46:48 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/23 04:40:28 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	expand(int *exit_stat, t_token **res, char **line, t_list *env)
{
	char	*t_tmp;
	int		flag;

	flag = 0;
	if (ft_strchr(*line, '$') && !ft_strchr(*line, '\''))
	{
		t_tmp = ft_expand(exit_stat, *line, env);
		*line = t_tmp;
		flag = 1;
	}
	*exit_stat = 0;
	*res = split_to_tokens(*line, exit_stat);
	if (*res)
		flag = 1;
	return (flag);
}

t_token	*ft_parse(int *exit_stat, char *line, t_list *env)
{
	t_token	*res;
	t_token	*t_tmp;

	g_signal = -1;
	if (!line || line[0] == '\0')
		return (NULL);
	res = NULL;
	if (!*exit_stat && !expand(exit_stat, &res, &line, env))
		ft_putstr_fd(ERR, 2);
	t_tmp = res;
	while (t_tmp)
	{
		init_tokens(t_tmp);
		*exit_stat = lexing(t_tmp, env);
		t_tmp = t_tmp->next;
	}
	if (g_signal == -1)
		g_signal = 0;
	return (free(line), res);
}
