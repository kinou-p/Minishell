/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 00:12:57 by apommier          #+#    #+#             */
/*   Updated: 2020/12/12 15:40:58 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	k;

	if (!size)
		return (ft_strlen(src));
	i = 0;
	k = ft_strlen(dst);
	if (k >= size)
		return (ft_strlen(src) + size);
	while (size - k - 1 && src[i])
	{
		dst[k + i] = src[i];
		i++;
		size--;
	}
	dst[k + i] = 0;
	return (k + ft_strlen(src));
}
