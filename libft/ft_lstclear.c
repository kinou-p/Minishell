/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sadjigui <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/03 16:03:18 by sadjigui          #+#    #+#             */
/*   Updated: 2021/06/07 12:13:31 by sadjigui         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*nap;

	if (!lst || !del || !*lst)
		return ;
	while (lst && *lst)
	{
		nap = (*lst)->next;
		ft_lstdelone(*lst, del);
		*lst = nap;
	}
}
