/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:39:41 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/19 16:10:30 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	print_builtin_err(char *arg)
{
	ft_putstr_fd("Error: couldn't open file: ", STDERR_FILENO);
	ft_putendl_fd(arg, STDERR_FILENO);
	*exit_stts() = 1;
	free(arg);
	return (-1);
}

int	run_builtin(t_tree *node, char ***env, char *cmd, int fd)
{
	if (cmd && !ft_strncmp(cmd, "pwd", 4))
		return (ft_pwd(fd));
	if (cmd && !ft_strncmp(cmd, "exit", 5))
		return (ft_exit(get_cmd_args(node, 0)));
	if (cmd && !ft_strncmp(cmd, "echo", 5))
		return (ft_echo(get_cmd_args(node, 0), fd));
	if (cmd && !ft_strncmp(cmd, "env", 4))
		return (ft_env(*env, fd));
	if (cmd && !ft_strncmp(cmd, "export", 7))
		return (ft_export(get_cmd_args(node, 0), env, fd));
	if (cmd && !ft_strncmp(cmd, "unset", 6))
		return (ft_unset(get_cmd_args(node, 0), env));
	if (cmd && !ft_strncmp(cmd, "cd", 3))
		return (ft_cd(get_cmd_args(node, 0), env));
	if (fd > 2)
		close(fd);
	return (0);
}

bool	is_builtin(t_tree *node, char ***env, char *cmd)
{
	int	fd;

	if (cmd && (!ft_strncmp(cmd, "pwd", 4)
			|| !ft_strncmp(cmd, "exit", 5)
			|| !ft_strncmp(cmd, "echo", 5)
			|| !ft_strncmp(cmd, "env", 4)
			|| !ft_strncmp(cmd, "export", 7)
			|| !ft_strncmp(cmd, "unset", 6)
			|| !ft_strncmp(cmd, "cd", 3)))
	{
		if (redir_builtin_in(node))
			return (1);
		fd = redir_builtin_out(node);
		run_builtin(node, env, cmd, fd);
		return (1);
	}
	return (0);
}

int	builtin_ret(t_tree *node, char ***env, char *cmd, int pos)
{
	int	fd;

	fd = STDOUT_FILENO;
	if (cmd && !ft_strncmp(cmd, "pwd", 4))
		return (ft_pwd(fd));
	if (cmd && !ft_strncmp(cmd, "exit", 5))
		return (ft_exit(get_cmd_args(node, pos)));
	if (cmd && !ft_strncmp(cmd, "echo", 5))
		return (ft_echo(get_cmd_args(node, pos), fd));
	if (cmd && !ft_strncmp(cmd, "env", 4))
		return (ft_env(*env, fd));
	if (cmd && !ft_strncmp(cmd, "export", 7))
		return (ft_export(get_cmd_args(node, pos), env, fd));
	if (cmd && !ft_strncmp(cmd, "unset", 6))
		return (ft_unset(get_cmd_args(node, pos), env));
	if (cmd && !ft_strncmp(cmd, "cd", 3))
		return (ft_cd(get_cmd_args(node, pos), env));
	return (0);
}
