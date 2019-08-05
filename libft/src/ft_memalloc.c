/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.distance                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 17:32:11 by rkeli             #+#    #+#             */
/*   Updated: 2019/06/18 14:15:23 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	void *rs;

	if (size == (size_t)(-1))
		return (0);
	if (!(rs = malloc(size)))
		return (NULL);
	else
	{
		ft_bzero(rs, size);
		return (rs);
	}
}
