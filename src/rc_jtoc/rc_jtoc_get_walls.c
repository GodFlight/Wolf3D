//
// Created by Slaughterfish Becker on 2019-08-09.
//

#include "raycast.h"

int rc_jtoc_get_walls(t_rc_main *m, t_conf_json *conf, t_jnode *n)
{
    t_jnode *tmp;

    m->walls = (t_wall *)ft_memalloc(sizeof(t_wall) * 1000);
    n = n->down;
    while (n)
    {
        if (n->type != object)
            return (rc_jtoc_sdl_log_error("WALLS TYPE ERROR", -1));
        if ((tmp = jtoc_node_get_by_path(n, "default_walls")) && tmp->type == array)
        {
            if (rc_jtoc_get_default_walls(m->walls, conf, tmp))
                return (rc_jtoc_sdl_log_error("GET DEFAULT WALLS ERROR", -1));
        }
        else if ((tmp = jtoc_node_get_by_path(n, "walls_with_states")) && tmp->type == array)
        {
            ;
        }
        else
            return (rc_jtoc_sdl_log_error("THIS WALL TYPE DOESN'T EXIST", -1));
        n = n->right;
    }
	return (0);
}
