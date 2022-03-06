/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <alexpomms@student.42.fr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/11 00:10:12 by apommier          #+#    #+#             */
/*   Updated: 2020/12/13 22:37:30 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*begin;

	begin = 0;
	while (lst)
	{
		new = ft_lstnew(f(lst->nbr));
		if (!new)
		{
			ft_lstclear(&begin, *del);
			return (0);
		}
		ft_lstadd_back(&begin, new);
		lst = lst->next;
	}
	return (begin);
}
