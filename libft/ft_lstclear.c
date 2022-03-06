/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 19:58:04 by apommier          #+#    #+#             */
/*   Updated: 2022/01/17 11:28:39 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*chr;

	chr = *lst;
	while (*lst)
	{
		chr = (*lst)->next;
		del((*lst)->nbr);
		free(*lst);
		*lst = chr;
	}
	lst = 0;
}
