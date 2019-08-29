/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_jtoc_get_player.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/19 05:44:08 by sbecker           #+#    #+#             */
/*   Updated: 2019/08/22 00:23:13 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

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

static int	get_right_vector(t_rc_main *m, t_jnode *n)
{
	t_jnode	*tmp;
	float	tmp_x;
	float	tmp_y;

	if (!(tmp = jtoc_node_get_by_path(n, "direction_right")) ||
			tmp->type != object)
		return (rc_jtoc_sdl_log_error("DIRECTION RIGHT ERROR", -1));
	if (!(tmp = jtoc_node_get_by_path(n, "direction_right.x")) ||
			tmp->type != fractional)
		return (rc_jtoc_sdl_log_error("DIRECTION RIGHT X ERROR", -1));
	tmp_x = jtoc_get_float(tmp);
	if (!(tmp = jtoc_node_get_by_path(n, "direction_right.y")) ||
			tmp->type != fractional)
		return (rc_jtoc_sdl_log_error("DIRECTION RIGHT Y ERROR", -1));
	tmp_y = jtoc_get_float(tmp);
	normalize_vector(&tmp_x, &tmp_y);
	m->player.rdir_x = tmp_x;
	m->player.rdir_y = tmp_y;
	return (FUNCTION_SUCCESS);
}

int			rc_jtoc_get_player(t_rc_main *m, t_jnode *n)
{
	t_jnode	*tmp;

	if (!(tmp = jtoc_node_get_by_path(n, "fov")) ||
			tmp->type != fractional)
		return (rc_jtoc_sdl_log_error("PLAYER FOV ERROR", -1));
	m->player.plane_x = 0;
	m->player.plane_y = jtoc_get_float(tmp);
	if (!(tmp = jtoc_node_get_by_path(n, "direction_forward")) ||
			tmp->type != object)
		return (rc_jtoc_sdl_log_error("DIRECTION FORWARD ERROR", -1));
	if (!(tmp = jtoc_node_get_by_path(n, "direction_forward.x")) ||
			tmp->type != fractional)
		return (rc_jtoc_sdl_log_error("DIRECTION FORWARD X ERROR", -1));
	m->player.fdir_x = jtoc_get_float(tmp);
	if (!(tmp = jtoc_node_get_by_path(n, "direction_forward.y")) ||
			tmp->type != fractional)
		return (rc_jtoc_sdl_log_error("DIRECTION FORWARD Y ERROR", -1));
	m->player.fdir_y = jtoc_get_float(tmp);
	normalize_vector(&m->player.fdir_x, &m->player.fdir_y);
	if (get_right_vector(m, n))
		return (FUNCTION_FAILURE);
	return (FUNCTION_SUCCESS);
}
