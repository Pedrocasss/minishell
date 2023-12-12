/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:08:48 by paugonca          #+#    #+#             */
/*   Updated: 2022/10/13 12:44:07 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*res;
	int		p;

	res = (char *)s;
	p = 0;
	while (res[p] && res[p] != c)
		p++;
	if (res[p] == c)
		return (&res[p]);
	return (0);
}
