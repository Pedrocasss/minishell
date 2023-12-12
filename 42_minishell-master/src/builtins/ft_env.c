/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:40:12 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/16 14:40:16 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(char **env, int fd)
{
	int	i;

	i = -1;
	while (env[++i])
		if (find_eq_sign(env[i]) != -1)
			ft_putendl_fd(env[i], fd);
	return (1);
}
