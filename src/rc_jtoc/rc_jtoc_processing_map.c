//
// Created by dolov on 12.08.2019.
//

#include "raycast.h"

static int	check_bounds(int **map, int h_map, int w_map)
{
	int	i;

	i = -1;
	while (++i < w_map)
		if (map[0][i] < 0 || map[0][i] > 99 || map[h_map - 1][i] < 0 || map[h_map - 1][i] > 99)
			return (FUNCTION_FAILURE);
	i = -1;
	while (++i < h_map)
		if (map[i][0] < 0 || map[i][0] > 99 || map[i][w_map - 1] < 0 || map[i][w_map - 1] > 99)
//		if (map[i][0] == 0 || map[i][w_map - 1] == 0)
			return (FUNCTION_FAILURE);
	return (FUNCTION_SUCCESS);
}

static int get_phys_map_and_objs_num(t_rc_main *m, int **map)
{
	int	i;
	int	j;
	int	player_id_flag;

	player_id_flag = 0;
	m->phys_map = (int **)ft_memalloc(sizeof(int *) * m->map_h);
	i = -1;
	while (++i < m->map_h)
	{
		j = -1;
		m->phys_map[i] = (int *)ft_memalloc(sizeof(int) * m->map_w);
		while (++j < m->map_w)
		{
			if (map[i][j] < 0 || map[i][j] > 999 || (map[i][j] > 299 && map[i][j] < 800))
				return (rc_jtoc_sdl_log_error("BAD ID (ID COULD BE ONLY 0-299, 800-999)", -1));
			if (map[i][j] == 999)
			{
				m->player.x = i + 0.5f;
				m->player.y = j + 0.5f;
				player_id_flag++;
			}
			else
				m->phys_map[i][j] = map[i][j];
			if (map[i][j] >= 800 && map[i][j] <= 998)
				m->objects_num++;
			if (map[i][j] > 299)
				map[i][j] = 0;
		}
	}
	if (player_id_flag != 1)
		return (rc_jtoc_sdl_log_error("BAD PLAYER ID", -1));
	return (FUNCTION_SUCCESS);
}

static int get_objects_arr(t_rc_main *m, int **map)
{
	int	i;
	int	j;
	int	obj_count;

	obj_count = 0;
	m->objects = (t_object *)ft_memalloc(sizeof(t_object) * m->objects_num);
	i = -1;
	while (++i < m->map_h)
	{
		j = -1;
		while (++j < m->map_w)
		{
			if (map[i][j] >= 800 && map[i][j] <= 998)
			{
				m->objects[obj_count].id = map[i][j];
				m->objects[obj_count].x = i + 0.5f;
				m->objects[obj_count].y = j + 0.5f;
				obj_count++;
			}
		}
	}
	return (FUNCTION_SUCCESS);
}

int rc_jtoc_processing_map(t_rc_main *m)
{
	if (check_bounds(m->map, m->map_h, m->map_w))
		return (rc_jtoc_sdl_log_error("BAD BOUNDS", -1));
	if (get_phys_map_and_objs_num(m, m->map))
		return (rc_jtoc_sdl_log_error("PROCESSING MAP FAILURE", -1));
	get_objects_arr(m, m->phys_map);
	return (FUNCTION_SUCCESS);
}
