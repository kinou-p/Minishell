/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadjigui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 17:10:05 by sadjigui          #+#    #+#             */
/*   Updated: 2021/05/31 17:10:57 by sadjigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int ch, size_t maxSize)
{
	size_t	i;

	i = 0;
	while (i < maxSize)
	{
		*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
		if (*(unsigned char *)(src + i) == (unsigned char)ch)
			return (dest + i + 1);
		i++;
	}
	return (NULL);
}
