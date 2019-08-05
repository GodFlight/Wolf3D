/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.distance                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/03 16:59:00 by rkeli             #+#    #+#             */
/*   Updated: 2019/06/18 14:15:23 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*skip_something(char *str)
{
	while (*str == ' ' || *str == '\r' || *str == '\v' || *str == '\t'
			|| *str == '\n' || *str == '\f')
		str++;
	return (str);
}

int				ft_atoi(const char *str)
{
	unsigned long	res;
	int				sgn;

	res = 0;
	sgn = 1;
	str = skip_something((char*)str);
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		str++;
		sgn = -1;
	}
	while ((*str >= '0') && (*str <= '9'))
	{
		if (sgn > 0 && (res > L_MAX / 10
				|| (res == L_MAX / 10 && (*str - '0') > L_MAX % 10)))
			return (-1);
		else if (sgn < 0 && (res > L_MAX / 10
					|| (res == L_MAX / 10 && (*str - '0') > L_MAX % 10)))
			return (0);
		res = res * 10 + *str - '0';
		str++;
	}
	return (res * sgn);
}
