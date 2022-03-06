/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kinou <alexpomms@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/23 07:55:17 by kinou             #+#    #+#             */
/*   Updated: 2021/11/01 10:21:35 by kinou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_free(char *save, int *end)
{
	if (!*end)
	{
		free(save);
		free(end);
		return (0);
	}
	free(end);
	return (save);
}

char	*set_line(char *line, char *save)
{
	int		i;

	i = 0;
	line = ft_strjoin(save, 0);
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
	{
		while (line[i++])
			line[i] = '\0';
	}
	return (line);
}

char	*set_save(char *save)
{
	char	*delete;
	int		i;

	i = 0;
	delete = save;
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] != '\n')
		i = 0;
	save = ft_strjoin((save + i + 1), 0);
	free(delete);
	return (save);
}

char	*next_line(char *save, int *end, int fd)
{
	char	*delete;
	char	*dest;

	while (!ft_strchr(save, '\n') && *end > 0)
	{
		dest = ft_calloc(1, 1 + 1);
		*end = read(fd, dest, 1);
		delete = save;
		save = ft_strjoin(save, dest);
		free(delete);
		free(dest);
	}
	return (save);
}

char	*get_next_line(int fd)
{
	static char	*save = NULL;
	int			*end;
	char		*line;

	line = 0;
	if (fd < 0)
		return (0);
	end = malloc(sizeof(int *));
	*end = 1;
	if (save == NULL)
		save = ft_calloc(1, 1);
	save = next_line(save, end, fd);
	line = set_line(line, save);
	if (ft_strlen(line) > 0)
	{
		save = set_save(save);
		save = ft_free(save, end);
		return (line);
	}
	free(line);
	save = ft_free(save, end);
	return (0);
}
