/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 14:43:43 by jferreir          #+#    #+#             */
/*   Updated: 2023/10/19 16:26:10 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_max_long(char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '+' || arg[i] == '-')
		i = 1;
	while (arg[i] == '0')
		i++;
	if (ft_strlen(&arg[i]) < 19)
		return (1);
	if (ft_strlen(&arg[i]) > 19)
		return (0);
	if (arg[0] == '-')
	{
		if (ft_strncmp(&arg[i], "9223372036854775808", ft_strlen(&arg[i])) > 0)
			return (0);
	}
	else if (ft_strncmp(&arg[i], "9223372036854775807", ft_strlen(&arg[i])) > 0)
		return (0);
	return (1);
}

static int	is_nbr(char *str)
{
	int	i;
	int	nbr;

	nbr = 0;
	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if (!nbr)
			nbr = 1;
		i++;
	}
	if (!str[i] && nbr)
		return (1);
	return (0);
}

static int	quit(char **args, int isnum)
{
	if (args[1] && args[2] && isnum == 1)
	{
		ft_putstr_fd(SHELL, STDERR_FILENO);
		ft_putstr_fd(": exit: too many arguments\n", STDERR_FILENO);
		free_mtx(args);
		*exit_stts() = EXIT_FAILURE;
		return (-1);
	}
	*exit_stts() = 2;
	ft_putstr_fd("exit\n", STDERR_FILENO);
	ft_putstr_fd(SHELL, STDERR_FILENO);
	ft_putstr_fd(": exit: ", STDERR_FILENO);
	ft_putstr_fd(args[1], STDERR_FILENO);
	ft_putstr_fd(":	numeric argument required\n", STDERR_FILENO);
	free_mtx(args);
	rl_clear_history();
	exit(2);
	return (-42);
}

static void	ft_exit_args(char **args, int nbr)
{
	if ((nbr == 1 || mtx_len(args) == 2) || mtx_len(args) == 1)
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		if (nbr == 1)
		{
			*exit_stts() = (unsigned int)ft_atoi(args[1]);
			free_mtx(args);
			rl_clear_history();
			exit(*exit_stts());
		}
		free_mtx(args);
		rl_clear_history();
		exit(*exit_stts());
	}
}

int	ft_exit(char **args)
{
	long long int	nbr;

	nbr = 0;
	if (args[0] && !args[1])
	{
		ft_putstr_fd("exit\n", STDOUT_FILENO);
		*exit_stts() = 0;
		free_mtx(args);
		rl_clear_history();
		exit(*exit_stts());
	}
	if (args[1])
	{
		if (!check_max_long(args[1]) || !is_nbr(args[1]))
			return (quit(args, nbr));
	}
	if ((args[1] && is_nbr(args[1])))
		nbr = 1;
	if (args && args + 2 && args[2])
		return (quit(args, nbr));
	ft_exit_args(args, nbr);
	return (quit(args, nbr));
}
