/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 13:48:22 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/23 13:06:19 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_cmd(t_tree *node, int pos)
{
	if (!pos)
		while (node && node->type != E_CMD)
			node = node->left;
	else
		while (node && node->type != E_CMD)
			node = node->right;
	if (node)
		return (node->content);
	else
		return (NULL);
}

int	get_cmd_arg_num(t_tree *node, int pos)
{
	int	res;

	res = 0;
	while (node)
	{
		if (node->type == E_ARG || node->type == E_FLAG || node->type == E_CMD)
			res++;
		if (!pos)
			node = node->left;
		else
			node = node->right;
	}
	return (res);
}

char	**get_cmd_args(t_tree *node, int pos)
{
	int		p;
	char	**args;

	p = 0;
	args = malloc(sizeof(char *) * (get_cmd_arg_num(node, pos) + 1));
	if (!args)
		print_err("failed to allocate memory", EXIT_FAILURE);
	while (node)
	{
		if (node->type == E_ARG || node->type == E_FLAG || node->type == E_CMD)
			args[p++] = ft_strdup(node->content);
		if (!pos)
			node = node->left;
		else
			node = node->right;
	}
	args[p] = 0;
	return (args);
}

int	get_cmd_num(t_tree *node)
{
	int	res;

	res = 0;
	while (node)
	{
		if (!res && node->right)
			res++;
		res++;
		node = node->parent;
	}
	return (res);
}

char	**get_path(char **env)
{
	char	**path;
	char	*tmp;
	int		i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
		{
			path = ft_split(env[i] + 5, ':');
			i = 0;
			while (path[i])
			{
				tmp = ft_strdup(path[i]);
				free(path[i]);
				path[i] = ft_strjoin(tmp, "/");
				free(tmp);
				i++;
			}
			return (path);
		}
		i++;
	}
	return (NULL);
}
