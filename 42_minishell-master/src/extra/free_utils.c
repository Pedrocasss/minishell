/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:38:35 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/25 12:21:31 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_mtx(char **mtx)
{
	int	p;

	p = 0;
	if (!mtx)
		return ;
	while (mtx[p])
		free(mtx[p++]);
	free(mtx);
}

void	free_tree(t_tree **node)
{
	if (!node || !(*node))
		return ;
	free_tree(&((*node)->left));
	free_tree(&((*node)->right));
	if ((*node)->content)
		free((*node)->content);
	free(*node);
	*node = NULL;
}

t_tree	**get_tree_root(t_tree **node)
{
	t_tree	*root;

	if (!(*node))
		return (NULL);
	root = *node;
	while (root->parent)
		root = root->parent;
	*node = root;
	return (node);
}

int	mtx_len(char **mtx)
{
	int	res;

	res = 0;
	while (mtx[res])
		res++;
	return (res);
}
