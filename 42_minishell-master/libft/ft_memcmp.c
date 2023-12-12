/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 22:58:39 by paugonca          #+#    #+#             */
/*   Updated: 2022/10/19 15:22:15 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *b1, const void *b2, size_t len)
{
	size_t	p;

	p = 0;
	while (p < len)
	{
		if (((unsigned char *)b1)[p] != ((unsigned char *)b2)[p])
			return (((unsigned char *)b1)[p] - ((unsigned char *)b2)[p]);
		p++;
	}
	return (0);
}
