//
// Created by Slaughterfish Becker on 2019-08-07.
//

#include "raycast.h"

int	rc_jtoc_get_texture_state(int *state, t_jnode *n, int obj_id)
{
	t_jnode	*tmp;
	char	*s;

	if (!(tmp = jtoc_node_get_by_path(n, "state")))
		*state = 1;
	else if (tmp->type != string)
		return (rc_jtoc_sdl_log_error("TEXTURE STATE FAILURE", obj_id));
	else if ((s = jtoc_get_string(tmp)) && !(ft_strcmp(s, "default")))
		*state = 1;
	else if (!(ft_strcmp(s, "state1")))
		*state = 2;
	else if (!(ft_strcmp(s, "state2")))
		*state = 3;
	return (FUNCTION_SUCCESS);
}
