//
// Created by dolov on 13.08.2019.
//

#include "raycast.h"

float		fog_calculate_for_object(float distance)
{
	float intensity;

	intensity = clmp((distance / FOG_DIST_OBJ), 0, 1);
	return (intensity);
}

void	q_sort(float *arr, int *index_arr, int left, int right)
{
	int		l_hold;
	int		r_hold;
	float	pivot;

	pivot = arr[(left + right) / 2];
	l_hold = left;
	r_hold = right;
	while (left <= right)
	{
		while (arr[left] > pivot)
			left++;
		while (arr[right] < pivot)
			right--;
		if (left <= right)
		{
			ft_fswap(&arr[left], &arr[right]);
			ft_swap(&index_arr[left], &index_arr[right]);
			left++;
			right--;
		}
	}
	if (l_hold < right)
		q_sort(arr, index_arr, l_hold, right);
	if (r_hold > left)
		q_sort(arr, index_arr, left, r_hold);
}

int		*quick_sort(float *arr, int size)
{
	int		*index_arr;
	int		i;

	index_arr = (int *)malloc(sizeof(int) * size);
	i = -1;
	while (++i < size)
		index_arr[i] = i;
	q_sort(arr, index_arr, 0, size - 1);
	return (index_arr);
}

void	draw_objects(t_rc_main *m)
{
	t_object *obj = m->objects;
	t_rc_player *player = &m->player;
	int		i;
	float	obj_x;
	float	obj_y;
	float	inv_cam;
	float	transf_x;
	float	transf_y;
	int		obj_screen_x;
	int		obj_h;
	int		obj_w;
	int		draw_start_y;
	int		draw_end_y;
	int		draw_start_x;
	int		draw_end_x;
	int		stripe;
	int		y;
	int		texture_x;
	int		texture_y;

	float	*arr = (float *)malloc(sizeof(float) * m->objects_num);
	int		*index_arr;

	i = -1;
	while (++i < m->objects_num)
	{
		arr[i] = sqrtf((m->player.x - obj[i].x) * (m->player.x - obj[i].x) +
				(m->player.y - obj[i].y) * (m->player.y - obj[i].y));
		m->objects->intensity[i] = fog_calculate_for_object(arr[i]);
	}
	index_arr = quick_sort(arr, m->objects_num);
	i = -1;
	while (++i < m->objects_num)
	{
		obj_x = obj[index_arr[i]].x - player->x;
		obj_y = obj[index_arr[i]].y - player->y;
		inv_cam = 1.0f / (player->plane_x * player->fdir_y - player->fdir_x * player->plane_y);
		transf_x = inv_cam * (player->fdir_y * obj_x - player->fdir_x * obj_y);
		transf_y = inv_cam * (-player->plane_y * obj_x + player->plane_x * obj_y);
		obj_screen_x = (int)((((float)m->sdl->win_w / 2.f) * (float)(1 + transf_x / transf_y)));

		obj_h = ABS((int)(m->sdl->win_h / transf_y));
		obj_w = obj_h;
		draw_start_y = -obj_h / 2 + m->sdl->win_h / 2;
		draw_end_y = obj_h / 2 + m->sdl->win_h / 2;
		draw_start_x = -obj_w / 2 + obj_screen_x;
		draw_end_x = obj_w / 2 + obj_screen_x;
		if (draw_start_x < 0)
			draw_start_x = 0;
		if (draw_start_y < 0)
			draw_start_y = 0;
		if (draw_end_x >= m->sdl->win_w)
			draw_end_x = m->sdl->win_w - 1;
		if (draw_end_y >= m->sdl->win_h)
			draw_end_y = m->sdl->win_h - 1;
		stripe = draw_start_x - 1;
		while (++stripe < draw_end_x)
		{
			texture_x = (int)(((float)stripe - ((float)(-obj_w) / 2.f + (float)obj_screen_x)) * 64 / (float)obj_w);
			if (texture_x < 2)
				texture_x = 2;
			y = draw_start_y - 1;
			if (transf_y > 0 && transf_y < m->z_buffer[stripe] && stripe > 0 && stripe < m->sdl->win_w)
				while (++y < draw_end_y)
				{
					int tmp = y * 256 - m->sdl->win_h * 128 + obj_h * 128;
					texture_y = ((tmp * 64) / obj_h) / 256;
					int color = rgb_mod(m->objects->intensity[index_arr[i]], obj[index_arr[i]].texture[texture_y][texture_x]);
					if (color & 0x000000FF)
						sdl_put_pixel(m->sdl, stripe, y, color);
				}
		}
	}
	free(arr);
	free(index_arr);
}
