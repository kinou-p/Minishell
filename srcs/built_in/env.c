/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 21:09:47 by apommier          #+#    #+#             */
/*   Updated: 2022/04/09 21:10:57 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	print_env(char **tab, int fd)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			if (ft_strchr(tab[i], '='))
			{
				ft_putstr_fd(tab[i], fd);
				ft_putstr_fd("\n", fd);
			}
			i++;
		}
	}
}