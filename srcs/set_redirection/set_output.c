/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:45:10 by apommier          #+#    #+#             */
/*   Updated: 2022/04/19 14:51:17 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*set_output(char *line, t_s_cmd *cmd, int index)
{
	int	i;
	int	word_index;

	word_index = 0;
	i = index;
	i++;
	if (line[i] == '>')
		i++;
	word_index = i;
	while (line[i] == ' ' && line[i])
		i++;
	while ((line[i] != ' ' && line[i] != '<' && line[i] != '>') && line[i])
		i++;
	cmd->outfile = get_word(line, index);
	cmd->outfile = set_var(cmd->big_cmd, cmd->outfile);
	line = cut_str(line, index, i);
	return (line);
}

char	*ft_output(char *line, t_s_cmd *cmd, int index)
{
	int		i;
	char	next;

	i = index;
	next = next_space(line, i + 1);
	if (line[i + 1] == '>')
	{
		cmd->in_type = 1;
		next = next_space(line, i + 2);
	}
	else
		cmd->in_type = 0;
	if (next == '<' || next == '>' || !next)
		return (0);
	line = set_output(line, cmd, i);
	return (line);
}
