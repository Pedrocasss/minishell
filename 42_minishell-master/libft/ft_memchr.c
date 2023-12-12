/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/14 11:46:14 by paugonca          #+#    #+#             */
/*   Updated: 2022/10/14 12:02:22 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *b, int c, size_t len)
{
	size_t	p;

	p = 0;
	while (p < len)
	{
		if (*(const unsigned char *)(b + p) == (unsigned char)c)
			return ((unsigned char *)(b + p));
		p++;
	}
	return (0);
}
