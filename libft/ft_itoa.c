/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/08 18:20:19 by apommier          #+#    #+#             */
/*   Updated: 2022/01/17 11:28:01 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*fill(long n, int j, int minus)
{
	char	*dest;

	j += minus;
	dest = (char *)malloc(sizeof(char) * (j + 1));
	if (dest == 0)
		return (0);
	dest[j] = 0;
	if (n == 0)
		dest[j - 1] = '0';
	while (n)
	{
		dest[j - 1] = n % 10 + '0';
		j--;
		n /= 10;
	}
	if (minus)
		dest[j - 1] = '-';
	return (dest);
}

char	*ft_itoa(int n)
{
	long	i;
	long	k;
	int		j;
	int		minus;

	k = n;
	minus = 0;
	j = 1;
	if (k < 0)
	{
		minus = 1;
		k = k * -1;
	}
	i = k;
	while (k >= 10)
	{
		k /= 10;
		j++;
	}
	return (fill(i, j, minus));
}
