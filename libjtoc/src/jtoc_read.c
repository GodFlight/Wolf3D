/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jtoc_read.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 15:46:08 by sbednar           #+#    #+#             */
/*   Updated: 2019/06/01 15:50:54 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libjtoc.h"

t_jnode	*jtoc_read(const char *str)
{
	t_jnode	*json_tree;
	char	*json_str;

	json_str = NULL;
	if (jtoc_read_file(str, &json_str) < 0)
		return (NULL);
	if (jtoc_remove_spaces(&json_str) < 0)
	{
		free(json_str);
		return (NULL);
	}
	json_tree = jtoc_parse(json_str);
	free(json_str);
	return (json_tree);
}
