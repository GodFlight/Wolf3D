/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_jtoc_get_objects.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 05:29:00 by sbecker           #+#    #+#             */
/*   Updated: 2019/08/22 00:23:13 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

static int	get_object_textures(t_object *obj, t_conf_json *conf,
		t_jnode *n, int id)
{
	t_jnode	*tmp;
	int		**tmp_texture;

	if (!(tmp = jtoc_node_get_by_path(n, "textures")))
		return (rc_jtoc_sdl_log_error("OBJECT TEXTURE FAILURE", id));
	tmp = tmp->down;
	while (tmp)
	{
		if (tmp->type != object)
			return (rc_jtoc_sdl_log_error("OBJECT TEXTURE TYPE FAILURE", id));
		if (rc_jtoc_fill_texture_by_index(&tmp_texture, conf, tmp, id))
			return (rc_jtoc_sdl_log_error("GET TEXTURE BY INDEX FAILURE", id));
		obj->texture = tmp_texture;
		tmp = tmp->right;
	}
	return (FUNCTION_SUCCESS);
}

static void	fill_objects_by_id(t_rc_main *m, t_object *object)
{
	int			i;
	t_object	*objs;

	i = -1;
	objs = m->objects;
	while (++i < m->objects_num)
	{
		if (object->id == objs[i].id)
		{
			objs[i].texture = object->texture;
		}
	}
}

int			rc_jtoc_get_objects(t_rc_main *m, t_conf_json *conf, t_jnode *n)
{
	t_jnode		*tmp;
	t_object	tmp_obj;

	n = n->down;
	while (n)
	{
		if (!(tmp = jtoc_node_get_by_path(n, "id")) ||
				!(rc_jtoc_is_num(tmp->type)))
			return (rc_jtoc_sdl_log_error("OBJECT ID FAILURE", -1));
		tmp_obj.id = jtoc_get_int(tmp);
		if (tmp_obj.id < 800 || tmp_obj.id > 998)
			return (rc_jtoc_sdl_log_error("OBJECT INCORRECT ID", tmp_obj.id));
		if (get_object_textures(&tmp_obj, conf, n, tmp_obj.id))
			return (rc_jtoc_sdl_log_error("OBJECT TEXTURES FAILURE",
						tmp_obj.id));
			fill_objects_by_id(m, &tmp_obj);
		n = n->right;
	}
	if (!(m->objects->intensity = (float *)malloc(sizeof(float)
					* m->objects_num)))
		exit(2);
	return (FUNCTION_SUCCESS);
}
