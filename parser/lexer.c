/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 00:06:21 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/23 09:21:05 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	outfile(char **tmp, t_token *token, t_list *env, int *count)
{
	char	*str;

	str = *tmp;
	token->redir_out.type = redirect_spec(str);
	if (token->redir_out.type == ERROR)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
		return (1);
	}
	while (ft_strchr(" \t<>", *str))
		str++;
	if (get_file(str, token, token->redir_out.type, env) == -1)
	{
		display_err(token->redir_out.file, strerror(errno));
		return (1);
	}
	*tmp = str;
	(*count)--;
	return (0);
}

int	infile(char **tmp, t_token *token, t_list *env, int *count)
{
	char	*str;

	str = *tmp;
	token->redir_in.type = redirect_spec(str);
	if (token->redir_in.type == ERROR)
	{
		ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
		return (1);
	}
	while (ft_strchr(" \t<>", *str))
		str++;
	if (get_file(str, token, token->redir_in.type, env) == -1)
	{
		display_err(token->redir_in.file, strerror(errno));
		return (1);
	}
	*tmp = str;
	(*count)--;
	return (0);
}

char	*ft_clean(char *token, int *count)
{
	char	*str;
	char	*res;

	str = NULL;
	str = ft_substr(token, 0, (ft_strlen(token) - ft_strlen(ft_next(token))));
	res = skip_quotes(str);
	(*count)--;
	free(str);
	return (res);
}

int	lexing(t_token *token, t_list *env)
{
	int		count;
	char	*tmp;
	int		i;

	i = 0;
	count = ft_count2(token->value);
	token->args = ft_calloc(count + 1, sizeof(char *));
	tmp = token->value;
	while (count)
	{
		tmp += skip_spaces(tmp, 0);
		if (ft_strchr("><", *tmp))
		{
			if (((*tmp == '>' && outfile(&tmp, token, env, &count))
					|| (*tmp == '<' && infile(&tmp, token, env, &count))))
				return (1);
		}
		else
			token->args[i++] = ft_clean(tmp, &count);
		tmp = ft_next(tmp);
	}
	return (0);
}
