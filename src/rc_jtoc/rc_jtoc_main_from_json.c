/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_jtoc_main_from_json.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 04:53:01 by sbecker           #+#    #+#             */
/*   Updated: 2019/08/22 00:23:13 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

static int	help_main(t_rc_main *m, t_conf_json *conf, t_jnode *root)
{
	t_jnode		*tmp;

	if (!(tmp = jtoc_node_get_by_path(root, "textures")) || tmp->type != array)
		return (rc_jtoc_sdl_log_error("MISSING TEXTURES", -1));
	if (rc_jtoc_get_textures(conf, tmp->down))
		return (rc_jtoc_sdl_log_error("GETTING TEXTURES FAILURE", -1));
	if (!(tmp = jtoc_node_get_by_path(root, "walls")) || tmp->type != array)
		return (rc_jtoc_sdl_log_error("MISSING WALLS", -1));
	if (rc_jtoc_get_walls(m, conf, tmp))
		return (rc_jtoc_sdl_log_error("WALLS ERROR", -1));
	if ((tmp = jtoc_node_get_by_path(root, "objects")) && tmp->type == array)
	{
		if (rc_jtoc_get_objects(m, conf, tmp))
			return (rc_jtoc_sdl_log_error("OBJECTS ERROR", -1));
	}
	return (FUNCTION_SUCCESS);
}

int			rc_jtoc_main_from_json(t_rc_main *m, const char *path,
		t_conf_json *conf)
{
	t_jnode		*root;
	t_jnode		*tmp;

	conf->index = 0;
	conf->textures = NULL;
	if (!(root = jtoc_read(path)))
		return (rc_jtoc_sdl_log_error("JSON", -1));
	if (!(tmp = jtoc_node_get_by_path(root, "win")) || tmp->type != object)
		return (rc_jtoc_sdl_log_error("MISSING WIN", -1));
	if (rc_jtoc_win_from_json(m, tmp))
		return (rc_jtoc_sdl_log_error("GETTING WIN PARAMS ERROR", -1));
	if (!(tmp = jtoc_node_get_by_path(root, "map")) || tmp->type != string)
		return (rc_jtoc_sdl_log_error("MISSING MAP", -1));
	if (rc_jtoc_get_map(m, jtoc_get_string(tmp)))
		return (rc_jtoc_sdl_log_error("READING MAP FAILURE", -1));
	if (!(tmp = jtoc_node_get_by_path(root, "player")) || tmp->type != object)
		return (rc_jtoc_sdl_log_error("MISSING PLAYER", -1));
	if (rc_jtoc_get_player(m, tmp))
		return (rc_jtoc_sdl_log_error("PLAYER FAILURE", -1));
	if (help_main(m, conf, root))
		return (FUNCTION_FAILURE);
	jtoc_node_clear(root);
	return (FUNCTION_SUCCESS);
}
