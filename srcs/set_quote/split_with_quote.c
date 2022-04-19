/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_with_quote.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/10 19:50:50 by apommier          #+#    #+#             */
/*   Updated: 2022/04/19 12:03:45 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int next_quote(const char *s, int i)
{
	int simple_quote;
	int double_quote;

	simple_quote = 0;
	double_quote = 0;
	if (s[i] == '"' || s[i] == '\'')
	{
		
		if (s[i] == '"')
			double_quote = 1;
		else if (s[i] == '\'')
			simple_quote = 1;
		else
			printf("qu'es tu fous ?\n");
		i++;
		if (simple_quote)
		{
			while (s[i] != '\'')
				i++;
		}
		else
		{
			while (s[i] != '"')
				i++;
		}
		i++;
	}
	return (i);
}

static int	fill_tab(char *s, char c, char **dest, size_t index)
{
	int		i;
	int		size;

	i = 0;
	while (s[i] != c && s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
			i = next_quote(s, i);
		else
			i++;
	}
	dest[index] = (char *)ft_calloc(i + 1, sizeof(char));
	if (dest[index] == 0)
		return (0);
	size = i;
	i = 0;
	while (i < size)
	{
		dest[index][i] = s[i];
		i++;
	}
	return (1);
}

static void	call(char *s, char c, char **dest, int j)
{
	int		index;
	int		i;

	i = 0;
	index = 0;
	while (j > index)
	{
		while (s[i] != '"' && s[i] != '\'' && s[i] == c && s[i])
			i++;
		if (!s[i])
			return ;
		fill_tab(s + i, c, dest, index);
		index++;
		while (s[i] != c && s[i])
		{
			if (s[i] == '"' || s[i] == '\'')
				i = next_quote(s, i);
			else
				i++;
		}
	}
}

char	**ft_split_with_quote(char const *s, char c)
{
	int		i;
	int		j;
	char	**dest;

	j = 0;
	i = 0;
	if (!s)
		return (0);
	i = next_quote(s, i);
	if (i)
		j++;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		while (s[i] != c && s[i])
		{
			if (s[i] == '"' || s[i] == '\'')
				i = next_quote(s, i);
			else
				i++;
		}
		j++;
		while (s[i] == c && s[i])
			i++;
	}
	dest = (char **)ft_calloc(sizeof(char *), (1 + j));
	if (!dest)
		return (0);
	dest[j] = 0;
	call((char *)s, c, dest, j);
	return (dest);
}