/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 22:54:40 by apommier          #+#    #+#             */
/*   Updated: 2020/12/16 16:45:34 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*dest;
	unsigned int	i;

	if (!s)
		return (0);
	i = 0;
	dest = malloc(1 * len + 1);
	if (dest == 0)
		return (0);
	if (start > ft_strlen(s) || len == 0)
	{
		dest[i] = 0;
		return (dest);
	}
	while (len && s[i + start])
	{
		dest[i] = s[i + start];
		len--;
		i++;
	}
	dest[i] = 0;
	return (dest);
}
