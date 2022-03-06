/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadjigui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/25 16:09:10 by sadjigui          #+#    #+#             */
/*   Updated: 2021/06/03 16:14:11 by sadjigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*dest;
	int				a;

	if (!s)
		return (0);
	a = ft_strlen(s);
	dest = NULL;
	i = 0;
	if (!s || !f)
		return (NULL);
	dest = malloc(sizeof(char) * a + 1);
	if (!dest)
		return (NULL);
	while (s[i])
	{
		dest[i] = (*f)(i, (char)s[i]);
		i++;
	}
	dest[i] = 0;
	return (dest);
}
