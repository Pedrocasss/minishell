/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psoares- <psoares-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 23:21:16 by paugonca          #+#    #+#             */
/*   Updated: 2023/10/10 15:25:08 by psoares-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	lendef(int n)
{
	if (n > 0)
		return (0);
	return (1);
}

int	signdef(int n)
{
	if (n > 0)
		return (1);
	return (-1);
}

char	*ft_itoa(long int n)
{
	char	*res;
	size_t	len;
	long	num;

	len = lendef(n);
	num = (long)n * signdef(n);
	while (n)
	{
		n /= 10;
		len++;
	}
	res = (char *)malloc(len + 1);
	if (!res)
		return (0);
	*(res + len--) = '\0';
	while (num > 0)
	{
		*(res + len--) = num % 10 + 48;
		num /= 10;
	}
	if (len == 0 && res[1] == '\0')
		*(res + len) = 48;
	else if (len == 0 && res[1] != '\0')
		*(res + len) = '-';
	return (res);
}
