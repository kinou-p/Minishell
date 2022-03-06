/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/29 23:52:05 by apommier          #+#    #+#             */
/*   Updated: 2022/01/17 11:40:17 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_set(char const *set, char c)
{
	int		i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	len_dest(const char *s1, char const *set)
{
	int		len;
	int		j;
	int		i;

	i = 0;
	j = 0;
	len = ft_strlen(s1);
	while (is_set(set, s1[i]))
		i++;
	while (is_set(set, s1[len - j - 1]))
		j++;
	len = len - j - i;
	if (len < 0)
		len = 0;
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		j;
	int		i;
	int		len;
	char	*dest;

	i = 0;
	j = 0;
	if (!s1)
		return (0);
	len = len_dest(s1, set);
	dest = ft_calloc(len + 1, 1);
	if (!dest)
		return (0);
	while (is_set(set, s1[i]))
		i++;
	while (s1[i] && len - j && len > 0)
	{
		dest[j] = s1[i];
		i++;
		j++;
	}
	return (dest);
}
