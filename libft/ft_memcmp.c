/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadjigui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 17:11:51 by sadjigui          #+#    #+#             */
/*   Updated: 2021/05/31 17:11:55 by sadjigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *p1, const void *p2, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (!(*(unsigned char *)(p1 + i) == *(unsigned char *)(p2 + i)))
			return (*(unsigned char *)(p1 + i) - *(unsigned char *)(p2 + i));
		i++;
	}
	return (0);
}
