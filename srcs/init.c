/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadjigui <sadjigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 17:17:01 by sadjigui          #+#    #+#             */
/*   Updated: 2022/03/01 18:39:20 by sadjigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

void	join_variable(t_struct *data, char **v_v, int size)
{
	char *str;
	char *tmp;

	str = ft_strjoin(v_v[0], "=");
	tmp = ft_strdup(str);
	free(str);
	str = ft_strjoin(tmp,v_v[1]);
	data->envy[size] = ft_strdup(str);
	free(str);
	free(tmp);
}

void	register_env(t_struct *data, char **variable)
{
	int		size;
	char	**tmp = NULL;

	// tmp = NULL;
	size = 0;
	while (data->envy[size])
		size++;
	tmp = malloc(sizeof(char *) * size);
	if(!tmp)
		ft_exit(data);
	size = 0;
	while (data->envy[size])
	{
		tmp[size] = ft_strdup(data->envy[size]);
		printf("ici\n");
		size++;
	}
	free_char_tab(data->envy);
	data->envy = malloc(sizeof(char *) * size + 1);
	if (!data->envy)
		ft_exit(data);
	size = 0;
	while (tmp[size])
	{
		data->envy[size] = ft_strdup(tmp[size]);
		size++;
	}
	join_variable(data, variable, size);
}

void	ft_env(t_struct *data, char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	data->envy = malloc(sizeof(char *) * i);
	i = 0;
	while (env[i])
	{
		data->envy[i] = ft_strdup(env[i]);
		i++;
	}

}

void	init_struct(t_struct *data, char **env)
{
	ft_env(data, env);
}
