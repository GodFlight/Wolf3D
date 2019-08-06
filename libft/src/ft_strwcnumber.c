/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strwcnumber.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 20:08:27 by sbecker           #+#    #+#             */
/*   Updated: 2018/12/02 20:46:37 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
