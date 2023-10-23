/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 08:28:44 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/21 09:13:20 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*skip_quotes(char *token)
{
	int		i;
	int		dq;
	int		sq;
	char	*res;

	i = 0;
	dq = 0;
	sq = 0;
	res = ft_calloc(ft_strlen(token) + 1, sizeof(char));
	if (!token)
		return (NULL);
	while (token[i])
	{
		if (token[i] == '\'' && !dq)
			sq = !sq;
		else if (token[i] == '\"' && !sq)
			dq = !dq;
		else
			res = join_char(res, token[i]);
		i++;
	}
	return (res);
}
