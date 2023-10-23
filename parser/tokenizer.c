/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 23:30:43 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/21 07:04:16 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_token	*add_back(t_token **token, t_token *new)
{
	t_token	*tmp;

	if (!new)
		return (NULL);
	if (!*token)
	{
		*token = new;
		return (*token);
	}
	tmp = *token;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	return (*token);
}

t_token	*free_token(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		free(token->value);
		free(token);
		token = tmp;
	}
	return (NULL);
}

t_token	*new_token(char *token)
{
	t_token	*new;

	new = (t_token *)malloc(sizeof(t_token));
	if (!new)
		return (NULL);
	new->value = token;
	new->next = NULL;
	return (new);
}

void	init_tokens(t_token *token)
{
	token->args = NULL;
	token->redir_in.file = NULL;
	token->redir_out.file = NULL;
	token->redir_in.type = NONE;
	token->redir_out.type = NONE;
}
