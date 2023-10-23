/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:33:48 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/23 04:32:03 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	execute_echo(char **args)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (args[i] && !ft_strcmp(args[i], "-n"))
	{
		i++;
		flag = 1;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		i++;
		if (args[i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (flag == 0)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
