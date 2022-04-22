/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:02:01 by apommier          #+#    #+#             */
/*   Updated: 2022/04/22 13:01:30 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*del_char(char *str, int *index)
{
	char	*swap;
	char	*swap2;

	swap = 0;
	swap = ft_strdup(str + *index + 1);
	str[*index] = 0;
	swap2 = str;
	str = ft_strjoin(str, swap);
	free(swap2);
	free(swap);
	return (str);
}

char	*get_var(t_cmd	*cmd, char *var_name)
{
	char	*line;
	char	**split_line;
	int		index;

	line = 0;
	if (!ft_strcmp(var_name, "?"))
		return (ft_itoa(cmd->err_var));
	index = find_it(cmd->env, var_name);
	if (index >= 0)
	{
		line = cmd->env[index];
		split_line = ft_split(line, '=');
		if (split_line[1])
			line = ft_strdup(split_line[1]);
		else
			return (0);
		free_double(split_line);
	}
	return (line);
}

char	*change_var(t_cmd *big_cmd, char *cmd, int *index)
{
	int		i;
	char	*ret;

	i = *index + 1;
	while (cmd[i] && (ft_isalnum(cmd[i]) || cmd[i] == '_'
			|| cmd[i] == '?' || cmd[i] == '$'))
		i++;
	if (i == *index + 1)
	{
		(*index)++;
		ret = ft_strdup(cmd);
		free(cmd);
		return (ret);
	}
	ret = find_var(big_cmd, cmd, i, index);
	return (ret);
}

char	*check_quote(t_cmd *big_cmd, char *cmd, int *i)
{
	cmd = del_char(cmd, i);
	if (cmd[*i])
	{
		while (cmd[*i] != '"')
		{	
			if (cmd[*i] == '$')
				cmd = change_var(big_cmd, cmd, i);
			(*i)++;
		}
		cmd = del_char(cmd, i);
	}
	return (cmd);
}

char	*set_var(t_cmd *big_cmd, char *cmd)
{
	int	i;

	i = 0;
	while (cmd[0] && cmd[i])
	{
		if (cmd[i] == '\'')
		{	
			cmd = del_char(cmd, &i);
			if (cmd[i])
			{
				while (cmd[i] != '\'')
					i++;
				cmd = del_char(cmd, &i);
			}
		}
		else if (cmd[i] == '"')
			cmd = check_quote(big_cmd, cmd, &i);
		else if (cmd[i] == '$')
			cmd = change_var(big_cmd, cmd, &i);
		else
			i++;
	}
	return (cmd);
}
