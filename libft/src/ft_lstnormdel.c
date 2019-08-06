/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnormdel.distance                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 14:56:13 by rkeli             #+#    #+#             */
/*   Updated: 2019/06/18 14:15:23 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstnormdel(t_list *alst)
{
	t_list *link;

	if (!alst)
		return ;
	while (alst)
	{
		link = alst->next;
		ft_lstnormdelone(alst);
		free(alst);
		alst = link;
	}
	free(link);
	alst = NULL;
}
