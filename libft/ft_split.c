/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 00:54:12 by apommier          #+#    #+#             */
/*   Updated: 2022/01/21 08:09:38 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	fill_tab(char *s, char c, char **dest, size_t index)
{
	int		i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	dest[index] = (char *)ft_calloc(i + 1, sizeof(char));
	if (dest[index] == 0)
		return (0);
	i = 0;
	while (s[i] != c && s[i])
	{
		dest[index][i] = s[i];
		i++;
	}
	return (1);
}

static void	call(char *s, char c, char **dest, int j)
{
	int		index;
	int		k;

	k = 0;
	index = 0;
	while (j > index)
	{
		while (s[k] == c && s[k])
			k++;
		if (!s[k])
			return ;
		fill_tab(s + k, c, dest, index);
		index++;
		while (s[k] != c && s[k])
			k++;
	}
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**dest;

	j = 0;
	i = 0;
	if (!s)
		return (0);
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		while (s[i] != c && s[i])
			i++;
		j++;
		while (s[i] == c && s[i])
			i++;
	}
	dest = (char **)ft_calloc(sizeof(char *), (i + j));
	if (!dest)
		return (0);
	dest[j] = 0;
	call((char *)s, c, dest, j);
	return (dest);
}
