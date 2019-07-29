/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.distance                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 17:32:53 by rkeli             #+#    #+#             */
/*   Updated: 2019/06/18 14:15:23 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char			*make_string(char *str, int n, int cnb)
{
	int		rmb_n;

	rmb_n = 0;
	str[cnb] = '\0';
	if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	while (cnb > 0 && n > 0)
	{
		rmb_n = n % 10;
		cnb--;
		str[cnb] = rmb_n + '0';
		n = n / 10;
	}
	return (str);
}

static int			count_numb(int n)
{
	int		i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char				*ft_itoa(int n)
{
	char	*str;
	int		cnb;

	if (n == 0)
		return (ft_strdup("0"));
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	cnb = count_numb(n);
	if (!(str = (char*)malloc(sizeof(char) * (cnb + 1))))
		return (0);
	str = make_string(str, n, cnb);
	return (str);
}
