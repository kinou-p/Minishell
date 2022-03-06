/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstbeforelast.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apommier <apommier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 19:16:55 by apommier          #+#    #+#             */
/*   Updated: 2022/01/17 11:28:22 by apommier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstbeforelast(t_list *lst)
{
	t_list	*save;

	save = 0;
	if (!lst)
		return (0);
	while (lst->next)
	{
		save = lst;
		lst = lst->next;
	}
	return (save);
}
