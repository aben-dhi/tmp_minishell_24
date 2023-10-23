/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 00:06:21 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/23 03:15:28 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redir_output(char *file)
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
	return (fd);
}

int	redir_input(char *file)
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
	return (fd);
}

int	redir_append(char *file)
{
	int	fd ;

	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd > -1)
	{
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	else
		close(STDOUT_FILENO);
	return (fd);
}

int	redir_heredoc(char *heredoc)
{
	int	pipefd[2];
	int	fd;

	pipe(pipefd);
	write(pipefd[1], heredoc, ft_strlen(heredoc));
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

int	ft_redir(char *file, t_redir_spec type)
{
	if (type == REDIR_OUT)
		return (redir_output(file));
	else if (type == REDIR_IN)
		return (redir_input(file));
	else if (type == APPEND)
		return (redir_append(file));
	else if (type == HEREDOC)
		return (redir_heredoc(file));
	else if (type == NONE)
		return (0);
	return (-1);
}
