/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 03:51:41 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/23 08:27:44 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	search_n_modify(char *new, char *envar, t_list *tmp_list)
{
	while (tmp_list)
	{
		if (!ft_strncmp(tmp_list->content, envar, ft_strlen(envar)))
		{
			if (((char *)tmp_list->content)[ft_strlen(envar)] == '=')
			{
				free(tmp_list->content);
				tmp_list->content = new;
				return (0);
			}
			else if (((char *)tmp_list->content)[ft_strlen(envar)] == '\0')
			{
				free(tmp_list->content);
				tmp_list->content = new;
				return (0);
			}
		}
		tmp_list = tmp_list->next;
	}
	return (1);
}

int	modify_env(char *envar, char *enval, t_list *env)
{
	t_list	*e_tmp;
	char	*new;
	char	*tmp;

	if (!envar)
		return (0);
	if (!enval)
		new = ft_strdup(envar);
	else
	{
		tmp = ft_strjoin(envar, "=");
		new = ft_strjoin(tmp, enval);
		free(tmp);
	}
	if (!search_n_modify(new, envar, env))
		return (0);
	e_tmp = ft_lstnew(new);
	ft_lstadd_back(&env, e_tmp);
	return (0);
}
