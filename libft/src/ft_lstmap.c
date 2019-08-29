/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 23:14:49 by rkeli             #+#    #+#             */
/*   Updated: 2019/08/28 23:48:08 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new_list;
	t_list *makson;
	t_list *seg;

	if (!lst || !f)
		return (NULL);
	new_list = f(lst);
	makson = new_list;
	lst = lst->next;
	while (lst)
	{
		if ((seg = f(lst)))
		{
			new_list->next = seg;
			new_list = new_list->next;
		}
		else
		{
			ft_lstnormdel(new_list);
			return (NULL);
		}
		lst = lst->next;
	}
	return (makson);
}
