/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.distance                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 13:04:27 by rkeli             #+#    #+#             */
/*   Updated: 2019/06/18 14:15:23 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*link;

	if (!(link = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	if (content == 0)
	{
		link->content = NULL;
		link->content_size = 0;
	}
	else
	{
		if (!(link->content = malloc(content_size)))
		{
			free(link);
			return (NULL);
		}
		ft_memcpy(link->content, content, content_size);
		link->content_size = content_size;
	}
	link->next = NULL;
	return (link);
}
