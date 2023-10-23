/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 00:40:08 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/23 09:20:09 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	skip_spaces(char *line, int i)
{
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
}

char	*ft_next(char *token)
{
	int	i;
	int	sq;
	int	dq;

	i = 0;
	sq = 0;
	dq = 0;
	while (token[i] && (!ft_strchr("\t |<>", token[i]) || sq || dq))
	{
		if (token[i] == '\'' && !dq)
			sq = !sq;
		else if (token[i] == '\"' && !sq)
			dq = !dq;
		i++;
	}
	return (token + i);
}

int	ft_count2(char	*token)
{
	int	count;

	count = 0;
	while (*token)
	{
		if (!ft_strchr("\t |<>", token[0]))
		{
			count++;
			token = ft_next(token);
		}
		else if (ft_strchr("><", token[0]))
		{
			while (ft_strchr("><", token[0]))
				token++;
		}
		else
			token++;
	}
	return (count);
}

int	get_file(char *line, t_token *token, t_redir_spec type, t_list *env)
{
	char	*file;
	int		i;

	i = 0;
	if (type == NONE)
		return (0);
	if ((type == REDIR_OUT || type == APPEND) && token->redir_out.file)
		free(token->redir_out.file);
	else if ((type == REDIR_IN || type == HEREDOC) && token->redir_in.file)
		free(token->redir_in.file);
	file = ft_substr(line, 0, ft_strlen(line) - ft_strlen(ft_next(line)));
	if (type == REDIR_OUT || type == APPEND)
	{
		token->redir_out.file = skip_quotes(file);
		i = open_redir_fd(token->redir_out.file, type);
	}
	else if (type == REDIR_IN)
	{
		token->redir_in.file = skip_quotes(file);
		i = open_redir_fd(token->redir_in.file, type);
	}
	else if (type == HEREDOC)
		token->redir_in.file = get_heredoc(file, env);
	free(file);
	return (i);
}

t_redir_spec	redirect_spec(char	*line)
{
	int				i;
	t_redir_spec	type;

	i = 0;
	type = NONE;
	while (line[i])
	{
		if (line[i] == '>')
			return (check_outfile(line, i));
		if (line[i] == '<')
			return (check_infile(line, i));
		i++;
	}
	return (type);
}
