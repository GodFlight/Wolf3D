//
// Created by Slaughterfish Becker on 2019-08-07.
//

#include "raycast.h"

static int get_wall_texture_pos(int *pos, t_jnode *n, int obj_id)
{
	t_jnode	*tmp;
	char	*s;

	if (!(tmp = jtoc_node_get_by_path(n, "pos")) || tmp->type != string)
		return (rc_jtoc_sdl_log_error("WALL TEXTURE POS FAILURE", obj_id));
	if ((s = jtoc_get_string(tmp)) && !(ft_strcmp(s, "north")))
		*pos = 1;
	else if (!(ft_strcmp(s, "south")))
		*pos = 2;
	else if (!(ft_strcmp(s, "west")))
		*pos = 3;
	else if (!(ft_strcmp(s, "east")))
		*pos = 4;
	else
		return (rc_jtoc_sdl_log_error("WALL TEXTURE POS NOT FOUND", obj_id));
	return (FUNCTION_SUCCESS);
}

t_list	*get_node_by_index_in_content_size(t_list *lst, int index)
{
	while (lst)
	{
		if (lst->content_size == (size_t)index)
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

static int	fill_cur_wall_texture_state(t_wts *cur_state, t_conf_json *conf, t_jnode *n, int pos)
{
	t_jnode	*tmp;
	int		**tmp_arr;
	t_list	*cur_lst;

	if (cur_state == NULL)
		cur_state = (t_wts *)ft_memalloc(sizeof(t_wts));
	if (!(tmp = jtoc_node_get_by_path(n, "index")) || !rc_jtoc_is_num(tmp->type))
		return (rc_jtoc_sdl_log_error("TEXTURE INDEX FAILURE", -1));
	cur_lst = get_node_by_index_in_content_size(conf->textures, jtoc_get_int(tmp));
	if (cur_lst == NULL)
		return (rc_jtoc_sdl_log_error("GET TEXTURE BY INDEX FAILURE", -1));
	tmp_arr = (int **)cur_lst->content;
	if (pos == 1)
		cur_state->texture_north = tmp_arr;
	if (pos == 2)
		cur_state->texture_south = tmp_arr;
	if (pos == 3)
		cur_state->texture_west = tmp_arr;
	if (pos == 4)
		cur_state->texture_east = tmp_arr;
	return (FUNCTION_SUCCESS);
}

static int	get_wall_texture(t_wall *wall, t_jnode *n, t_conf_json *conf, int *arr)
{
	int		obj_id;
	int		state;
	int		pos;
	t_wts	*cur_state;

	cur_state = 0;
	obj_id = arr[0];
	state = arr[1];
	pos = arr[2];
	cur_state = (state == 1 ? wall->state1 : cur_state);
	cur_state = (state == 2 ? wall->state2 : cur_state);
	cur_state = (state == 3 ? wall->state3 : cur_state);
	if (cur_state == 0)
		return (rc_jtoc_sdl_log_error("OBJECT STATE FAILURE", obj_id));
	if (fill_cur_wall_texture_state(cur_state, conf, n, pos))
		return (rc_jtoc_sdl_log_error("FILL WALL TEXTURE FAILURE", obj_id));
	return (FUNCTION_SUCCESS);
}

int	rc_jtoc_get_wall_obj(t_object *obj, t_jnode *n, t_conf_json *conf)
{
	t_jnode	*tmp;
	t_wall	*wall;
	int		state;
	int		pos;

	wall = (t_wall *)ft_memalloc(sizeof(t_wall));
	wall->state1 = (t_wts *)ft_memalloc(sizeof(t_wts));
	wall->state2 = (t_wts *)ft_memalloc(sizeof(t_wts));
	wall->state3 = (t_wts *)ft_memalloc(sizeof(t_wts));
	if (!(tmp = jtoc_node_get_by_path(n, "textures")) || tmp->type != array)
		return (rc_jtoc_sdl_log_error("OBJECT TEXTURE FAILURE", obj->id));
	tmp = tmp->down;
	while (tmp)
	{
		if (tmp->type != object)
			return (rc_jtoc_sdl_log_error("OBJECT TEXTURE FAILURE", obj->id));
		if (rc_jtoc_get_texture_state(&state, tmp, obj->id) || get_wall_texture_pos(&pos, tmp, obj->id))
			return (FUNCTION_FAILURE);
		if (get_wall_texture(wall, tmp, conf, (int []){(obj->id), (state), (pos)}))
			return (rc_jtoc_sdl_log_error("OBJECT TEXTURE FAILURE", obj->id));
		tmp = tmp->right;
	}
	obj->data = (void *)wall;
	return (FUNCTION_SUCCESS);
}
