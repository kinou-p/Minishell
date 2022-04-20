/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:18:58 by apommier          #+#    #+#             */
/*   Updated: 2022/04/20 13:52:56 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*get_word(char *str, int start)
{
	char	*new;
	int		i;

	i = 0;
	while (str[start + i] == '<' || str[start + i] == '>')
		i++;
	while (str[start + i] == ' ')
		i++;
	new = ft_strjoin(&str[start + i], 0);
	i = 0;
	while (new[i] && new[i] != ' ' && new[i] != '>' && new[i] != '<')
		i++;
	new[i] = 0;
	return (new);
}

int	set_file(char *file, int type)
{
	int	fd;
	
	if (type)
		fd = open(file, O_APPEND | O_CREAT, 0644);
	else
		fd = open(file, O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (0);
	}
	if (fd)
		close(fd);
	return (1);
}

char	**add_line(char **tab, char *line)
{
	int		size;
	char	**ret;
	int		i;

	i = 0;
	size = 0;
	ret = 0;
	if (tab)
		size = double_size(tab);
	ret = ft_calloc(size + 2, sizeof(char *));
	if (!ret)
		return (0);
	while (tab && tab[i])
	{
		ret[i] = ft_strjoin(tab[i], 0);
		i++;
	}
	ret[i] = ft_strjoin(line, 0);
	ret[i + 1] = 0;
	if (tab)
		free_double(tab);
	return (ret);
}

int	set_redirect_in(t_s_cmd *cmd, char **line, int *i, int index)
{
	if (!is_in_quote(*line, *i))
	{
		*line = ft_input(*line, cmd, *i);
		if (!(*line))
			return (error_parsing());
		if (cmd->in_type == 1)
		{
			if (wait_prompt(cmd, index, 0, 0) == -1)
			{
				free(*line);
				return (0);
			}
		}
		*i = 0;
	}
	return (1);
}

char	*set_redirection(t_s_cmd *cmd, char *line, int index, int i)
{
	while (line[i])
	{
		if (line[i] == '<')
		{
			if (!set_redirect_in(cmd, &line, &i, index))
				return (0);
		}
		else if (line[i] == '>')
		{
			if (!is_in_quote(line, i))
			{
				line = ft_output(line, cmd, i);
				if (!set_file(cmd->outfile, cmd->in_type))
					return (0);
				i = 0;
			}
		}
		if (line[i] && (line[i] == '<' || line[i] == '>')
			&& is_in_quote(line, i))
			i++;
		else if (line[i] && line[i] != '<' && line[i] != '>')
			i++;
	}
	return (line);
}
