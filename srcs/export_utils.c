/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadjigui <sadjigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 23:26:59 by sadjigui          #+#    #+#             */
/*   Updated: 2022/03/01 18:33:45 by sadjigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/mini.h"

int	check_variable(char *variable)
{
	int	i;

	i = 0;
	if (!ft_isalpha(variable[i]))
		return(0);
	i++;
	while(variable[i])
	{
		printf("%c\n", variable[i]);
		if(!ft_isalnum(variable[i]))
			return(0);
		i++;
	}
	return(1);
}

char	*define_value(char *value)
{
	int		i;
	char	*new_value;

	i = 0;
	if (value[i] == ' ')
	{
		new_value = ft_strdup("");
	}
	else
	{
		printf("%s\n", value);
		while (value[i])
		{
			printf("%d\n", i);
			i++;
		}
		new_value = ft_substr(value, 0, i);
	}
	return (new_value);
}

char	*check_value(char *value)
{
	int		i;
	char	*new_value;

	i = 0;
	if (value[0] == '"')
	{
		new_value = NULL;
		printf("jojo\n");
	}
	else
		new_value = define_value(value);
	return(new_value);
}

void	ft_export_variable(t_struct *data, char *variable)
{
	char	*v_v[2];
	int		i;
	char	*tmp;

	i = 0;
	while (variable[i] != '=')
		i++;
	v_v[0] = ft_substr(variable, 1, i - 1);
	i++;
	v_v[1] = ft_substr(variable, i, find_len(variable, i));
	if (check_variable(v_v[0]) == 1)
	{
		tmp = ft_strdup(v_v[1]);
		free(v_v[1]);
		v_v[1] = check_value(tmp);
		register_env(data, v_v);
	}
}
