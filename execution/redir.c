/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 00:06:21 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/23 08:46:17 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_input(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY, 0644);
	if (fd > -1)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else
		close(STDIN_FILENO);
	return (0);
}

int	ft_output(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd > -1)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else
		close(STDOUT_FILENO);
	return (0);
}

int	ft_append(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd > -1)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else
		close(STDOUT_FILENO);
	return (0);
}

int	ft_heredoc(char *file)
{
	int	fd;
	int	pipefd[2];

	pipe(pipefd);
	write(pipefd[1], file, ft_strlen(file));
	close(pipefd[1]);
	fd = pipefd[0];
	if (fd >= 0)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else
		close(STDIN_FILENO);
	return (fd);
}

int	ft_redirect(char *file, t_redir_spec type)
{
	if (type == REDIR_IN)
		return (ft_input(file));
	else if (type == REDIR_OUT)
		return (ft_output(file));
	else if (type == APPEND)
		return (ft_append(file));
	else if (type == HEREDOC)
		return (ft_heredoc(file));
	else if (type == NONE)
		return (0);
	return (-1);
}
