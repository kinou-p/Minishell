/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_var.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:02:01 by apommier          #+#    #+#             */
/*   Updated: 2022/04/19 19:55:04 by apommier         ###   ########.fr       */
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
	char	*swap;
	char	*swap2;
	char	*ret;
	char	*var;

	i = *index + 1;
	while (cmd[i] && (ft_isalnum(cmd[i]) || cmd[i] == '_' || cmd[i] == '?'))
		i++;
	swap = ft_substr(cmd, *index + 1, i - *index - 1);
	var = get_var(big_cmd, swap);
	free(swap);
	swap2 = ft_strdup(cmd + i);
	cmd[*index] = 0;
	ret = ft_strjoin(cmd, var);
	free(cmd);
	*index += ft_strlen(var) - 1;
	free(var);
	var = ret;
	ret = ft_strjoin(ret, swap2);
	free(var);
	free(swap2);
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
	while (cmd[i])
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
