/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/08 10:28:02 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/23 09:15:15 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	skip_space(char *line, int *i)
{
	while (line[*i] == ' ' || line[*i] == '\t')
		(*i)++;
}

int	quote_check(char *line)
{
	int	i;
	int	sq;
	int	dq;

	i = 0;
	sq = 0;
	dq = 0;
	while (line && line[i])
	{
		if (line[i] == '\'' && !dq)
			sq = !sq;
		if (line[i] == '\"' && !sq)
			dq = !dq;
		i++;
	}
	if (sq || dq)
		return (1);
	return (0);
}

int	syntax_q(t_token *token, int *exit_stat)
{
	while (token)
	{
		if (quote_check(token->value))
		{
			*exit_stat = 1;
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			return (free(token->value), 1);
		}
		if (!token->next)
			break ;
		else
			token = token->next;
	}
	return (0);
}

int	ft_count1(char *line)
{
	int	count;
	int	sq;
	int	dq;

	count = 0;
	sq = 0;
	dq = 0;
	while (line && line[count])
	{
		if (line[count] == '\'' && !dq)
			sq = !sq;
		if (line[count] == '\"' && !sq)
			dq = !dq;
		if (line[count] == '|' && !sq && !dq)
			return (count);
		count++;
	}
	return (count);
}

t_token	*split_to_tokens(char *line, int *exit_stat)
{
	t_token	*t_tmp;
	int		i;
	int		j;

	i = 0;
	t_tmp = NULL;
	skip_space(line, &i);
	if (line[i] == '|')
		return (free(line), NULL);
	while (line && line[i])
	{
		j = ft_count1(line + i);
		add_back(&t_tmp, new_token(ft_substr(line, i, j)));
		i += j;
		if (line[i] == '|' && i++)
		{
			skip_space(line, &i);
			if (line[i] == '|' || !line[i])
				return (free_token(t_tmp), ft_putstr_fd(ERR, 2), NULL);
		}
	}
	if (syntax_q(t_tmp, exit_stat))
		return (free(t_tmp), NULL);
	return (t_tmp);
}
