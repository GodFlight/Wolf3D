/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 23:14:19 by rkeli             #+#    #+#             */
/*   Updated: 2019/08/28 23:48:08 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(int n, int base)
{
	char	*bs;
	int		tmp;
	char	*res;
	int		i;

	tmp = n;
	i = -1;
	while (tmp > 0)
	{
		tmp /= base;
		i++;
	}
	bs = ft_strdup("0123456789ABCDEF");
	if (!(res = (char*)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	res[i + 1] = '\0';
	while (i >= 0)
	{
		tmp = (n % base);
		res[i] = bs[tmp];
		n /= base;
		i--;
	}
	free(bs);
	return (res);
}
