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

void	ft_export_variable(t_s_cmd *cmd, char *variable)
{
	char *dest;
	char *unset;
	int	i;

	i = 0;
	if (check_variable(variable) == 1)
	{
		ft_putstr_fd("Minishell: export: ", 2);
		ft_putstr_fd(variable, 2);
		ft_putstr_fd(": not a valid identifier\n", 2);
		// 1
		return ;
	}
	// dest = check_value(variable);
	dest = ft_strdup(variable);
	unset = ft_substr(dest, 0, find_len(dest, 0, '='));
	while (cmd->big_cmd->env[i] != NULL)
	{
		if (ft_strncmp(unset, cmd->big_cmd->env[i], ft_strlen(unset)) == 0)
		{
			free(cmd->big_cmd->env[i]);
			cmd->big_cmd->env[i] = dest;
			return ;
		}
		i++;
	}
	register_env(cmd, dest);
	if (dest)
		free(dest);
	if (unset)
		free(unset);
}

void	ft_export(t_s_cmd *cmd)
{
	int	i;

	i = 1;
	if (!cmd->args[i])
		lone_export(cmd);
	else if (cmd->args[i])
		while (cmd->args[i])
		{
			ft_export_variable(cmd, cmd->args[i]);
			i++;
		}
}
