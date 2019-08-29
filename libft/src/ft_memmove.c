/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 23:15:51 by rkeli             #+#    #+#             */
/*   Updated: 2019/08/28 23:48:08 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void						*ft_memmove(void *dst, void *src, size_t n)
{
	unsigned char	*s1;
	size_t			i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	s1 = (unsigned char*)dst;
	if (dst > src)
	{
		i = n - 1;
		while (n-- > 0)
		{
			s1[i] = ((unsigned char *)src)[i];
			i--;
		}
	}
	else
	{
		while (n-- > 0)
		{
			s1[i] = ((unsigned char *)src)[i];
			i++;
		}
	}
	return ((void*)s1);
}
