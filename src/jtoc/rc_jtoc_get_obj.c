//
// Created by Slaughterfish Becker on 2019-08-07.
//

#include "raycast.h"


int	rc_jtoc_get_obj(t_rc_main *m, t_jnode *n, t_conf_json *conf)
{
	t_jnode		*tmp;
	t_object	*objs;
	t_object	cur_obj;
	char		*s;

	//TODO create from max id
	objs = (t_object *)ft_memalloc(sizeof(t_object) * 100000);

	if (!(tmp = jtoc_node_get_by_path(n, "id")) || !(rc_jtoc_is_num(tmp->type)))
		return (rc_jtoc_sdl_log_error("OBJECT ID FAILURE", -1));
	cur_obj.id = jtoc_get_int(tmp);

	if (tmp = jtoc_node_get_by_path(n, "params") && tmp->type == array)
	{
		cur_obj.params = 0;
		tmp = tmp->down;
		while (tmp)
		{
			if (tmp->type != string)
				return (rc_jtoc_sdl_log_error("OBJECT PARAMS FAILURE", cur_obj.id));
			if (ft_strcmp(jtoc_get_string(tmp), "OBJ_IS_DESTRUCTIBLE"))
				cur_obj.params |= OBJ_IS_DESTRUCTIBLE;
		}
	}

	if (!(tmp = jtoc_node_get_by_path(n, "type")) || tmp->type != string)
		return (rc_jtoc_sdl_log_error("OBJECT TYPE FAILURE", cur_obj.id));
	s = jtoc_get_string(tmp);
	if (ft_strcmp(s, "wall"))
	{
		cur_obj.type = 1;
		rc_jtoc_get_wall_obj(&cur_obj, n, conf);
	}
}
