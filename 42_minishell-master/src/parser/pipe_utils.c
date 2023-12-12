/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:37:41 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/17 13:57:51 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	check_pipes_utils(char *arg, int *i)
{
	while (arg[*i])
	{
		if (arg[*i] && !is_diff_sign("\"'", arg[*i]))
			*i = quotes_skip(arg, *i);
		if (arg[*i] && !is_diff_sign("|", arg[*i]))
		{
			(*i)++;
			while (arg[*i] && (arg[*i] == ' ' || arg[*i] == '\t'))
				(*i)++;
			if (arg[*i] && !is_diff_sign("|", arg[*i]))
				print_syntax_error();
		}
		else
			(*i)++;
		if (*syntax())
			return ;
	}
}

void	check_pipes(char *arg)
{
	int	i;

	i = 0;
	if (!arg)
		return ;
	while (arg[i] && (arg[i] == ' ' || arg[i] == '\t'))
		i++;
	if (arg[i] && !is_diff_sign("|", arg[i]))
		print_syntax_error();
	check_pipes_utils(arg, &i);
	if (*syntax())
		return ;
}

void	pipe_add2pos(t_pipe **pipes, int pos, int num)
{
	t_pipe	*res;
	t_pipe	*tmp;

	tmp = *pipes;
	res = malloc(sizeof(*res));
	res->pos = pos;
	res->num = num;
	res->next = NULL;
	if (!tmp)
	{
		*pipes = res;
		return ;
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = res;
}

char	**pipe_split(t_pipe *pipes, char *arg)
{
	int		i;
	char	**res;
	t_pipe	*tmp;

	if (!pipes)
		return (NULL);
	tmp = pipes;
	while (tmp->next)
		tmp = tmp->next;
	res = malloc((tmp->num + 3) * sizeof(char *));
	i = 0;
	while (pipes)
	{
		res[pipes->num] = ft_substr(arg, i, pipes->pos - 1);
		i = pipes->pos + 1;
		if (!pipes->next)
		{
			res[pipes->num + 1] = ft_substr(arg, i, ft_strlen(arg) - 1);
			res[pipes->num + 2] = 0;
		}
		pipes = pipes->next;
	}
	return (res);
}

void	free_pipes(t_pipe **pipes)
{
	if (!pipes || !(*pipes))
		return ;
	free_pipes(&((*pipes)->next));
	free(*pipes);
	*pipes = NULL;
}
