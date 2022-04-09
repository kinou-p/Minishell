/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:18:58 by apommier          #+#    #+#             */
/*   Updated: 2022/04/09 21:05:43 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	next_space(char *str, int i)
{
	i++;
	while (str[i] == ' ')
		i++;
	return (str[i]);
}

char	*cut_str(char *str, int start, int end)
{
	char	*swap;
	char	*del;

	del = str;
	swap = ft_strjoin(&str[end], 0);
	str[start] = 0;
	str = ft_strjoin(str, swap);
	free(del);
	free(swap);
	return (str);
}

char	*get_word(char *str, int start)
{
	char *new;
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
	printf("get word= %s\n", new);
	return (new);
}

void	error_redirect(char *str)
{
	printf("error : %s\n", str);
	exit(1);
}

char	*set_input(char *line, t_s_cmd *cmd, int index)
{
	int	i;
	int word_index;

	word_index = 0;
	i = index;
	i++;
	if (line[i] == '<')
		i++;
	word_index = i;
	while (line[i] == ' ' && line[i])
		i++;
	while ((line[i] != ' ' && line[i] != '<' && line[i] != '>') && line[i])
		i++;
	cmd->infile = get_word(line, word_index);
	line = cut_str(line, index, i);
	return (line);
}

char *set_output(char *line, t_s_cmd *cmd, int index)
{
	int	i;
	int word_index;

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
	line = cut_str(line, index, i);
	return (line);
}

//choose type of redirection, check error
char	*ft_input(char *line, t_s_cmd *cmd, int index)
{
	int i;
	char	next;

	i = index;
	next = next_space(line, i);
	if (line[i + 1] == '<')
	{
		cmd->in_type = 1;
		next = next_space(line, i + 1);
	}
	else
		cmd->in_type = 0;
	if (next == '<' || next == '>' || !next)
		error_redirect("problem in ft_input");
	line = set_input(line, cmd, i);
	return (line);
}

char	*ft_output(char *line, t_s_cmd *cmd, int index)
{
	int i;
	char	next;

	i = index;
	next = next_space(line, i);
	if (line[i + 1] == '>')
	{
		cmd->in_type = 1;
		next = next_space(line, i + 1);
	}
	else
		cmd->in_type = 0;
	if (next == '<' || next == '>' || !next)
		error_redirect("problem in ft_output");
	line = set_output(line, cmd, i);
	return (line);
}

void	set_file(char *file)
{
	int fd;

	printf("setfile= %s\n", file);
	fd = open(file, O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		error_redirect("can't set file");
	if (fd)
		close(fd);
}

char	**add_line(char **tab, char *line)
{
	int size;
	char	**ret;
	int		i;

	i = 0;
	size = 0;
	ret = 0;
	if (tab)
		size = double_size(tab);
	ret = ft_calloc(size + 2, sizeof(char*));
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
	return(ret);
}

char	*set_heredoc(int index, char **in)
{
	char	*nbr_file;
	char	*file_name;
	int		fd;
	int		i;

	i = 0;
	if (index)
	{
		nbr_file = ft_itoa(index + 1);
		file_name = ft_strjoin(".heredoc", nbr_file);
	}
	else
		file_name = ft_strjoin(".heredoc", 0);
	fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd > 0)
	{
		print_double_fd(in, fd);
		free_double(in);
	}
	close(fd);
	return (file_name);
}

void	wait_prompt(t_s_cmd *cmd, int index)
{
	char	*input;
	char	**history;

	history = 0;
	input = 0;
	while (ft_strcmp(input, cmd->infile))
	{
		ft_putstr_fd("> ", 0);
		input = get_next_line(0);
		if (!input)
			return ;
		input[ft_strlen(input) - 1] = 0;
		if (ft_strcmp(input, cmd->infile))
			history = add_line(history, input);
	}
	free(input);
	free(cmd->infile);
	cmd->infile = 0;//option?
	cmd->infile = set_heredoc(index, history);
	cmd->in_type = 0;
}

char	*set_redirection(t_s_cmd *cmd, char *line, int index)
{
	int i;

	i = 0;
//	printf("enter redirection\n");
	while (line[i])
	{
		if(line[i] == '<')
		{
			line = ft_input(line, cmd, i);
			if (cmd->in_type == 1)
				wait_prompt(cmd, index);
			i = 0;
		}
		else if(line[i] == '>')
		{
			line = ft_output(line, cmd, i);
			if (cmd->in_type == 0)
				set_file(cmd->outfile);
			i = 0;
		}
		else
			i++;
	}
	return(line);
}