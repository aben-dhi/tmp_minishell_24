/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:33:48 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/23 08:23:52 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	display_export(t_list *env)
{
	t_list	*e_tmp;
	int		len;

	e_tmp = env;
	while (e_tmp)
	{
		ft_putstr_fd("declare -x ", 1);
		if (ft_strchr(e_tmp->content, '='))
		{
			len = ft_strchr(e_tmp->content, '=') - (char *)e_tmp->content + 1;
			write(1, e_tmp->content, len);
			ft_putstr_fd("\"", 1);
			ft_putstr_fd(ft_strchr(e_tmp->content, '=') + 1, 1);
			ft_putstr_fd("\"", 1);
		}
		else
			ft_putstr_fd(e_tmp->content, 1);
		ft_putstr_fd("\n", 1);
		e_tmp = e_tmp->next;
	}
	return (0);
}

int	check_envar_syntax(char *envar)
{
	int	i;

	if (!envar)
		return (1);
	i = 0;
	if (!ft_isalpha(envar[i]) && envar[i] != '_')
		return (1);
	while (envar[i] && envar[i] != '=')
	{
		if (!ft_isalnum(envar[i]) && envar[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	export_envar(char *arg, t_list *env)
{
	char	*new_envar;
	char	*new_enval;

	new_envar = ft_substr(arg, 0, ft_strchr(arg, '=') - arg);
	new_enval = ft_substr(arg, ft_strchr(arg, '=') - arg + 1, ft_strlen(arg));
	modify_env(new_envar, new_enval, env);
	free(new_envar);
	free(new_enval);
	return (0);
}

int	execute_export(char **args, t_list *env)
{
	int		i;

	i = 1;
	if (!args[1])
		return (display_export(env));
	while (args[i])
	{
		if (check_envar_syntax(args[i]))
		{
			display_err("export", "not a valid identifier");
			return (1);
		}
		if (ft_strchr(args[i], '='))
			export_envar(args[i], env);
		else
			modify_env(args[i], NULL, env);
		i++;
	}
	return (0);
}
