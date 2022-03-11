/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:18:58 by apommier          #+#    #+#             */
/*   Updated: 2022/03/11 23:24:09 by apommier         ###   ########.fr       */
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

	//printf("before cut :%s\n", str);
	del = str;
	swap = ft_strjoin(&str[end], 0);
	//printf("&str[start] :%s\n", &str[start]);
	str[start] = 0;
	str = ft_strjoin(str, swap);
	free(del);
	free(swap);
	//printf("after cut :%s\n", str);
	return (str);
}

char	*get_word(char *str, int start, int end)
{
	char *new;
	char *swap;
	int		i;

	i = 0;
	//printf("str de get_word %s\n", str);
	while (str[start + i] == '<' || str[start + i] == '>')
		i++;
	while (str[start + i] == ' ')
		i++;
	printf("srt= %s\n", &str[start + i]);
	new = ft_strjoin(&str[start + i], 0);
	printf("char= %c\n",new[end - start - i]);
	printf("char str= %s end=%d start=%d out=%d\n", &new[0], end, start, end - start - i - 1);
	i = 0;
	while (new[i] && new[i] != ' ' && new[i] != '>' && new[i] != '<')
		i++;
	new[i] = 0;
	//new[end - start - start] = 0;
	//swap = new;
	//new = ft_strjoin(&new[i], 0);
	//free(swap);
	printf("get word= %s\n", new);
	return (new);
}

void	error_redirect(void)
{
	printf("ERROR: bad syntax\n");
	exit(1);
}

char	*set_input(char *line, t_s_cmd *cmd, int index)
{
	int	i;
	int word_index;

	//printf("&line[index] :%s\n", &line[index]);
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
	cmd->infile = get_word(line, word_index, i);
	line = cut_str(line, index, i);
	return (line);
}

char *set_output(char *line, t_s_cmd *cmd, int index)
{
	int	i;
	int word_index;

	//printf("&line[index] :%s\n", &line[index]);
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
	cmd->outfile = get_word(line, index, i);
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
		error_redirect();
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
		error_redirect();
	line = set_output(line, cmd, i);
	return (line);
}

void	set_file(char *file)
{
	int fd;

	fd = open(file, O_CREAT | O_TRUNC);
	if (fd)
		close(fd);
	if (fd == -1)
		error_redirect();
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
	//printf("size= %d\n", size);
	ret = ft_calloc(size + 2, sizeof(char*));
	if (!ret)
	{
	//	if (tab)
	//		free_double(tab);
		return (0);
	}
	while (tab && tab[i])
	{
		printf("tab[i]= %s\n", tab[i]);
		ret[i] = ft_strjoin(tab[i], 0);
		i++;
	}
	ret[i] = line;
	ret[i + 1] = 0;
	//if (tab)
	//	free_double(tab);
	return(ret);
}

void	wait_prompt(t_s_cmd *cmd)
{
	char	*input;
	char	**history;

	history = 0;
	input = 0;
	while (ft_strcmp(input, cmd->infile))
	{
		input = readline("> ");
		history = add_line(history, input);
		print_double(history);
	}
	//print_double(history);
	//free_double(history);
	free(input);
	free(cmd->infile);
	cmd->infile = 0;
}

char	*set_redirection(t_s_cmd *cmd, char *line)
{
	int i;

	i = 0;
	//printf("enter redirection\n");
	while (line[i])
	{
		if(line[i] == '<')
		{
			line = ft_input(line, cmd, i);
			if (cmd->in_type == 1)
				wait_prompt(cmd);
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