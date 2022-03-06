/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadjigui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 14:58:49 by sadjigui          #+#    #+#             */
/*   Updated: 2021/05/25 16:30:00 by sadjigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t size)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*to_find == '\0')
		return ((char *)str);
	while (i < size && str[i])
	{
		if ((i + j) > size)
			return (NULL);
		if (to_find[j] == '\0')
			return ((char *)&str[i]);
		if (str[i + j] == to_find[j])
			j++;
		else
		{
			j = 0;
			i++;
		}
	}
	return (0);
}
