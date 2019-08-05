/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jtoc_validate_value.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 20:30:23 by sbednar           #+#    #+#             */
/*   Updated: 2019/06/02 20:31:49 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libjtoc.h"

int	jtoc_validate_number(const char *str, int b, int e)
{
	if (str[b] == '-')
		++b;
	while (b <= e && str[b] >= '0' && str[b] <= '9')
		++b;
	if ((b < e && str[b] != '.') || (b == e && str[b] == '.'))
		return (FUNCTION_FAILURE);
	if (str[b] == '.')
		++b;
	while (b <= e && str[b] >= '0' && str[b] <= '9')
		++b;
	return (b < e ?
		FUNCTION_FAILURE :
		FUNCTION_SUCCESS);
}

int	jtoc_validate_string(const char *str, int b, int e)
{
	if (e - b == 3 && !ft_strncmp(str + b, "NULL", 4))
		return (FUNCTION_SUCCESS);
	return (str[b] == '"' && str[e] == '"' ?
		FUNCTION_SUCCESS :
		FUNCTION_FAILURE);
}

int	jtoc_validate_object(const char *str, int b, int e)
{
	int	c;

	if (str[e] == '\n')
		--e;
	if (e - b == 3 && !ft_strncmp(str + b, "NULL", 4))
		return (FUNCTION_SUCCESS);
	if (str[b++] != '{' || str[e--] != '}')
		return (FUNCTION_FAILURE);
	while (b < e)
	{
		if ((c = jtoc_find_comma(str, b) - 1) < 0 || c > e)
			c = e;
		if (jtoc_validate_field(str, b, c) < 0)
			return (FUNCTION_FAILURE);
		b = c + (c == e ? 0 : 2);
	}
	return (b > e ? FUNCTION_FAILURE : FUNCTION_SUCCESS);
}

int	jtoc_validate_array(const char *str, int b, int e)
{
	int	c;

	if (e - b == 3 && !ft_strncmp(str + b, "NULL", 4))
		return (FUNCTION_SUCCESS);
	if (str[b++] != '[' || str[e--] != ']')
		return (FUNCTION_FAILURE);
	while (b < e)
	{
		if ((c = jtoc_find_comma(str, b) - 1) < 0 || c > e)
			c = e;
		if (jtoc_validate_value(str, b, c))
			return (FUNCTION_FAILURE);
		b = c + (c == e ? 0 : 2);
	}
	return (b > e ? FUNCTION_FAILURE : FUNCTION_SUCCESS);
}
