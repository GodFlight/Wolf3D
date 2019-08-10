//
// Created by Slaughterfish Becker on 2019-08-07.
//

#include "raycast.h"

static int fill_default_wall_by_pos(t_wall *wall, int **texture, t_jnode *n, int id)
{
    t_jnode	*tmp;
    char	*s;

    if (!(tmp = jtoc_node_get_by_path(n, "pos")) || tmp->type != string)
        return (rc_jtoc_sdl_log_error("WALL TEXTURE POS FAILURE", id));
    if ((s = jtoc_get_string(tmp)) && !(ft_strcmp(s, "north")))
        wall->texture1 = texture;
    else if (!(ft_strcmp(s, "south")))
        wall->texture2 = texture;
    else if (!(ft_strcmp(s, "west")))
        wall->texture3 = texture;
    else if (!(ft_strcmp(s, "east")))
        wall->texture4 = texture;
    else
        return (rc_jtoc_sdl_log_error("WALL TEXTURE POS NOT FOUND", id));
    return (FUNCTION_SUCCESS);
}

static int	get_default_wall_textures(t_wall *wall, t_conf_json *conf, t_jnode *n, int id)
{
    t_jnode *tmp;
    int     **tmp_texture;

    if (!(tmp = jtoc_node_get_by_path(n, "textures")) || tmp->type != array)
        return (rc_jtoc_sdl_log_error("DEFAULT WALL TEXTURE FAILURE", id));
    tmp = tmp->down;
    while (tmp)
    {
        if (tmp->type != object)
            return (rc_jtoc_sdl_log_error("DEFAULT WALL TEXTURE FAILURE", id));
        if (rc_jtoc_fill_texture_by_index(&tmp_texture, conf, tmp, id))
            return (rc_jtoc_sdl_log_error("FILL WALL TEXTURE BY ID FAILURE", id));
        if (fill_default_wall_by_pos(wall, tmp_texture, tmp, id))
            return (FUNCTION_FAILURE);
        tmp = tmp->right;
    }
    return (FUNCTION_SUCCESS);
}

int	rc_jtoc_get_default_walls(t_wall *walls, t_conf_json *conf, t_jnode *n)
{
    t_wall cur_wall;
    int cur_id;
    t_jnode *tmp;

    n = n->down;
    while (n)
    {
        if (n->type != object)
            return (rc_jtoc_sdl_log_error("DEFAULT WALL TYPE FAILURE", -1));
        if (!(tmp = jtoc_node_get_by_path(n, "id")) || !(rc_jtoc_is_num(tmp->type)))
            return (rc_jtoc_sdl_log_error("DEFAULT WALL ID FAILURE", -1));
        cur_id = jtoc_get_int(tmp);
        if (get_default_wall_textures(&cur_wall, conf, n, cur_id))
            return (rc_jtoc_sdl_log_error("GET TEXTURES FOR DEFAULT WALL FAILURE", cur_id));
        walls[cur_id] = cur_wall;
        n = n->right;
    }
    return (FUNCTION_SUCCESS);
}
