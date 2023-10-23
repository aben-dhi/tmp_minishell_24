/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 00:06:21 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/21 09:31:09 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_redir_spec	check_outfile(char *str, int i)
{
	t_redir_spec	type;

	type = REDIR_OUT;
	i++;
	if (!str[i] || str[i++] == '>')
		type = APPEND;
	i = skip_spaces(str, i);
	if (!str[i] || ft_strchr(" \t|<>", str[i]) != 0)
		type = ERROR;
	return (type);
}

t_redir_spec	check_infile(char *str, int i)
{
	t_redir_spec	type;

	type = REDIR_IN;
	i++;
	if (!str[i] || str[i++] == '<')
		type = HEREDOC;
	i = skip_spaces(str, i);
	if (!str[i] || ft_strchr(" \t|<>", str[i]) != 0)
		type = ERROR;
	return (type);
}

int	open_redir_fd(char *file, t_redir_spec type)
{
	int	fd;

	fd = 0;
	if (type == REDIR_OUT)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (type == APPEND)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else if (type == REDIR_IN)
		fd = open(file, O_RDONLY);
	if (fd != -1 && type != HEREDOC)
		close(fd);
	return (fd);
}
