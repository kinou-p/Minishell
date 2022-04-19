/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 23:58:21 by apommier          #+#    #+#             */
/*   Updated: 2022/04/19 07:09:58 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_in_quote(char *str, int index)
{
	int i;
	int	open;

	open = 0;
	i = 0;
	while (i < index)
	{
		if (str[i] == '\'' && open != 2)
		{
			if (!open)
				open = 1;
			else if (open == 1)
				open = 0;
		}
		else if (str[i] == '"' && open != 1)
		{
			if (!open)
				open = 2;
			else if (open == 2)
				open = 0;
		}
		i++;
	}
	return (open);
}

int	is_quote_good(char *str)
{
	int simple_quote;
	int	double_quote;
	int	open;
	int	i;

	i = 0;
	open = 0;
	simple_quote = 0;
	double_quote = 0;
	while (str[i])
	{
		if (str[i] == '\'' && open != 2)
		{
			if (!open)
				open = 1;
			else if (open == 1)
				open = 0;
			simple_quote++;
		}
		else if (str[i] == '"' && open != 1)
		{
			if (!open)
				open = 2;
			else if (open == 2)
				open = 0;
			double_quote++;
		}
		i++;
	}
	if (simple_quote % 2 || double_quote % 2)
	{
		printf("bad quote\n");
		return (0); 
	}
	//printf("good_quote\n");
	return (1);
}

char	*del_char(char *str, int *index)
{
	char *swap;
	char *swap2;

	swap = 0;
	//printf("index= %d\n", *index);
	//printf("before del char -%s-\n", str);
//	if (ft_strlen(str) > 1)
		swap = ft_strdup(str + *index + 1);
//	else 
//		swap = 
	//printf("in del char after dup -%s-\n", swap);
//	if (str)
		str[*index] = 0;
	swap2 = str;
	str = ft_strjoin(str, swap);
	//if (*index)
	//	(*index)--;
	//printf("after del char -%s-\n", str);
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
	//printf("var_name -%s-\n", var_name);
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
	
	//printf("get_var line= -%s-\n", line);
	return (line);
}

char	*change_var(t_cmd *big_cmd, char *cmd, int *index)
{
	int	i;
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
	free(swap2);
	return (ret);
}

char	*set_var(t_cmd *big_cmd, char *cmd)
{
	int i;
	char *del;

	//printf("set_var\n");
	i = 0;
	while (cmd[i])
	{
		//printf("char= -%c-\n", cmd[i]);
		if (cmd[i] == '\'')
		{	
			cmd = del_char(cmd, &i);
			//printf("i= %d char= -%c- str= -%s-\n", i, cmd[i], cmd);
			if (cmd[i])
			{
				while (cmd[i] != '\'')
				{
					i++;
				}
				cmd = del_char(cmd, &i);
			}
		}
		else if (cmd[i] == '"')
		{
			cmd = del_char(cmd, &i);
			//printf("i= %d char= -%c-\n", i, cmd[i]);
			if (cmd[i])
			{
				while (cmd[i] != '"')
				{	
					if (cmd[i] == '$')
					{
						cmd = change_var(big_cmd, cmd, &i);	
						//printf("i= %d et cmd= -%s-\n", i, cmd);
					}
					i++;
				}
				del = cmd;
				cmd = del_char(cmd, &i);
				free(cmd);
			}
			
			//i++;
		}
		else if (cmd[i] == '$')
			cmd = change_var(big_cmd, cmd, &i);
		else
			i++;
	}
	//printf("after all -%s-\n", cmd);
	return (cmd);
}

int parse_quote(t_cmd *cmd)
{
	int i;
	int j;
	char	*swap;
	
	i = 0;
	while (cmd->s_cmds[i])
	{
		j = -1;
		while (cmd->s_cmds[i]->args[++j])
		{
			swap = cmd->s_cmds[i]->args[j];
			cmd->s_cmds[i]->args[j] = set_var(cmd, cmd->s_cmds[i]->args[j]);
			if (cmd->s_cmds[i]->args[j] != swap)
				free(swap);
		}
		//printf("parse quote -%s-\n", cmd->s_cmds[i]->args[0]);
		if (!is_builtin(cmd->s_cmds[i]->args[0]))
			cmd->s_cmds[i]->cmd = get_command(cmd->s_cmds[i]->args, cmd->path);
		else
			cmd->s_cmds[i]->cmd = cmd->s_cmds[i]->args[0];
		if (!cmd->s_cmds[i]->cmd)
			cmd->s_cmds[i]->cmd = ft_strdup(cmd->s_cmds[i]->args[0]);
		else
			cmd->s_cmds[i]->cmd = ft_strdup(cmd->s_cmds[i]->cmd);
		//free(cmd->s_cmds[i]->cmd);
		//cmd->s_cmds[i]->cmd = ft_strdup(cmd->s_cmds[i]->args[0]);
		//printf("parse quote -%s-\n", cmd->s_cmds[i]->cmd);
		i++;
	}
	return (0);
}