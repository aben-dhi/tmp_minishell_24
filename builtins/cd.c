/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-dhi <aben-dhi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 16:32:42 by aben-dhi          #+#    #+#             */
/*   Updated: 2023/10/23 04:26:30 by aben-dhi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cd_to_home(char *old_pwd, t_list *env)
{
	char	*home_path;

	if (chdir(ft_getenv("HOME", env) + 5) == -1)
	{
		display_err("cd", strerror(errno));
		return (free(old_pwd), 1);
	}
	home_path = getcwd(NULL, 0);
	modify_env("OLDPWD", old_pwd, env);
	modify_env("PWD", home_path, env);
	return (free(home_path), 0);
}

int	cd_to_old_pwd(char *oldpwd, t_list *env)
{
	if (!oldpwd)
	{
		display_err("cd", "OLDPWD not set");
		return (1);
	}
	else if (chdir(oldpwd) == -1)
	{
		display_err("cd", strerror(errno));
		return (1);
	}
	modify_env("OLDPWD", oldpwd, env);
	modify_env("PWD", oldpwd, env);
	return (0);
}

int	cd_to_path(char *args, char *old_pwd, t_list *env)
{
	char	*pwd;

	if (chdir(args) == -1)
	{
		display_err("cd", strerror(errno));
		return (free(old_pwd), 1);
	}
	pwd = getcwd(NULL, 0);
	modify_env("OLDPWD", old_pwd, env);
	modify_env("PWD", pwd, env);
	return (free(pwd), 0);
}

int	execute_cd(char **arg, t_list *env)
{
	char	*old_pwd;

	if (!arg)
		return (1);
	old_pwd = getcwd(NULL, 0);
	if (arg[2])
		return (free(old_pwd), 0);
	else if (!arg[1] || !ft_strncmp(arg[1], "~", 1))
	{
		if (cd_to_home(old_pwd, env))
			return (1);
	}
	else if (!ft_strncmp(arg[1], "-", 1))
	{
		if (cd_to_old_pwd(ft_getenv("OLDPWD", env) + 7, env))
			return (1);
	}
	else
		if (cd_to_path(arg[1], old_pwd, env))
			return (1);
	return (free(old_pwd), 0);
}
