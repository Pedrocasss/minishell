/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:12:20 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/23 10:12:21 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ctrl_c(int sig)
{
	(void)sig;
	*exit_stts() = 130;
	if (*is_inside() > 0)
	{
		write(1, "\n", 1);
		return ;
	}
	else if (!*is_inside())
	{
		write(2, "^C\n", 3);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ctrl_bs(int sig)
{
	(void)sig;
	if (*is_inside() < 1)
		SIG_IGN ;
	else
	{
		*exit_stts() = 131;
		ft_putendl_fd("Quit (core dumped)\n", STDERR_FILENO);
	}
}

void	sig_handle(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, ctrl_c);
	signal(SIGQUIT, ctrl_bs);
}

void	here_c(int sig)
{
	(void)sig;
	write(2, "^C\n", 3);
	exit(*exit_stts());
}

void	signal_here(void)
{
	signal(SIGINT, here_c);
	signal(SIGQUIT, SIG_IGN);
}
