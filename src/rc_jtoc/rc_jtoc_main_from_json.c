//
// Created by Slaughterfish Becker on 2019-08-05.
//

#include "raycast.h"

int	rc_jtoc_main_from_json(t_rc_main *m, const char *path)
{
	t_conf_json	conf;
	t_jnode		*root;
	t_jnode		*tmp;

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

	//TODO !!textures!!
	if (!(tmp = jtoc_node_get_by_path(root, "textures")) || tmp->type != array)
		return (rc_jtoc_sdl_log_error("MISSING TEXTURES", -1));
	if (rc_jtoc_get_textures(m, &conf, tmp->down))
		return (rc_jtoc_sdl_log_error("GETTING TEXTURES FAILURE", -1));

	//walls
	if (!(tmp = jtoc_node_get_by_path(root, "walls")) || tmp->type != array)
		return (rc_jtoc_sdl_log_error("MISSING WALLS", -1));
    if (rc_jtoc_get_walls(m, &conf, tmp))
		return (rc_jtoc_sdl_log_error("WALLS ERROR", -1));

	return (FUNCTION_SUCCESS);
}