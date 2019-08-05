/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.distance                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:20:07 by rkeli             #+#    #+#             */
/*   Updated: 2019/06/18 14:15:23 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	int			i;
	char		*s1;
	const char	*s2;

	if (!dst && !src)
		return (NULL);
	s1 = (char*)dst;
	s2 = (const char *)src;
	i = 0;
	while (n-- > 0)
	{
		s1[i] = s2[i];
		i++;
	}
	return ((void*)dst);
}
