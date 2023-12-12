/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 13:12:58 by paugonca          #+#    #+#             */
/*   Updated: 2022/10/14 15:25:55 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t len)
{
	unsigned int	p;

	p = 0;
	if (len == 0)
		return (0);
	while (p < len && s1[p] && s2[p] && s1[p] == s2[p])
		p++;
	if (p == len)
		p--;
	return (((unsigned char *)s1)[p] - ((unsigned char *)s2)[p]);
}
