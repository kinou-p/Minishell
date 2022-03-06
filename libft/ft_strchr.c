/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 13:57:59 by apommier          #+#    #+#             */
/*   Updated: 2022/01/17 21:18:59 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	if (!s)
		return ("no s");
	str = (char *)s;
	while ((*str != c) && (*str != 0))
		str++;
	if (*str == c)
		return ((char *)str);
	else
		return (0);
}
