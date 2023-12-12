/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termios_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/21 20:18:31 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/21 20:18:54 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_set_termios(void)
{
	struct termios	term;
	struct termios	termbase;

	if (tcgetattr(STDIN_FILENO, &term) != 0 || \
	tcgetattr(STDIN_FILENO, &termbase) != 0)
		print_err("failed to get terminal attributes", EXIT_FAILURE);
	term.c_cc[VQUIT] = _POSIX_VDISABLE;
	term.c_lflag &= ~ECHOCTL;
}
