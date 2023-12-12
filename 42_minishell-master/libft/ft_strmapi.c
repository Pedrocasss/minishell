/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:04:40 by paugonca          #+#    #+#             */
/*   Updated: 2022/10/18 17:41:06 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*res;
	unsigned int	p;

	if (!s || !f)
		return (0);
	p = 0;
	res = ft_strdup(s);
	if (!res)
		return (0);
	while (res[p])
	{
		res[p] = f(p, res[p]);
		p++;
	}
	return (res);
}
