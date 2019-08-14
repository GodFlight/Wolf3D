//
// Created by dolov on 13.08.2019.
//

#include "raycast.h"

static void draw_object(t_object *obj, t_rc_main *m, t_rc_player *player)
{
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
	int		column;
	int		y;

	SDL_Log("%d\n", m->objects_num);
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
		column = draw_start_x - 1;
		while (++column < draw_end_x)
		{
			y = draw_start_y - 1;
			while (++y < draw_end_y)
				sdl_put_pixel(m->sdl, column, y, 0);
		}
	}
}

void draw_objects(t_rc_main *m)
{
	t_object	*objs;
	int			i;

	i = -1;
	objs = m->objects;
	draw_object(&(objs[i]), m, &(m->player));
}
