/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 00:11:04 by apommier          #+#    #+#             */
/*   Updated: 2022/01/17 11:29:38 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	char		*p;
	const char	*p1;
	size_t		i;

	i = 0;
	p = (char *)dest;
	p1 = (const char *)src;
	while (i < n)
	{
		p[i] = p1[i];
		if ((unsigned char)p[i] == (unsigned char)c)
			return (dest + i + 1);
		i++;
	}
	return (0);
}
