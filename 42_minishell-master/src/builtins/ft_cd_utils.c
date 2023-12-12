/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 10:49:32 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/23 10:09:15 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//If "cd" receives no arguments, it will navigate to the current user's
//home directory. Otherwise, if "cd" is followed by a single or two "-", it
//will navigate to the working directory before the last time that "cd" was
//called.
static int	ft_cd_weird_args(char **args, char ***env)
{
	char	*tmp;

	tmp = NULL;
	if (mtx_len(args) == 1 || (mtx_len(args) == 2 && args[1][1] == '-' \
	&& args[1][0] == '-'))
	{
		tmp = parse_signs(ft_strdup("$HOME"), *env);
		chdir(tmp);
	}
	else if (((args[1][0] == '-') || !ft_strncmp(args[1], "--", 2)) && \
	ft_strlen(args[1]) < 2)
	{
		tmp = parse_signs(ft_strdup("$OLDPWD"), *env);
		ft_putendl_fd(tmp, STDOUT_FILENO);
		chdir(tmp);
	}
	if (tmp)
	{
		free_mtx(args);
		free(tmp);
		return (1);
	}
	return (0);
}

static int	is_valid_input(char **args, char **env)
{
	int	i;

	if (mtx_len(args) > 2)
	{
		ft_putstr_fd("MiniHell: cd: too many arguments\n", STDERR_FILENO);
		*exit_stts() = 1;
		return (1);
	}
	i = 0;
	while (env && env[i] != 0)
	{
		if (ft_strncmp(env[i], "HOME=", 5))
		{
			return (0);
		}
		i++;
	}
	ft_putstr_fd("minishell: cd: HOME not set\n", STDERR_FILENO);
	return (1);
}

int	ft_cd_checker(char **args, char ***env, char *path)
{
	if (mtx_len(args) > 2)
	{
		print_shell_err("cd", "too many arguments", NO_EXIT);
		free_mtx(args);
		return (1);
	}
	if ((is_valid_input(&args[1], *env) == 1 || getcwd(path, 1025) == NULL))
	{
		free_mtx(args);
		return (1);
	}
	if (ft_cd_weird_args(args, env))
		return (1);
	return (0);
}
