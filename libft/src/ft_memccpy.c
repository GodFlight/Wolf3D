/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 23:15:25 by rkeli             #+#    #+#             */
/*   Updated: 2019/08/28 23:48:08 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
