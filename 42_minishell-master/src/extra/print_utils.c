/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:38:46 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/25 16:15:28 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_mtx(char **mtx)
{
	int	p;

	p = 0;
	while (mtx[p])
		ft_putendl_fd(mtx[p++], STDOUT_FILENO);
}

void	print_err(char *msg, int stts)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	*exit_stts() = stts;
	exit(*exit_stts());
}

void	print_shell_err(char *cmd, char *msg, int stts)
{
	ft_putstr_fd(SHELL, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(msg, STDERR_FILENO);
	if (stts != NO_EXIT)
	{
		*exit_stts() = stts;
		exit(*exit_stts());
	}
}

void	print_hdoc_warn(char *eof, char *in, int stts)
{
	ft_putstr_fd(SHELL, STDERR_FILENO);
	ft_putstr_fd(": warning: here-document delimited by end-of-file (wanted `",
		STDERR_FILENO);
	ft_putstr_fd(eof, STDERR_FILENO);
	ft_putendl_fd("')", STDERR_FILENO);
	free(eof);
	free(in);
	unlink(".heredoc_tmp");
	*exit_stts() = stts;
	exit(*exit_stts());
}

void	print_syntax_error(void)
{
	ft_putendl_fd("Syntax Error", STDOUT_FILENO);
	*exit_stts() = EXIT_FAILURE;
	(*syntax())++;
}
