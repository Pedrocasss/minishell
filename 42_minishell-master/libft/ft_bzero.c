/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paugonca <paugonca@student.42lisboa.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 17:51:43 by paugonca          #+#    #+#             */
/*   Updated: 2022/10/13 22:55:40 by paugonca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//IN CONSTRUCTION

#include "libft.h"

void	ft_bzero(void *b, size_t len)
{
	size_t	p;

	p = 0;
	while (p < len)
	{
		((unsigned char *)b)[p] = 0;
		p++;
	}
}
