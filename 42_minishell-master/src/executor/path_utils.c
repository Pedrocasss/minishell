/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:39:09 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/25 11:35:49 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_valid_path(char *cmd, char *path)
{
	struct stat	buf;

	if (lstat(path, &buf) == 0)
	{
		if (S_ISDIR(buf.st_mode))
			print_shell_err(cmd, "command not found", 127);
		else if (access(path, X_OK) == 0)
			return (1);
	}
	free(path);
	return (0);
}

static char	*get_abs_path(char *cmd)
{
	DIR	*dir;

	dir = opendir(cmd);
	if (dir)
	{
		closedir(dir);
		print_shell_err(cmd, "Is a directory", 126);
	}
	else if (access(cmd, X_OK) < 0)
		print_shell_err(cmd, "command not found", 127);
	return (cmd);
}

static char	*join_rel_path(char *cmd, char **path, char *tmp)
{
	int	p;

	p = 0;
	while (path[p])
	{
		tmp = ft_strjoin(path[p++], cmd);
		if (is_valid_path(cmd, tmp))
		{
			free_mtx(path);
			return (tmp);
		}
	}
	free_mtx(path);
	p = 0;
	while (cmd[p])
		if (cmd[p++] == '/')
			print_shell_err(cmd, "No such file or directory", 126);
	return (NULL);
}

static char	*get_rel_path(char *cmd, char **env)
{
	char	*tmp;
	char	*pwd;
	char	*cwd;

	tmp = NULL;
	if (cmd[0] && cmd[0] == '.')
	{
		cwd = getcwd(NULL, 0);
		pwd = ft_strjoin(cwd, "/");
		free(cwd);
		tmp = ft_strjoin(pwd, cmd);
		if (is_valid_path(cmd, tmp))
		{
			free_mtx(env);
			return (tmp);
		}
	}
	if (!env)
		print_shell_err(cmd, "path is unset", 127);
	return (join_rel_path(cmd, env, tmp));
}

char	*get_cmd_path(char *cmd, char **env)
{
	if (!cmd)
		return (NULL);
	else if (ft_strlen(cmd) == 1 && cmd[0] == '.')
	{
		ft_putstr_fd(SHELL, STDERR_FILENO);
		ft_putendl_fd(": filename argument required", STDERR_FILENO);
		ft_putendl_fd(".: usage: . filename [arguments]", STDERR_FILENO);
		*exit_stts() = 126;
		exit(*exit_stts());
	}
	else if (ft_strlen(cmd) == 2 && cmd[0] == '.' && cmd[1] == '.')
		print_shell_err(cmd, "command not found", 127);
	if (cmd[0] == '/')
		return (get_abs_path(cmd));
	else
		return (get_rel_path(cmd, get_path(env)));
}
