/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:54:47 by paugonca          #+#    #+#             */
/*   Updated: 2022/10/13 13:04:39 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	p;
	size_t	i;

	p = 0;
	if (!little[0])
		return ((char *)big);
	while (big[p])
	{
		i = 0;
		while (big[p + i] == little[i] && (p + i) < len)
		{
			if (!big[p + i] && !little[i])
				return ((char *)&big[i]);
			i++;
		}
		if (!little[i])
			return ((char *)big + p);
		p++;
	}
	return (0);
}
