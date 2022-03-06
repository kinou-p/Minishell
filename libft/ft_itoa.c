/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadjigui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 13:13:20 by sadjigui          #+#    #+#             */
/*   Updated: 2021/05/31 17:09:12 by sadjigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	base_len(long nb)
{
	int	len;

	len = 1;
	if (nb < 0)
	{
		nb = -nb;
		len++;
	}
	while (nb >= 10)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

static void	filler(char *str, int i, long n)
{
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		str[i] = 48 + (n % 10);
		n /= 10;
		i--;
	}
}

char	*ft_itoa(int nb)
{
	long	n;
	int		i;
	char	*str;

	n = nb;
	i = base_len(n);
	str = (char *)malloc(sizeof(char) * i + 1);
	if (!str)
		return (NULL);
	str[i] = '\0';
	i--;
	if (n == 0)
	{
		str[0] = 48;
		return (str);
	}
	filler(str, i, n);
	return (str);
}
