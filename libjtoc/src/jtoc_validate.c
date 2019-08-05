/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jtoc_validate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 00:24:02 by sbednar           #+#    #+#             */
/*   Updated: 2019/06/02 20:31:57 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libjtoc.h"
#include <stdio.h>

int	jtoc_validate_value(const char *str, int c, int e)
{
	return ((str[c] == '"' && jtoc_validate_string(str, c, e) < 0) ||
		((str[c] == '-' || (str[c] >= '0' && str[c] <= '9')) &&
			jtoc_validate_number(str, c, e) < 0) ||
		(str[c] == '[' && jtoc_validate_array(str, c, e) < 0) ||
		(str[c] == '{' && jtoc_validate_object(str, c, e) < 0) ||
		(str[c] != '"' && str[c] != '[' && str[c] != '{' &&
			str[c] != '-' && (str[c] < '0' || str[c] > '9')));
}

int	jtoc_validate_field(const char *str, int b, int e)
{
	int	c;

	if ((c = jtoc_find(str, ':', b, F_RIGHT)) < 0 ||
		str[b] != '"' || str[c - 1] != '"' ||
		jtoc_validate_value(str, c + 1, e))
		return (FUNCTION_FAILURE);
	return (FUNCTION_SUCCESS);
}
