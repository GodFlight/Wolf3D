/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 23:15:36 by rkeli             #+#    #+#             */
/*   Updated: 2019/08/28 23:48:08 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *arr1, const void *arr2, size_t n)
{
	const unsigned char		*mass1;
	const unsigned char		*mass2;
	int						i;

	i = 0;
	mass1 = (const unsigned char*)arr1;
	mass2 = (const unsigned char*)arr2;
	while (n-- > 0)
	{
		if (mass1[i] != mass2[i])
			return (mass1[i] - mass2[i]);
		i++;
	}
	return (0);
}
