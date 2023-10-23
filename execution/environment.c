/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 23:01:06 by htouil            #+#    #+#             */
/*   Updated: 2023/10/23 08:17:03 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_list	*ft_env_fill(char **env)
{
	t_list	*env_list;
	t_list	*e_tmp;
	int		i;

	if (!env)
		return (NULL);
	i = 0;
	env_list = NULL;
	while (env[i])
	{
		e_tmp = ft_lstnew(ft_strdup(env[i]));
		ft_lstadd_back(&env_list, e_tmp);
		i++;
	}
	return (env_list);
}
