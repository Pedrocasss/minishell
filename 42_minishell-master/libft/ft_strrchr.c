/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 13:24:42 by paugonca          #+#    #+#             */
/*   Updated: 2022/10/13 12:44:51 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*res;
	int		p;

	res = (char *)s;
	p = ft_strlen(s);
	while (p > 0 && res[p] != c)
		p--;
	if (res[p] == c)
		return (&res[p]);
	return (0);
}
