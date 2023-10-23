/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:24:00 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/23 08:45:55 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	display_err(char *file, char *err)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(err, 2);
	ft_putstr_fd("\n", 2);
}

void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_token_all(t_token *token)
{
	while (token)
	{
		if (token->value)
			free(token->value);
		if (token->args)
			free_arr(token->args);
		if (token->redir_in.file)
			free(token->redir_in.file);
		if (token->redir_out.file)
			free(token->redir_out.file);
		free(token);
		token = token->next;
	}
}
