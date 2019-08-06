/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.distance                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 21:10:52 by rkeli             #+#    #+#             */
/*   Updated: 2019/06/18 14:15:23 by rkeli            ###   ########.fr       */
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
