/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/30 20:17:02 by htouil            #+#    #+#             */
/*   Updated: 2023/10/23 08:23:52 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isnum(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	if (str[i] && ft_strchr("-+", str[i]))
		i++;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

int	execute_exit(char **arg)
{
	int	num;

	if (!arg[1])
		exit(0);
	if (arg[1] && arg[2])
	{
		display_err("exit", "too many arguments");
		return (1);
	}
	if (ft_isnum(arg[1]))
	{
		display_err (arg[0], "numeric argument required");
		exit(255);
	}
	if (arg[1])
	{
		num = ft_atoi(arg[1]);
		exit(num);
	}
	return (0);
}
