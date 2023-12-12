/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:37:24 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/16 14:37:26 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	parse_part1(char *arg, int *i)
{
	if (*syntax())
		return ;
	if (!is_diff_sign("\"'", arg[*i]))
		*i = quotes_skip(arg, *i);
}

void	parse_all(t_tree **root, char *arg, t_pipe **pipes, int num)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		parse_part1(arg, &i);
		if (*syntax())
			return (free(arg));
		if (arg[i] == '|' && arg[i + 1] && arg[i + 1] != '|')
		{
			tree_add_pipe(root);
			pipe_add2pos(pipes, i, num);
			num++;
		}
		if (arg[i])
			i++;
		if (*syntax())
			return (free(arg));
	}
}
