//
// Created by Slaughterfish Becker on 2019-08-05.
//

#include "wolf3d.h"

int	jtoc_sdl_log_error(const char *p, const int id)
{
	SDL_Log("%s ----> ERROR <---- %s", KRED, KNRM);
	SDL_Log("INCORRECT: %s%s%s%s%s",
			p,
			id < 0 ? "" : " IN ID = ",
			KGRN,
			id < 0 ? "" : ft_itoa(id),
			KNRM);
	return (FUNCTION_FAILURE);
}

int	ui_jtoc_isnum(enum e_type type)
{
	return (type == fractional || type == integer);
}

static int	get_map(t_wolf *wlf, char *path)
{
	int	fd;

	if (!(fd = open(path, O_RDONLY)))
		return (FUNCTION_FAILURE);
	if (map_read(wlf, fd))
		return (FUNCTION_FAILURE);
	return (FUNCTION_SUCCESS);
}

static int	get_obj_from_json(t_wolf *wlf, t_jnode *obj)
{
	
}

int	setup_game_from_json(t_wolf *wlf, const char path)
{
	t_jnode	*root;
	t_jnode	*map;
	t_jnode	*obj;
	wlf->

	if (!(root = jtoc_read(path)))
		return (jtoc_sdl_log_error("JSON", -1));
	if (!(map = jtoc_node_get_by_path(root, "map")) || map->type != string)
		return (jtoc_sdl_log_error("MISSING MAP", -1));
	if (get_map(wlf, jtoc_get_string(map)))
		return (jtoc_sdl_log_error("READING MAP FAILURE", -1));
	if (!(obj = jtoc_node_get_by_path(root, "objects")) || map->type != array)
		return (jtoc_sdl_log_error("MISSING OBJECTS", -1));
	obj = obj->down;
	while (obj)
	{
		if (obj->type != object)
			return (jtoc_sdl_log_error("NODE OBJECT (TYPE)", -1));
		if (get_obj_from_json(wlf, obj))
			return (jtoc_sdl_log_error("NODE OBJECT (TYPE)", -1));
		obj = obj->right;
	}
}