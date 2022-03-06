/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadjigui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 15:05:04 by sadjigui          #+#    #+#             */
/*   Updated: 2021/06/07 11:37:08 by sadjigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*yup;

	if (alst)
	{
		if (*alst)
		{
			yup = ft_lstlast(*alst);
			yup->next = new;
		}
		else
			*alst = new;
	}
}
