/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 15:19:42 by apommier          #+#    #+#             */
/*   Updated: 2022/03/08 15:19:47 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	double_size(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

s_cmds	*set_s_cmd(char *line)
{
	t_s_cmd	s_cmd;
	tmp		**split_line;
	int	i;

	i = 0;
	split_line = ft_split(line, ' ');
	s_cmd.cmd = split_line[i];
	
}

t_cmd *split_cmd(t_cmd *cmd, char **cmds)
{
	int	i;

	i = 0;
	while (cmd->s_cmds[i])
	{
		cmd->s_cmds[i] = set_s_cmd(cmds[i])
		i++;
	}
	return (cmd);
}

t_cmd	*set_cmd(char *input)
{
	t_cmd	*cmd;
	char	**cmds;

	cmds = ft_split(input, '|');
	if (!cmds)
		return (0);
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (0);
	cmd->s_cmds = malloc(sizeof(t_s_cmds) * double_size(cmds));
	if (!cmd->s_cmds)
		return (0);
	cmd->nb_s_cmd = double_size(cmds);
	cmd = split_cmd(cmd, cmds); //split each cmd into args in s_cmd
}