/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 23:58:21 by apommier          #+#    #+#             */
/*   Updated: 2022/04/11 16:30:09 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_quote_even(char *str)
{
	int simple_quote;
	int	double_quote;
	int	i;

	i = -1;
	simple_quote = 0;
	double_quote = 0;
	while (str[i++])
	{
		if (str[i] == 39)
			simple_quote++;
		else if (str[i] == 34)
			double_quote++;
	}
	if (simple_quote % 2 || double_quote % 2)
		return (0); 
	return (1);
}

void set_var(char *cmd)
{
	int i;
	int simple_quote;
	int double_quote;
	int first_open;

	i = 0;
	first_open = 0;
	simple_quote = 0;
	double_quote = 0;
	while (cmd[i])
	{
		if (cmd[i] == '\'')
		{	
			if (simple_quote)
				simple_quote = 0;
			else
				simple_quote = 1;	 
		}
		else if (cmd[i] == '"')
		{
			if (double_quote)
				double_quote = 0;
			else
				double_quote = 1;
		}
		else if (cmd[i] == '$' && !simple_quote)
				i = change_var(cmd, i);
		i++;
	}
}

int parse_quote(char **cmds)
{
	int i;

	i = 0;
	while (cmds[i])
	{
		set_var(cmds[i]);
		i++;
	}
}