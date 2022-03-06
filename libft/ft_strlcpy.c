/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 00:13:07 by apommier          #+#    #+#             */
/*   Updated: 2022/01/17 11:38:48 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	if (!src || !dst)
		return (0);
	while (src[i])
		i++;
	if (!size)
		return (i);
	while (size - 1 && src[j] != 0)
	{
		dst[j] = src[j];
		j++;
		size--;
	}
	dst[j] = 0;
	return (i);
}
