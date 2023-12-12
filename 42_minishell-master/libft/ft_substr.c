/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 20:18:40 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/04 12:37:11 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//Repurposed for this project
char	*ft_substr(char const *s, int start, int end)
{
	char	*sub;
	int		i;

	i = 0;
	if (start > end)
		return (NULL);
	sub = malloc(end - start + 2);
	while (start <= end)
	{
		sub[i] = s[start];
		start++;
		i++;
	}
	sub[i] = 0;
	return (sub);
}
