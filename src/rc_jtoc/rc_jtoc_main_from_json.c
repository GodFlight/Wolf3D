//
// Created by Slaughterfish Becker on 2019-08-05.
//

#include "raycast.h"

int get_enemy_textures(t_enemy *enemy, t_conf_json *conf, t_jnode *n, int id)
{
    t_jnode *tmp;
    int     **tmp_texture;

    if (!(tmp = jtoc_node_get_by_path(n, "textures")))
        return (rc_jtoc_sdl_log_error("ENEMY TEXTURE FAILURE", id));
    tmp = tmp->down;
    while (tmp)
    {
        if (tmp->type != object)
            return (rc_jtoc_sdl_log_error("ENEMY TEXTURE TYPE FAILURE", id));
        if (rc_jtoc_fill_texture_by_index(&tmp_texture, conf, tmp, id))
            return (rc_jtoc_sdl_log_error("ENEMY GET TEXTURE BY INDEX FAILURE", id));
        enemy->texture = tmp_texture;
        tmp = tmp->right;
    }
    return (FUNCTION_SUCCESS);
}

int	rc_jtoc_get_enemies(t_rc_main *m, t_conf_json *conf, t_jnode *n)
{
    int     i;
    t_jnode *tmp_n;
    t_jnode *tmp;
    t_enemy tmp_enemy;
    int     id;

    i = 0;
    tmp_n = n->down;
    while (tmp_n)
    {
        if (tmp_n->type != object)
            return (rc_jtoc_sdl_log_error("ENEMY TYPE FAILURE", -1));
        i++;
        tmp_n = tmp_n->right;
    }
    m->enemies = (t_enemy *)ft_memalloc(sizeof(t_enemy) * i);
	n = n->down;
	i = -1;
	while (n)
	{
	    i++;
        if (!(tmp = jtoc_node_get_by_path(n, "id")) || !(rc_jtoc_is_num(tmp->type)))
            return (rc_jtoc_sdl_log_error("ENEMY ID FAILURE", -1));
        id = jtoc_get_int(tmp);
        if (id < 1000 || id > 1999)
            return (rc_jtoc_sdl_log_error("ENEMY INCORRECT ID", -1));
        if (get_enemy_textures(&tmp_enemy, conf, n, id))
            return (rc_jtoc_sdl_log_error("ENEMY TEXTURES FAILURE", -1));
        m->enemies[i] = tmp_enemy;
        n = n->right;
	}
	return (FUNCTION_SUCCESS);
}

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

	//TODO reading from few packs
	if (!(tmp = jtoc_node_get_by_path(root, "textures")) || tmp->type != array)
		return (rc_jtoc_sdl_log_error("MISSING TEXTURES", -1));
	if (rc_jtoc_get_textures(m, &conf, tmp->down))
		return (rc_jtoc_sdl_log_error("GETTING TEXTURES FAILURE", -1));

	//walls
	if (!(tmp = jtoc_node_get_by_path(root, "walls")) || tmp->type != array)
		return (rc_jtoc_sdl_log_error("MISSING WALLS", -1));
    if (rc_jtoc_get_walls(m, &conf, tmp))
		return (rc_jtoc_sdl_log_error("WALLS ERROR", -1));

    //enemies
	if ((tmp = jtoc_node_get_by_path(root, "enemies")) && tmp->type == array)
	{
		if (rc_jtoc_get_enemies(m, &conf, tmp))
			return (rc_jtoc_sdl_log_error("ENEMIES ERROR", -1));
	}

	return (FUNCTION_SUCCESS);
}