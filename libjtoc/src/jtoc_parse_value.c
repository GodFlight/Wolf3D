/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jtoc_parse_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/02 20:33:59 by sbednar           #+#    #+#             */
/*   Updated: 2019/06/02 20:37:28 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libjtoc.h"

int	jtoc_parse_object(t_jnode *p, const char *str, int b, int e)
{
	int	c;

	if (e - b == 3 && !ft_strncmp(str + b, "NULL", 4))
	{
		p->data = NULL;
		return (FUNCTION_SUCCESS);
	}
	if (str[e] == '\n')
		--e;
	++b;
	--e;
	while (b < e)
	{
		if ((c = jtoc_find_comma(str, b) - 1) < 0 || c > e)
			c = e;
		if (jtoc_parse_field(p, str, b, c) < 0)
			return (FUNCTION_FAILURE);
		b = c + (c == e ? 0 : 2);
	}
	return (b > e ? FUNCTION_FAILURE : FUNCTION_SUCCESS);
}

int	jtoc_parse_string(t_jnode *p, const char *str, int b, int e)
{
	char	*sub;

	if (e - b == 3 && !ft_strncmp(str + b, "NULL", 4))
	{
		p->data = NULL;
		return (FUNCTION_SUCCESS);
	}
	++b;
	--e;
	if (!(sub = ft_strsub(str, b, e - b + 1)))
		return (FUNCTION_FAILURE);
	p->data = (void *)sub;
	return (FUNCTION_SUCCESS);
}

int	jtoc_parse_array(t_jnode *p, const char *str, int b, int e)
{
	t_jnode	*child;
	char	*tmp;
	int		c;
	int		i;

	if (e - b == 3 && !ft_strncmp(str + b, "NULL", 4))
	{
		p->data = NULL;
		return (FUNCTION_SUCCESS);
	}
	++b;
	--e;
	i = -1;
	while (b < e)
	{
		++i;
		if ((c = jtoc_find_comma(str, b) - 1) < 0 || c > e)
			c = e;
		if (!(tmp = ft_itoa(i)))
			return (FUNCTION_FAILURE);
		child = jtoc_node_create(jtoc_get_field_type((char *)str + b), tmp,
				NULL);
		free(tmp);
		if (!child)
			return (FUNCTION_FAILURE);
		jtoc_node_add_child(p, child);
		jtoc_parse_value(child, str, b, c);
		b = c + (c == e ? 0 : 2);
	}
	return (b > e ? FUNCTION_FAILURE : FUNCTION_SUCCESS);
}

int	jtoc_parse_field(t_jnode *p, const char *str, int b, int e)
{
	t_jnode	*child;
	char	*name;
	int		c;

	c = jtoc_find(str, ':', b, F_RIGHT);
	if (!(name = ft_strsub(str, b + 1, c - b - 2)))
		return (FUNCTION_FAILURE);
	child = jtoc_node_create(jtoc_get_field_type((char *)str + c + 1), name, NULL);
	free(name);
	if (!child)
		return (FUNCTION_FAILURE);
	jtoc_node_add_child(p, child);
	jtoc_parse_value(child, str, c + 1, e);
	return (FUNCTION_SUCCESS);
}
