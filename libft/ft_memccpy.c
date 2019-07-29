/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.distance                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:46:40 by rkeli             #+#    #+#             */
/*   Updated: 2019/06/18 14:15:23 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	int				i;
	unsigned char	*s1;
	unsigned char	*s2;
	unsigned char	c1;

	i = 0;
	s1 = (unsigned char*)dst;
	s2 = (unsigned char*)src;
	c1 = (unsigned char)c;
	while (n-- > 0)
	{
		s1[i] = s2[i];
		if (s2[i] == c1)
		{
			s1[i] = s2[i];
			return ((void*)s1 + i + 1);
		}
		i++;
	}
	return (NULL);
}
