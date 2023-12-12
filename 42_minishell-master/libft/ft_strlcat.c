/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 16:54:45 by paugonca          #+#    #+#             */
/*   Updated: 2022/10/13 11:46:24 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_size;
	size_t	src_size;
	size_t	p;
	size_t	i;

	dst_size = ft_strlen(dst);
	src_size = ft_strlen(src);
	p = dst_size;
	i = 0;
	if (size == 0 || size <= p)
		return (src_size + size);
	while (src[i] && (i < (size - dst_size - 1)))
	{
		dst[p] = src[i];
		p++;
		i++;
	}
	dst[p] = '\0';
	return (dst_size + src_size);
}
/*
#include <stdio.h>

int	main(void)
{
	char	dst[] = "cat stuff here";
	char	src[] = "hehehehaw";
	size_t	size = 4;

	printf("My ft_strlcat: %zu\n", ft_strlcat(dst, src, size));
	return (0);
}
*/
