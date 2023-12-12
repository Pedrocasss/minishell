/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_stts_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:37:11 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/16 14:37:28 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	get_stts_utils(char *str, int i, char *val, char **res)
{
	int		k;
	int		j;
	int		l;

	l = 0;
	k = 0;
	j = 0;
	while (str[k + l])
	{
		if ((k + j) == i)
		{
			while (val[j])
			{
				(*res)[k + j] = val[j];
				j++;
			}
			l = 2;
		}
		else
		{
			(*res)[k + j] = str[k + l];
			k++;
		}
	}
	(*res)[k + j] = 0;
}

char	*get_stts(char *str, int i, char *val)
{
	char	*res;

	res = malloc(ft_strlen(str) - 2 + ft_strlen(val) + 1);
	get_stts_utils(str, i, val, &res);
	free(val);
	free(str);
	return (res);
}
