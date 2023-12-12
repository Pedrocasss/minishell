/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:40:06 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/23 10:09:32 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	is_flag(char *arg)
{
	int	i;

	i = -1;
	while (arg[++i])
		if ((!i && arg[i] != '-') || (i && arg[i] != 'n'))
			return (false);
	return (true);
}

int	ft_echo(char **args, int fd)
{
	int	i;

	i = 1;
	if (mtx_len(args) > 1 && is_flag(args[1]))
		i++;
	while (args[i])
	{
		ft_putstr_fd(args[i], fd);
		if (args[i + 1])
			ft_putstr_fd(" ", fd);
		i++;
	}
	if (!(mtx_len(args) > 1 && is_flag(args[1])) || !args[1][0])
		ft_putchar_fd('\n', fd);
	free_mtx(args);
	*exit_stts() = 0;
	return (1);
}
