/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/09 15:18:58 by apommier          #+#    #+#             */
/*   Updated: 2022/03/09 20:43:42 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void set_redirection(t_s_cmd *cmd, char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	if (!line[i])
		return (0);
	while (line[i] && (line[i] != '<' || line[i] != '<'))
		i++;
	if (!line[i])
		return (0);
}