/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 10:31:49 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/14 18:29:53 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	tree_add_pipe(t_tree **root)
{
	t_tree	*tmp;
	t_tree	*pipe;

	tmp = *root;
	pipe = malloc(sizeof(*pipe));
	pipe->type = E_PIPE;
	pipe->left = NULL;
	pipe->right = NULL;
	pipe->parent = NULL;
	pipe->content = NULL;
	if (!tmp)
	{
		*root = pipe;
		return ;
	}
	while (tmp->parent)
		tmp = tmp->parent;
	tmp->parent = pipe;
	pipe->left = tmp;
}

static void	tar_util(char *arg, int *i, int *j)
{
	while (arg[*i] && (arg[*i] == ' ' || arg[*i] == '\t'))
		(*i)++;
	if (!arg[*i])
		print_syntax_error();
	*j = *i;
	while (arg[*j] && (arg[*j] == ' ' || arg[*j] == '\t'))
		(*j)++;
}

static void	tar_util2(char *arg, t_ndtype type, t_parse parse)
{
	if (type == E_HDOC)
	{
		if (!(*(parse.tree)))
			tree_add_n_parse(parse.tree, quotes_rm(arg), type);
		else
			tree_add_node(quotes_rm(arg), type, parse);
	}
	else
	{
		if (!(*(parse.tree)))
			tree_add_n_parse(parse.tree, \
			quotes_rm(parse_signs(arg, parse.env)), type);
		else
			tree_add_node(quotes_rm(parse_signs(arg, parse.env)), type, parse);
	}
}

static void	check_export(char *arg, t_ndtype type, t_parse parse)
{
	char	*tmp;

	tmp = quotes_rm(arg);
	if (!ft_strncmp(tmp, "export", ft_strlen(tmp)) && type == E_CMD)
		*(parse.exp) = 1;
	free(tmp);
}

int	tree_add_case(char *arg, int i, t_ndtype type, t_parse parse)
{
	int	j;

	if (type == E_HDOC || type == E_APPEND)
		i++;
	i++;
	tar_util(arg, &i, &j);
	if (!arg[j] || !is_diff_sign("<>|&", arg[j]))
		print_syntax_error();
	while (arg[j] && is_diff_sign("<>|& \t", arg[j]))
	{
		if (!is_diff_sign("\"'", arg[j]))
			j = quotes_skip(arg, j);
		j++;
	}
	if (*syntax())
		return (0);
	check_export(ft_substr(arg, i, j - 1), type, parse);
	tar_util2(ft_substr(arg, i, j - 1), type, parse);
	return (j);
}
