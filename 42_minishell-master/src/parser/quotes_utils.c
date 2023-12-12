/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 15:51:58 by jferreir          #+#    #+#             */
/*   Updated: 2023/10/14 19:01:39 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	quotes_skip(char *str, int i)
{
	char	tmp;

	tmp = str[i++];
	while (str[i] && str[i] != tmp)
		i++;
	if (!str[i])
	{
		ft_putendl_fd("Unclosed quotes!", STDOUT_FILENO);
		print_syntax_error();
	}
	return (i);
}

int	get_quote_num(char *str)
{
	int		i;
	int		count;
	char	qt;

	i = 0;
	count = 0;
	while (str && str[i])
	{
		if (str[i] && !is_diff_sign("'\"", str[i]))
		{
			qt = str[i];
			i++;
			while (str[i] && str[i] != qt)
				i++;
			count += 2;
		}
		i++;
	}
	return (count);
}

static char	*quotes_rm_fr(char *str, int i, int j, char tmp)
{
	char	*res;

	res = malloc(sizeof(char) * ft_strlen(str) - get_quote_num(str) + 1);
	while (str && str[i])
	{
		if (str[i] && !is_diff_sign("'\"", str[i]))
		{
			tmp = str[i];
			i++;
			while (str[i] && str[i] != tmp)
			{
				res[j] = str[i];
				j++;
				i++;
			}
		}
		else
		{
			res[j] = str[i];
			j++;
		}
		i++;
	}
	res[j] = 0;
	return (res);
}

char	*quotes_rm(char *str)
{
	char	*res;

	res = quotes_rm_fr(str, 0, 0, ' ');
	free(str);
	return (res);
}
