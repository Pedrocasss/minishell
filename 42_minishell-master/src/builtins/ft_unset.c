/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:40:46 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/16 14:40:48 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	unset_fail(char *arg)
{
	char	*msg;

	msg = ft_strjoin(arg, ": not a valid identifier");
	print_shell_err("unset", msg, NO_EXIT);
	return (false);
}

static bool	is_unsettable(char *arg)
{
	int	i;

	if (!(ft_strlen(arg) || ft_isalpha(arg[0])))
		return (unset_fail(arg));
	i = 0;
	while (arg[i])
		if (!is_var(arg[i++]))
			return (unset_fail(arg));
	return (true);
}

static void	unset_arg_new(char ***env, char ***new_env, char *arg)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while ((*env)[++i])
	{
		if (ft_strncmp((*env)[i], arg, find_eq_sign((*env)[i])))
			(*new_env)[j++] = ft_strdup((*env)[i]);
	}
	(*new_env)[j] = NULL;
}

static void	unset_arg(char *arg, char ***env)
{
	int		i;
	char	**new_env;

	if (!is_unsettable(arg))
		return ;
	i = -1;
	while ((*env)[++i])
	{
		if (!ft_strncmp((*env)[i], arg, ft_strlen(arg)) && \
		(!((*env)[i][ft_strlen(arg)]) \
		|| ((*env)[i][ft_strlen(arg)]) == '='))
		{
			new_env = malloc(sizeof(char *) * mtx_len(*env));
			unset_arg_new(env, &new_env, arg);
			free_mtx(*env);
			*env = new_env;
			return ;
		}
	}
}

int	ft_unset(char **args, char ***env)
{
	int	i;

	i = 1;
	while (args[i])
		unset_arg(args[i++], env);
	free_mtx(args);
	return (1);
}
