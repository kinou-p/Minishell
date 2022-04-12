/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/07 17:58:25 by sadjigui          #+#    #+#             */
/*   Updated: 2022/04/09 04:55:48 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_swap(char **a, char **b)
{
	char *tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	sort_tab(char **av)
{
	int i;
	int x;

	i = 0;
	while (av[i])
	{
		x = i;
		while (av[x])
		{
			if (ft_strcmp(av[i], av[x]) > 0)
				ft_swap(&av[i], &av[x]);
			x++;
		}
		i++;
	}
}

void	print_export(char *tmp)
{
	char	*str1;
	char	*str2;
	int		i;

	i = 0;
	str1 = ft_substr(tmp, 0, find_len(tmp, i, '='));
	i = find_len(tmp, 0, '=') + 1;
	str2 = ft_substr(tmp, i, find_len(tmp, i, '\0'));
	printf("declare -x %s", str1);
	if (next_space(str2, 0) != '\0')
		printf("=\"%s\"", str2);
	printf("\n");
	free(str1);
	free(str2);

}

void	lone_export(t_s_cmd *cmd)
{
	char	**tmp;
	int i;

	i = 0;
	tmp = cmd->big_cmd->env;
	sort_tab(tmp);
	while (tmp[i])
	{
		print_export(tmp[i]);
		i++;
	}
}
