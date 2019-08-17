//
// Created by Slaughterfish Becker on 2019-08-05.
//

#include "raycast.h"

int get_object_textures(t_object *obj, t_conf_json *conf, t_jnode *n, int id)
{
	t_jnode *tmp;
	int     **tmp_texture;

	if (!(tmp = jtoc_node_get_by_path(n, "textures")))
		return (rc_jtoc_sdl_log_error("OBJECT TEXTURE FAILURE", id));
	tmp = tmp->down;
	while (tmp)
	{
		if (tmp->type != object)
			return (rc_jtoc_sdl_log_error("OBJECT TEXTURE TYPE FAILURE", id));
		if (rc_jtoc_fill_texture_by_index(&tmp_texture, conf, tmp, id))
			return (rc_jtoc_sdl_log_error("OBJECT GET TEXTURE BY INDEX FAILURE", id));
		obj->texture = tmp_texture;  //TODO now there is only one texture in object
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

int	rc_jtoc_get_objects(t_rc_main *m, t_conf_json *conf, t_jnode *n)
{
	t_jnode		*tmp;
	t_object	tmp_obj;

	n = n->down;
	while (n)
	{
		if (!(tmp = jtoc_node_get_by_path(n, "id")) || !(rc_jtoc_is_num(tmp->type)))
			return (rc_jtoc_sdl_log_error("OBJECT ID FAILURE", -1));
		tmp_obj.id = jtoc_get_int(tmp);
		if (tmp_obj.id < 800 || tmp_obj.id > 998)
			return (rc_jtoc_sdl_log_error("OBJECT INCORRECT ID", tmp_obj.id));
		if (get_object_textures(&tmp_obj, conf, n, tmp_obj.id))
			return (rc_jtoc_sdl_log_error("OBJECT TEXTURES FAILURE", tmp_obj.id));
		fill_objects_by_id(m, &tmp_obj);
		n = n->right;
	}
	if (!(m->objects->intensity = (float *)malloc(sizeof(float) * m->objects_num)))
		exit(2);
	return (FUNCTION_SUCCESS);
}

static void	normalize_vector(float *a, float *b)
{
	float	x;
	float	y;
	float	len;

	x = *a;
	y = *b;
	len = sqrtf(x * x + y * y);
	if (len == 0)
		return ;
	*a = x / len;
	*b = y / len;
}

int	rc_jtoc_get_player(t_rc_main *m, t_jnode *n)
{
	t_jnode	*tmp;
	float	tmp_x;
	float	tmp_y;

	if (!(tmp = jtoc_node_get_by_path(n, "fov")) || tmp->type != fractional)
		return (rc_jtoc_sdl_log_error("PLAYER FOV ERROR", -1));
	m->player.plane_x = 0;
	m->player.plane_y = jtoc_get_float(tmp);
	if (!(tmp = jtoc_node_get_by_path(n, "direction_forward")) || tmp->type != object)
		return (rc_jtoc_sdl_log_error("PLAYER DIRECTION FORWARD ERROR", -1));
	if (!(tmp = jtoc_node_get_by_path(n, "direction_forward.x")) || tmp->type != fractional)
		return (rc_jtoc_sdl_log_error("PLAYER DIRECTION FORWARD X ERROR", -1));
	tmp_x = jtoc_get_float(tmp);
	if (!(tmp = jtoc_node_get_by_path(n, "direction_forward.y")) || tmp->type != fractional)
		return (rc_jtoc_sdl_log_error("PLAYER DIRECTION FORWARD Y ERROR", -1));
	tmp_y = jtoc_get_float(tmp);
	normalize_vector(&tmp_x, &tmp_y);
	m->player.fdir_x = tmp_x;
	m->player.fdir_y = tmp_y;
	if (!(tmp = jtoc_node_get_by_path(n, "direction_right")) || tmp->type != object)
		return (rc_jtoc_sdl_log_error("PLAYER DIRECTION RIGHT ERROR", -1));
	if (!(tmp = jtoc_node_get_by_path(n, "direction_right.x")) || tmp->type != fractional)
		return (rc_jtoc_sdl_log_error("PLAYER DIRECTION RIGHT X ERROR", -1));
	tmp_x = jtoc_get_float(tmp);
	if (!(tmp = jtoc_node_get_by_path(n, "direction_right.y")) || tmp->type != fractional)
		return (rc_jtoc_sdl_log_error("PLAYER DIRECTION RIGHT Y ERROR", -1));
	tmp_y = jtoc_get_float(tmp);
	normalize_vector(&tmp_x, &tmp_y);
	m->player.rdir_x = tmp_x;
	m->player.rdir_y = tmp_y;
	return (FUNCTION_SUCCESS);
}

int rc_jtoc_main_from_json(t_rc_main *m, const char *path, t_conf_json *conf)
{
	t_jnode		*root;
	t_jnode		*tmp;

	//conf init
	conf->index = 0;
	conf->textures = NULL;

	//root
	if (!(root = jtoc_read(path)))
		return (rc_jtoc_sdl_log_error("JSON", -1));

	//win
	if (!(tmp = jtoc_node_get_by_path(root, "win")) || tmp->type != object)
		return (rc_jtoc_sdl_log_error("MISSING WIN", -1));
	if (rc_jtoc_win_from_json(m, tmp))
		return (rc_jtoc_sdl_log_error("GETTING WIN PARAMS ERROR", -1));

	//map
	if (!(tmp = jtoc_node_get_by_path(root, "map")) || tmp->type != string)
		return (rc_jtoc_sdl_log_error("MISSING MAP", -1));
	if (rc_jtoc_get_map(m, jtoc_get_string(tmp)))
		return (rc_jtoc_sdl_log_error("READING MAP FAILURE", -1));

	//player
	if (!(tmp = jtoc_node_get_by_path(root, "player")) || tmp->type != object)
		return (rc_jtoc_sdl_log_error("MISSING PLAYER", -1));
	if (rc_jtoc_get_player(m, tmp))
		return (rc_jtoc_sdl_log_error("PLAYER FAILURE", -1));

	//TODO reading from few packs
	if (!(tmp = jtoc_node_get_by_path(root, "textures")) || tmp->type != array)
		return (rc_jtoc_sdl_log_error("MISSING TEXTURES", -1));
	if (rc_jtoc_get_textures(conf, tmp->down))
		return (rc_jtoc_sdl_log_error("GETTING TEXTURES FAILURE", -1));

	//walls
	if (!(tmp = jtoc_node_get_by_path(root, "walls")) || tmp->type != array)
		return (rc_jtoc_sdl_log_error("MISSING WALLS", -1));
	if (rc_jtoc_get_walls(m, conf, tmp))
		return (rc_jtoc_sdl_log_error("WALLS ERROR", -1));

	//objects
	if ((tmp = jtoc_node_get_by_path(root, "objects")) && tmp->type == array)
	{
		if (rc_jtoc_get_objects(m, conf, tmp))
			return (rc_jtoc_sdl_log_error("OBJECTS ERROR", -1));
	}

	jtoc_node_clear(root);
	return (FUNCTION_SUCCESS);
}