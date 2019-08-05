/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jtoc_parse_number.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 21:20:00 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/18 21:20:00 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libjtoc.h"

static void		jtoc_atof(const char *str, float *res)
{
	float	pr;

	pr = (float)atof(str);
	*res = pr;
}

int				jtoc_parse_fractional(t_jnode *p, const char *str, int b, int e)
{
	char	*sub;
	float	*data;

	if (!(sub = ft_strsub(str, b, e - b + 1)))
		return (FUNCTION_FAILURE);
	if (!(data = (float *)malloc(sizeof(float))))
	{
		free(sub);
		return (FUNCTION_FAILURE);
	}
	jtoc_atof(sub, data);
	p->data = (void *)data;
	free(sub);
	return (FUNCTION_SUCCESS);
}

int				jtoc_parse_integer(t_jnode *p, const char *str, int b, int e)
{
	char	*sub;
	int		*data;

	if (!(sub = ft_strsub(str, b, e - b + 1)))
		return (FUNCTION_FAILURE);
	if (!(data = (int *)malloc(sizeof(int))))
	{
		free(sub);
		return (FUNCTION_FAILURE);
	}
	*data = ft_atoi(sub);
	p->data = (void *)data;
	free(sub);
	return (FUNCTION_SUCCESS);
}