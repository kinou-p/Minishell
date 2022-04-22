/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:45:10 by apommier          #+#    #+#             */
/*   Updated: 2022/04/22 13:02:24 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*find_var(t_cmd *big_cmd, char *cmd, int i, int *index)
{
	char	*swap;
	char	*swap2;
	char	*ret;
	char	*var;

	swap = ft_substr(cmd, *index + 1, i - *index - 1);
	var = get_var(big_cmd, swap);
	free(swap);
	swap2 = ft_strdup(cmd + i);
	cmd[*index] = 0;
	ret = ft_strjoin(cmd, var);
	free(cmd);
	if (*index > 0)
		*index += ft_strlen(var) - 1;
	free(var);
	var = ret;
	ret = ft_strjoin(ret, swap2);
	free(var);
	free(swap2);
	return (ret);
}

int	check_access_output(t_s_cmd *cmd)
{
	if (!access(cmd->outfile, F_OK) && access(cmd->outfile, W_OK))
	{
		g_var = 1;
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(cmd->outfile, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		free(cmd->outfile);
		return (0);
	}
	return (1);
}

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
	if (cmd->outfile)
		free(cmd->outfile);
	cmd->outfile = get_word(line, index);
	cmd->outfile = set_var(cmd->big_cmd, cmd->outfile);
	if (!check_access_output(cmd))
	{
		free(line);
		return (0);
	}
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
		return (error_parsing(line));
	line = set_output(line, cmd, i);
	return (line);
}
