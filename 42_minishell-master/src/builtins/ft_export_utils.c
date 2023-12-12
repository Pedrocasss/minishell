/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:40:30 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/26 10:58:51 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_fail(char *arg)
{
	char	*msg;

	msg = ft_strjoin(SHELL, ": export: `");
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
	*exit_stts() = 1;
	free(msg);
	return (0);
}

static bool	is_exportable(char *arg)
{
	int	i;

	if (!ft_strlen(arg) || arg[0] == '=')
		return (export_fail(arg));
	if (ft_isdigit(arg[0]))
		return (0);
	i = 0;
	while (arg[i] && arg[i] != '=')
		if (!is_var(arg[i++]))
			return (export_fail(arg));
	return (true);
}

static void	export_add(char *arg, char ***env, int size)
{
	int		i;
	char	**new_env;

	if (!is_exportable(arg))
		return ;
	i = -1;
	new_env = malloc((size + 2) * sizeof(char *));
	while (++i < size)
		new_env[i] = ft_strdup((*env)[i]);
	new_env[i] = ft_strdup(arg);
	new_env[++i] = NULL;
	free_mtx(*env);
	*env = new_env;
}

void	export_arg_new(char *arg, char ***env, int i)
{
	if (!((*env)[i]))
		export_add(arg, env, i);
	else
	{
		free((*env)[i]);
		(*env)[i] = ft_strdup(arg);
	}
	free(arg);
}
