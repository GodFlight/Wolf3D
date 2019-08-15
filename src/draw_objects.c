//
// Created by dolov on 13.08.2019.
//

#include "raycast.h"

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

	i = -1;
	while (++i < m->objects_num)
	{
		obj_x = obj[i].x - player->x;
		obj_y = obj[i].y - player->y;
		inv_cam = 1.0f / (player->plane_x * player->fdir_y - player->fdir_x * player->plane_y);
		transf_x = inv_cam * (player->fdir_y * obj_x - player->fdir_x * obj_y);
		transf_y = inv_cam * (-player->plane_y * obj_x + player->plane_x * obj_y);
		obj_screen_x = (int)((m->sdl->win_w / 2) * (float)(1 + transf_x / transf_y));

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
			//TODO 64 - texture w and texture h
			texture_x = (int)((256 * (stripe - (-obj_w / 2 + obj_screen_x)) * 64 / obj_w) / 256);
			y = draw_start_y - 1;
			if (transf_y > 0 && stripe > 0 && stripe < m->sdl->win_w) //TODO z-buffer
				while (++y < draw_end_y)
				{
					int tmp = y * 256 - m->sdl->win_h * 128 + obj_h * 128;
					texture_y = ((tmp * 64) / obj_h) / 256;
					int color = obj[i].texture[texture_y][texture_x];
					sdl_put_pixel(m->sdl, stripe, y, color);
				}
		}
	}
}
