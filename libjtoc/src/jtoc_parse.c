/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jtoc_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 00:22:42 by sbednar           #+#    #+#             */
/*   Updated: 2019/07/09 19:22:46 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libjtoc.h"

int				jtoc_parse_value(t_jnode *p, const char *str, int b, int e)
{
	if ((p->type == array && jtoc_parse_array(p, str, b, e) < 0) ||
		(p->type == string && jtoc_parse_string(p, str, b, e) < 0) ||
		(p->type == object && jtoc_parse_object(p, str, b, e) < 0) ||
		(p->type == fractional && jtoc_parse_fractional(p, str, b, e) < 0) ||
		(p->type == integer && jtoc_parse_integer(p, str, b, e) < 0))
		return (FUNCTION_FAILURE);
	return (FUNCTION_SUCCESS);
}

t_jnode			*jtoc_parse(const char *str)
{
	t_jnode	*root;

	if (!(root = jtoc_node_create(none, "root", NULL)))
		return (NULL);
	if (jtoc_parse_object(root, str, 0, ft_strlen(str) - 1) < 0)
	{
		jtoc_node_clear(root);
		return (NULL);
	}
	return (root);
}
