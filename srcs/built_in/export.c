/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 23:26:59 by sadjigui          #+#    #+#             */
/*   Updated: 2022/04/09 04:59:38 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	check_variable(char *variable)
{
	int	i;

	i = 0;
	if (!ft_isalpha(variable[i]) && variable[i] != '_')
		return(1);
	i++;
	while(variable[i] && variable[i] != '=')
	{
		if(!ft_isalnum(variable[i]) && variable[i] != '_')
			return(1);
		i++;
	}
	return(0);
}

// char	*check_value(char *value)
// {
// 	int	i;
// 	char *dest;

// 	i = find_len(value, 0, '=') + 1;
// 	if (value[i] == '"')
// 	{
// 		printf("wait\n");
// 		dest = ft_strdup(" ");
// 		// dest = define_double_quotes(value);
// 	}
// 	else{
// 		dest = ft_substr(value, 0, find_len(value, 0, ' '));
// 		// printf("brrrrrrr------\n");

// 	}
// 	return (dest);
// }

int	ft_export_variable(t_s_cmd *cmd, char *variable)
{
	char *dest;
	char *unset;

	if (check_variable(variable) == 1)
	{
		ft_putstr_fd("Minishell: export: `", 2);
		ft_putstr_fd(variable, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	dest = ft_strdup(variable);
	unset = ft_substr(dest, 0, find_len(dest, 0, '='));
	if (find_it(cmd->big_cmd->env, unset) != -1)
	{
		cmd->big_cmd->env[find_it(cmd->big_cmd->env, unset)] = dest;
		free(unset);
		return (0);
	}
	register_env(cmd, dest);
	if (dest)
		free(dest);
	if (unset)
		free(unset);
	return (0);
}

void	ft_export(t_s_cmd *cmd)
{
	int	i;
	int j;

	i = 1;
	j = 0;
	if (!cmd->args[i])
		lone_export(cmd);
	else if (cmd->args[i])
		while (cmd->args[i])
		{
			j = ft_export_variable(cmd, cmd->args[i]);
			i++;
		}
}
