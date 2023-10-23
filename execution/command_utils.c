/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 07:28:28 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/23 08:46:51 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_absolute_path(char **token)
{
	DIR	*dir;

	dir = opendir(*token);
	if (dir)
	{
		display_err(*token, "is a directory");
		closedir(dir);
		exit(126);
	}
	if (!access(*token, F_OK))
	{
		if (!access(*token, X_OK))
			return (*token);
		display_err(*token, strerror(errno));
		exit(126);
	}
	else
	{
		display_err(*token, strerror(errno));
		exit(127);
	}
	return (NULL);
}

char	*find_path(char **token, char **paths_list)
{
	char	*tmp;

	while (*paths_list)
	{
		tmp = ft_strjoin(*paths_list, "/");
		tmp = join_n_free(tmp, *token);
		if (!access(tmp, F_OK))
		{
			if (!access(tmp, X_OK))
			{
				free(*token);
				*token = tmp;
				return (tmp);
			}
		}
		free(tmp);
		paths_list++;
	}
	return (NULL);
}

char	*ft_cmd(char **token, t_list *env)
{
	char	*path;
	char	**paths_list;

	if (!*token || !token)
		return (NULL);
	if (**token == '/' || **token == '.')
		return (get_absolute_path(token));
	path = extract_enval("PATH", env);
	if (!path)
		return (NULL);
	paths_list = ft_split(path, ':');
	free(path);
	path = find_path(token, paths_list);
	free_arr(paths_list);
	return (path);
}
