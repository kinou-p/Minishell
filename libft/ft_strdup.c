/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadjigui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/22 15:05:42 by sadjigui          #+#    #+#             */
/*   Updated: 2021/06/03 12:38:05 by sadjigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcpy(char *dest, const char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strdup(const char *src)
{
	size_t		i;
	char		*copy;

	copy = NULL;
	i = ft_strlen(src);
	copy = malloc(sizeof(char) * i + 1);
	if (!copy)
		return (NULL);
	copy = ft_strcpy(copy, src);
	return (copy);
}
