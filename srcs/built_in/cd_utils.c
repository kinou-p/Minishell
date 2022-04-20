/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadjigui <sadjigui@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 15:35:02 by sadjigui          #+#    #+#             */
/*   Updated: 2022/04/20 16:07:58 by sadjigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	change_oldpwd(char **env, int old_pwd, int pwd, char *p)
{
	if (find_it(env, "PWD") != -1)
	{
		if (find_it(env, "OLDPWD") != -1)
		{
			free(env[old_pwd]);
			env[old_pwd] = ft_strjoin("OLD", env[pwd]);
		}
		free(env[pwd]);
		env[pwd] = ft_strjoin("PWD=", p);
	}
}
