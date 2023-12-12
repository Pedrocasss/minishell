/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 21:27:26 by paugonca          #+#    #+#             */
/*   Updated: 2022/10/14 21:54:55 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	p;
	size_t	i;

	if (!s1 || !s2)
		return (0);
	res = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!res)
		return (0);
	p = 0;
	i = 0;
	while (s1[p])
		res[i++] = s1[p++];
	p = 0;
	while (s2[p])
		res[i++] = s2[p++];
	res[i] = '\0';
	return (res);
}
