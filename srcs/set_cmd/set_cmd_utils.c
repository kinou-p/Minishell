/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cmd_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 16:53:13 by apommier          #+#    #+#             */
/*   Updated: 2022/04/22 11:43:15 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*error_parsing(char *to_free)
{
	g_var = 2;
	if (to_free)
		free(to_free);
	ft_putstr_fd("Minishell: error while parsing command\n", 2);
	return (0);
}
