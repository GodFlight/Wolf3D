/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jtoc_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 16:23:00 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/19 16:23:00 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libjtoc.h"

size_t	jtoc_get_child_count(t_jnode *n)
{
	size_t	res;

	res = 0;
	n = n->down;
	while (n)
	{
		n = n->down;
		++res;
	}
	return (res);
}

char	*jtoc_ftoa(float n, int flen)
{
	int		len;
	char	*res;

	len = (n < 0 ? 2 : 1) + FLOAT_BUF_SIZE + flen;
	if (!(res = (char *)ft_memalloc(len)) ||
		!(gcvt(n, 10, res)))
		return (NULL);
	return (res);
}