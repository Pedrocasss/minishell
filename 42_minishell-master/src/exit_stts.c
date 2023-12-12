/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_stts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 13:04:17 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/25 12:21:26 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*exit_stts(void)
{
	static int	fuck_the_subject;

	return (&fuck_the_subject);
}

void	set_exit_stts(int stts)
{
	if (WIFSIGNALED(stts))
	{
		*exit_stts() = WTERMSIG(stts) + 128;
		if (stts == SIGINT)
			ft_putendl_fd(NULL, STDIN_FILENO);
	}
	else
		*exit_stts() = WEXITSTATUS(stts);
}
