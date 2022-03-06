/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadjigui <sadjigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 17:12:52 by sadjigui          #+#    #+#             */
/*   Updated: 2022/03/06 15:33:06 by sadjigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	print_env(t_struct *data)
{
	int i;

	i = 0;
	while (data->envy[i])
	{
		printf("%s\n", data->envy[i]);
		i++;
	}
	// printf("ici\n");
}

void	lexer(char *input, t_struct *data)
{
	if (ft_strcmp(input, "exit") == 0)
		ft_exit(data);
	if (ft_strcmp(input, "env") == 0)
		print_env(data);
	if (ft_strncmp(input, "export", ft_strlen("export")) == 0)
		ft_export(input, data);
}
