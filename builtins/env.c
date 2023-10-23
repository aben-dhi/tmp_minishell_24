/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:19:59 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/23 06:18:54 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_env(t_list *env)
{
	t_list	*e_tmp;

	e_tmp = env;
	while (e_tmp)
	{
		if (ft_strchr(e_tmp->content, '='))
			ft_putendl_fd(e_tmp->content, 1);
		e_tmp = e_tmp->next;
	}
	return (0);
}
