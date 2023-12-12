/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:39:17 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/21 17:44:28 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	open_builtin_in(t_tree *node)
{
	int	fd;

	while (node)
	{
		if (node->type == E_STDIN)
		{
			fd = open(node->content, O_RDONLY, S_STDPERMS);
			if (fd == -1)
			{
				print_builtin_err(node->content);
				*exit_stts() = 1;
			}
			close(fd);
		}
		node = node->left;
	}
	return (1);
}

int	redir_builtin_in(t_tree *node)
{
	pid_t	pid;
	int		stts;

	if (!get_redir_num(node, 0, E_IN))
		return (0);
	pid = fork();
	if (pid < 0)
		print_err("failed to fork process", EXIT_FAILURE);
	if (pid == 0)
		exit(open_builtin_in(node));
	waitpid(pid, &stts, 0);
	*exit_stts() = WEXITSTATUS(stts);
	if (*exit_stts() == 255)
		*exit_stts() = EXIT_FAILURE;
	else
		*exit_stts() = EXIT_SUCCESS;
	return (*exit_stts());
}

static int	rdo_check_fd(int fd)
{
	if (fd == -1)
	{
		*exit_stts() = 1;
		return (0);
	}
	return (1);
}

int	redir_builtin_out(t_tree *node)
{
	t_cmd	cmd;
	int		i;
	int		fd;

	cmd.out = get_redir_num(node, 0, E_OUT);
	i = 0;
	while (node)
	{
		if (node->type == E_STDOUT || node ->type == E_APPEND)
		{
			if (node->type == E_STDOUT)
				fd = open(node->content, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			else
				fd = open(node->content, O_CREAT | O_WRONLY | O_APPEND, 0644);
			i++;
			if (!rdo_check_fd(fd))
				return (print_builtin_err(node->content));
			if (i != cmd.out)
				close(fd);
			else
				return (fd);
		}
		node = node->left;
	}
	return (1);
}
