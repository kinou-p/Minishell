/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:18:58 by apommier          #+#    #+#             */
/*   Updated: 2022/04/17 10:25:03 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	next_space(char *str, int i)
{
	//i++;
	while (str[i] == ' ')
		i++;
	return (str[i]);
}

char	*cut_str(char *str, int start, int end)
{
	char	*swap;
	char	*del;

	swap = 0;
	del = str;
	if (str[end])
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
	//printf("get word= %s\n", new);
	return (new);
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
	cmd->infile = get_word(line, index);
	cmd->infile = set_var(cmd->big_cmd, cmd->infile);
	if (access(cmd->infile, R_OK))
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(cmd->infile, 2);
		if (access(cmd->infile, F_OK))
			ft_putstr_fd(": no such file\n", 2);
		else
			ft_putstr_fd(": Permission denied\n", 2);
		return (0);
	}
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
	cmd->outfile = set_var(cmd->big_cmd, cmd->outfile);
	line = cut_str(line, index, i);
	return (line);
}

//choose type of redirection, check error
char	*ft_input(char *line, t_s_cmd *cmd, int index)
{
	int i;
	char	next;

	i = index;
	next = next_space(line, i + 1);
	if (line[i + 1] == '<')
	{
		cmd->in_type = 1;
		next = next_space(line, i + 2);
	}
	else
		cmd->in_type = 0;
	if (next == '<' || next == '>' || !next)
		return (0);
	//printf("line bf set_input -%s-", line);
	line = set_input(line, cmd, i);
	if (!line)
		return (0);
	//printf("line -%s-\n", line);
	return (line);
}

char	*ft_output(char *line, t_s_cmd *cmd, int index)
{
	int i;
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
	//printf("line -%s-\n", line);
	return (line);
}

int	set_file(char *file)
{
	int fd;

	//printf("setfile= %s\n", file);
	fd = open(file, O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
	{
		ft_putstr_fd("Minishell: ", 2);
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		return (0);
	}
	//error_redirect("can't set file");
	if (fd)
		close(fd);
	return (1);
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

/*void	del_heredoc()
{
	
}*/

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

void	sig_heredoc(int num)
{
	num = 0;
	struct	sigaction base;
	
	base.sa_handler = &crtl_c;
	base.sa_flags = 0;
	close(1);
	//printf("sig_heredoc\n");
	if (sigaction(SIGINT, &base, 0) == -1)
	{
		printf("sigaction error2\n");
		return ;
	}
}

int	wait_prompt(t_s_cmd *cmd, int index)
{
	char	*input;
	int		i;
	char	**history;
	char	*in;
	char	*dup;
	struct	sigaction test;
	

	test.sa_handler = &sig_heredoc;
	test.sa_flags = 0;
	

	in = ft_strjoin(cmd->infile, "\n");
	free(cmd->infile);
	cmd->infile = 0;
	if (sigaction(SIGINT, &test, 0) == -1)
	{
		printf("sigaction error\n");
		exit(1);
	}
	//printf("wait_prompt\n");
	history = 0;
	input = 0;
	i = 0;
	while (i == 0 || (input && ft_strlen(input) && ft_strcmp(input, in)))
	{
		i = 1;
		ft_putstr_fd("> ", 0);
		input = get_next_line(0);
		//input = readline("");
		//printf("input= -%s-", input);
		if (!input)
			return (0);
		//input[ft_strlen(input) - 1] = 0;
		if (ft_strcmp(input, in))
		{
			dup = ft_strdup(input);
			dup[ft_strlen(input) - 1] = 0;
			dup = set_var(cmd->big_cmd, dup);
			history = add_line(history, dup);
		}
	}
	free(input);
	//free(cmd->infile);
	//cmd->infile = 0;//option?
	cmd->infile = set_heredoc(index, history);
	cmd->in_type = 0;
	return (1);
}

char	*set_redirection(t_s_cmd *cmd, char *line, int index)
{
	int i;
	
	i= 0;
//	printf("enter redirection\n");
	while (line[i])
	{
		//printf("line[i] i= %d\n", i);
		//printf("-%s-\n", line);
		if(line[i] == '<')
		{
			if (!is_in_quote(line, i))
			{
				line = ft_input(line, cmd, i);
				if (!line)
					return (0);
				if (cmd->in_type == 1)
				{
					if (!wait_prompt(cmd, index))
						return (0);
				}
				i = 0;
			}
		}
		else if(line[i] == '>')
		{
			if (!is_in_quote(line, i))
			{
				line = ft_output(line, cmd, i);
				//if (cmd->in_type == 0)
				if (!set_file(cmd->outfile))
					return (0);
				i = 0;
			}
		}
		if (line[i] && (line[i] == '<' || line[i] == '>') && is_in_quote(line, i))
			i++;
		else if (line[i] && line[i] != '<' && line[i] != '>')
			i++;
	}
	return(line);
}