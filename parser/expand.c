/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 15:47:39 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/23 08:58:55 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_for_heredoc(int *exit_stat, char *str, int i)
{
	if (!str || !exit_stat)
		return (0);
	if (i > 0 && str[i] == '$')
		i--;
	while (i > 0 && ft_strchr(" \t", str[i]))
		i--;
	if (i > 0 && str[i] == '<' && str[i - 1] == '<')
		return (1);
	return (0);
}

int	expand_status(int *exit_stat, char **value_str, char c, int *i)
{
	char	*val;

	if (c != '?')
		return (1);
	val = ft_itoa(*exit_stat);
	*value_str = join_n_free(*value_str, val);
	*i += 2;
	return (free(val), 0);
}

int	expand_value(char *str, char **value_str, int i, t_list *env)
{
	char	*envar;
	char	*enval;
	int		j;

	i++;
	j = i;
	while (str[i] && str[i] != ' ' && str[i] != '\"' && str[i] != '$'
		&& str[i] != '\'' && str[i] != '\\' && str[i] != '\n')
		i++;
	envar = get_envar(str, i, j);
	enval = extract_enval(envar, env);
	if (!enval)
		enval = strdup("");
	*value_str = join_n_free(*value_str, enval);
	free(envar);
	free(enval);
	return (i);
}

char	*ft_expand(int *exit_stat, char *str, t_list *env)
{
	char	*value_str;
	int		i;

	if (!str || !env || !ft_strchr(str, '$'))
		return (NULL);
	i = 0;
	value_str = ft_strdup("");
	while (str[i])
	{
		if (str[i] == '$' && ft_strchr("\t $\'\"'\n'", str[i + 1])
			&& check_for_heredoc(exit_stat, str, i) == 0)
		{
			if (expand_status(exit_stat, &value_str, str[i + 1], &i))
				continue ;
			i = expand_value(str, &value_str, i, env);
		}
		else
		{
			value_str = join_char(value_str, str[i]);
			i++;
		}
	}
	return (free(str), value_str);
}
