/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 00:12:43 by apommier          #+#    #+#             */
/*   Updated: 2020/12/11 18:35:10 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*sdup;

	i = 0;
	while (s[i])
		i++;
	sdup = malloc(sizeof(char) * (i + 1));
	if (sdup == 0)
		return (0);
	i = 0;
	while (s[i])
	{
		sdup[i] = s[i];
		i++;
	}
	sdup[i] = 0;
	return (sdup);
}
