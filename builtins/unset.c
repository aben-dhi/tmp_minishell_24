/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:29:33 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/23 08:23:52 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_if_envar_exist(char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (1);
	while (str[i])
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	cmp_envar(char *str1, char *str2)
{
	int	len;

	len = ft_strlen(str2);
	if (!ft_strncmp(str1, str2, len))
	{
		if (str1[len] == '=' || !str1[len])
			return (0);
	}
	return (1);
}

int	remove_from_env(void *data_ref, t_list **env, int (*cmp)())
{
	t_list	*e_tmp;
	t_list	*prev;

	e_tmp = *env;
	prev = NULL;
	while (e_tmp)
	{
		if (!cmp(e_tmp->content, data_ref))
		{
			if (!prev)
				*env = e_tmp->next;
			else
			{
				prev->next = e_tmp->next;
				ft_lstdelone(e_tmp, free);
			}
			return (1);
		}
		prev = e_tmp;
		e_tmp = e_tmp->next;
	}
	return (0);
}

int	execute_unset(char **arg, t_list **env)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (check_if_envar_exist(arg[i]))
			display_err("unset", "not a valid identifier");
		else
			remove_from_env(arg[i], env, cmp_envar);
		i++;
	}
	return (0);
}
