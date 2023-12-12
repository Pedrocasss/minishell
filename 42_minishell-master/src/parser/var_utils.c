/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 16:48:54 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/25 15:59:49 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	is_var(char c)
{
	return (ft_isalnum(c) || c == '_');
}

static void	add_var_helper(t_var tmp)
{
	tmp.i = 0;
	tmp.j = 0;
	while ((tmp.str)[tmp.i])
	{
		if ((tmp.str)[tmp.i] && tmp.i >= tmp.start - 1 && tmp.i <= tmp.end)
		{
			tmp.i = -1;
			if (tmp.var)
			{
				while (tmp.var[++tmp.i])
					(*(tmp.res))[tmp.j++] = tmp.var[tmp.i];
			}
			tmp.i = tmp.end + 1;
		}
		if ((tmp.str)[tmp.i] && (tmp.i < tmp.start || tmp.i > tmp.end))
			(*(tmp.res))[tmp.j] = (tmp.str)[tmp.i];
		if ((tmp.str)[tmp.i])
			tmp.i++;
		tmp.j++;
	}
}

char	*add_var(char *str, char *var, int start, int end)
{
	char	*res;
	t_var	tmp;

	if (var)
		res = malloc(ft_strlen(str) - (end - start + 2) + ft_strlen(var) + 1);
	else
		res = malloc(ft_strlen(str) - (end - start + 2) + 1);
	tmp.str = str;
	tmp.var = var;
	tmp.res = &res;
	tmp.start = start;
	tmp.end = end;
	add_var_helper(tmp);
	if (var)
		res[ft_strlen(str) - (end - start + 2) + ft_strlen(var)] = 0;
	else
		res[ft_strlen(str) - (end - start + 2)] = 0;
	if (var)
		free(var);
	return (res);
}

char	*find_var(char *var, char **env)
{
	int		i;
	int		size;
	char	*tmp;

	tmp = ft_strdup(var + 1);
	if (ft_isdigit(*var))
	{
		free(var);
		return (tmp);
	}
	free(tmp);
	i = -1;
	while (env[++i])
		if (!ft_strncmp(env[i], var, find_eq_sign(env[i])) && \
		!var[find_eq_sign(env[i])])
			break ;
	size = ft_strlen(var);
	if (var)
		free(var);
	if (!env[i])
		return (NULL);
	return (ft_strdup(env[i] + size + 1));
}

char	*get_var(char *str, int *i, char **env)
{
	int		j;
	char	*res;

	j = (*i) + 1;
	if (str[j] == '?')
	{
		return (get_stts(str, *i, ft_itoa(*exit_stts())));
		(*i)++;
	}
	while (str[j] && is_var(str[j]))
		j++;
	if (j == (*i) + 1)
	{
		(*i)++;
		return (str);
	}
	res = add_var(str, find_var(ft_substr(str, (*i) + 1, j - 1), env), \
		(*i) + 1, j - 1);
	if (str)
		free(str);
	return (res);
}
