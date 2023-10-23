/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 19:17:22 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/23 09:04:44 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*join_n_free(char *s1, char *s2)
{
	char	*new;

	new = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	return (new);
}

char	*join_char(char *str, char c)
{
	char	*joined;
	int		i;

	i = 0;
	joined = (char *)ft_calloc(sizeof(char), (ft_strlen(str) + 2));
	while (str[i])
	{
		joined[i] = str[i];
		i++;
	}
	joined[i++] = c;
	joined[i] = '\0';
	return (free(str), joined);
}

char	*get_envar(char *str, int i, int j)
{
	char	*envar;
	int		k;

	envar = ft_calloc(sizeof(char), (i - j + 1));
	k = 0;
	while (j < i)
	{
		envar[k] = str[j];
		k++;
		j++;
	}
	envar[k] = '\0';
	return (envar);
}

char	*ft_getenv(char *var, t_list *env)
{
	int	len;

	if (!var)
		return (NULL);
	len = ft_strlen(var);
	while (env)
	{
		if (ft_strncmp(env->content, var, len) == 0
			&& ((char *)env->content)[len] == '=')
			return (env->content);
		env = env->next;
	}
	return (NULL);
}

char	*extract_enval(char *envar, t_list *env)
{
	char	*tmp;
	char	*enval;

	if (!envar)
		return (NULL);
	tmp = ft_getenv(envar, env);
	if (tmp)
	{
		enval = ft_strdup(tmp + ft_strlen(envar) + 1);
		return (enval);
	}
	return (NULL);
}
