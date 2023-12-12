/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 16:55:14 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/14 18:19:28 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	tree_add_branch(t_tree **node, char *arg, t_ndtype type, int left)
{
	t_tree	*branch;

	branch = malloc(sizeof(*branch));
	branch->type = type;
	branch->content = arg;
	branch->left = NULL;
	branch->right = NULL;
	branch->parent = *node;
	if (!(*node))
	{
		*node = branch;
		branch->parent = NULL;
	}
	else if (!left)
		(*node)->left = branch;
	else
		(*node)->right = branch;
}

void	tree_add_n_parse(t_tree **node, char *arg, t_ndtype type)
{
	t_tree	*tmp;

	if (!(*node))
		tree_add_branch(node, arg, type, 0);
	else
	{
		tmp = *node;
		while (tmp->left)
			tmp = tmp->left;
		tree_add_branch(&tmp, arg, type, 0);
	}
}

void	tree_add_node(char *arg, t_ndtype type, t_parse parse)
{
	t_tree	*node;

	node = *(parse.tree);
	while (parse.pos - 1 > 0)
	{
		node = node->parent;
		parse.pos--;
	}
	if (!node)
		return ;
	if (parse.pos == 0)
		while (node->left)
			node = node->left;
	else
		while (node->right)
			node = node->right;
	if (parse.pos == 0)
		tree_add_branch(&node, arg, type, 0);
	else
		tree_add_branch(&node, arg, type, 1);
}
