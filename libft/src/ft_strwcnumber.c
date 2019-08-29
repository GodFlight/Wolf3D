/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strwcnumber.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/22 20:49:47 by rkeli             #+#    #+#             */
/*   Updated: 2019/08/28 23:48:08 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

size_t		ft_strwcnumber(const char *s, int c)
{
	size_t a;

	a = 0;
	if (!s)
		return (0);
	while (*s == (unsigned char)c)
		s++;
	while (*s)
	{
		a++;
		while (*s != (unsigned char)c && *s != '\0')
			s++;
		while (*s == (unsigned char)c)
			s++;
		if (*s == '\0')
			return (a);
	}
	return (0);
}
