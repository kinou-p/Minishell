/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/09 23:58:21 by apommier          #+#    #+#             */
/*   Updated: 2022/04/10 21:03:07 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_quote_even(char *str)
{
	int simple_quote;
	int	double_quote;
	int	i;

	i = -1;
	simple_quote = 0;
	double_quote = 0;
	while (str[i++])
	{
		if (str[i] == 39)
			simple_quote++;
		else if (str[i] == 34)
			double_quote++;
	}
	if (simple_quote % 2 || double_quote % 2)
		return (0); 
	return (1);
}

/*int parse_quote(char *str)
{
	
}*/