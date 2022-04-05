/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/11 20:52:56 by sadjigui          #+#    #+#             */
/*   Updated: 2022/04/05 17:30:24 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	jump_space(char *str, int i)
{
	int	j;

	j = i;
	while (str[j] == ' ')
		j++;
	return (j);
}

void	print_value(char *str, char *input)
{
	(void)input;
	int i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	i++;
	ft_putstr_fd(str + i, 0);
	/*while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}*/
}

// void	print_rest(char *input, char *str, int j)
// {
// 	int	i;
//
// 	i = 0;
// 	j -= 1;
// 	while (input[j++])
// 		printf("%c", input[j]);
// 	printf("\n");
// 	while (input[j] && input[j] == str[i])
// 	{
// 		i++;
// 		j++;
// 	}
// 	printf("str == %s\n", str);
// 	if (input[j] != '\0')
// 	{
// 		j = jump_space(input, j);
// 		if (input[j] != '\0')
// 			while(input[j])
// 			{
// 				ft_putchar(input[j]);
// 				j++;
// 			}
// 		else
// 			return;
// 	}
// 	else
// 		return ;
// }

void	find_for_print(t_s_cmd *cmd, char *input)
{
	char *str;
	// char *tmp;
	int	i;
	int x;

	i = 0;
	// j = j + 1;
	// tmp = ft_substr(input, j, find_len(input, j, 32));
	// printf("%c\n", input[j]);
	str = ft_strjoin(input, "=");
	x = ft_strlen(str);
	// printf("%d\n", x);
	while (cmd->env[i])
	{
		if (ft_strncmp(cmd->env[i], str, x) == 0)
		{
			// printf("%s\n", cmd->env[i]);
			break ;
		}

		i++;
	}
	if (cmd->env[i] != NULL)
	{
		print_value(cmd->env[i], input);
		// print_rest(input, tmp, j);
	}
}

int	dollar_or_not(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

void	find_value(t_s_cmd *cmd, char *str)
{
	// int i;
	//
	// i = 0;
	while (*str)
	{
		if (*str == '$')
			break ;
		printf("%c", *str);
		str++;
	}
	str++;
	find_for_print(cmd, str);
}

void	ft_echo(t_s_cmd *d)
{
	int	i;
	int j;
	int	is_option;

	j = 0;
	i = 1;
	is_option = 0;
	if (d->args[i] && ft_strcmp(d->args[i], "-n") == 0)
	{
		is_option = 1;
		i++;
	}
	if (d->args[i])
		while (d->args[i])
		{
			if (dollar_or_not(d->args[i]) == 1)
				find_value(d, d->args[i]);
			else
				printf("%s", d->args[i]);
			if (d->args[i + 1] != NULL)
			printf("\n");
			i++;
		}
	// else
	// 	my_putstr(input, i);
	if (is_option == 0)
		printf("\n");
}
