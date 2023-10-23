/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 20:49:31 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/21 03:04:22 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_handler(int signal)
{
	(void)signal;
	if (g_signal > 0)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
	}
	else
	{
		if (g_signal == -1)
		{
			close(STDIN_FILENO);
			g_signal = -2;
		}
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
