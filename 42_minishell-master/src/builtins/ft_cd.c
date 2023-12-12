/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:38:35 by jferreir          #+#    #+#             */
/*   Updated: 2023/10/24 13:17:04 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	print_cd_error(char **args)
{
	if (access(args[1], F_OK == -1))
	{
		ft_putstr_fd(SHELL ": cd: `", STDERR_FILENO);
		ft_putstr_fd(args[1], STDERR_FILENO);
		ft_putstr_fd("': No such file or directory\n", STDERR_FILENO);
		free_mtx(args);
		return (1);
	}
	ft_putstr_fd(SHELL ": cd: `", STDERR_FILENO);
	ft_putstr_fd(args[1], STDERR_FILENO);
	ft_putstr_fd("': Not a directory\n", STDERR_FILENO);
	free_mtx(args);
	return (1);
}

int	set_oldpwd(char ***env, char *path)
{
	int	i;

	i = 0;
	while ((*env)[i] != NULL)
	{
		if (!ft_strncmp((*env)[i], "OLDPWD=", 7))
		{
			free((*env)[i]);
			(*env)[i] = ft_strjoin("OLDPWD=", path);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	set_updpwd(char ***env, char *path)
{
	int	i;

	i = 0;
	while ((*env)[i] != NULL)
	{
		if (!ft_strncmp((*env)[i], "PWD=", 4))
		{
			free((*env)[i]);
			(*env)[i] = ft_strjoin("PWD=", path);
			return (1);
		}
		i++;
	}
	return (1);
}

int	ft_cd(char **args, char ***env)
{
	char	path[1025];

	if (ft_cd_checker(args, env, path))
		return (1);
	if (chdir(args[1]) == -1)
	{
		*exit_stts() = 1;
		return (print_cd_error(args));
	}
	if (!set_oldpwd(env, path) || getcwd(path, 1025) == NULL)
	{
		free_mtx(args);
		return (1);
	}
	free_mtx(args);
	return (set_updpwd(env, path));
}
