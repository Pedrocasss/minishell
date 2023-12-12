/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 12:19:59 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/25 12:24:20 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fd_close_cmd(t_tree **node)
{
	t_tree	*a;

	a = *node;
	if (!node || !(*node))
		return ;
	fd_close_cmd(&((*node)->left));
	fd_close_cmd(&((*node)->right));
	if ((*node)->type == E_BUILTIN && (*node)->pipes[1] > 2)
		close((*node)->pipes[1]);
	if ((*node)->type == E_BUILTIN && (*node)->pipes[0] > 2)
		close((*node)->pipes[0]);
	if ((*node)->type == E_CMD && ((t_cmd *)*node)->pipes[1] > 2)
		close(((t_cmd *)*node)->pipes[1]);
	if ((*node)->type == E_CMD && ((t_cmd *)*node)->pipes[0] > 2)
		close(((t_cmd *)*node)->pipes[0]);
	*node = a;
}

void	fd_close_hdoc(t_tree **node)
{
	t_tree	*a;

	a = *node;
	if (!node || !(*node))
		return ;
	fd_close_hdoc(&((*node)->left));
	fd_close_hdoc(&((*node)->right));
	if ((*node)->type == E_HDOC && (*node)->pipes[1] > 2)
		close((*node)->pipes[1]);
	if ((*node)->type == E_HDOC && (*node)->pipes[0] > 2)
		close((*node)->pipes[0]);
	*node = a;
}

void	fd_close_all(int fd)
{
	while (fd < FOPEN_MAX)
		close(fd++);
}
