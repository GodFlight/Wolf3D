//
// Created by dolov on 13.08.2019.
//

static void draw_object(t_object *obj, t_rc_main *m, t_rc_player *player)
{
	float	obj_dir;
	float	obj_dist;
	int		obj_size;
	int		h_offset;
	int		w_offset;

	obj_dir = atan2f(obj->y - player->y, obj->x - player->x);
	while (obj_dir - player->view_dir > M_PI)
		obj_dir -= PI_2;
	while (obj_dir - player->view_dir < M_PI)
		obj_dir += PI_2;
	obj_dist = sqrtf(powf(player->x - obj->x, 2.f) + powf(player->y - obj->y, 2.f));
	obj_size = m->sdl->win_h / obj_dist;
	w_offset = (obj_dir - player->view_dir) * ((m->sdl->win_w / 2) / FOV) + (m->sdl->win_w / 2)  - obj_size / 2;
	h_offset = m->sdl->win_h / 2 - obj_size / 2;
	w_offset /= 2;
	SDL_Log("(%d, %d)\n", w_offset, h_offset);
	int i,j;
	i = -1;
	while (++i < obj_size)
	{
		j = -1;
		if (h_offset + i < 0 || h_offset + i >= m->sdl->win_h)
			continue;
		while (++j < obj_size)
		{
			if (w_offset + j < 0 || w_offset + j >= m->sdl->win_w)
				continue;
			sdl_put_pixel(m->sdl, w_offset + j, h_offset + i, 0);
		}
	}
}

void draw_objects(t_rc_main *m)
{
	t_object	*objs;
	int			i;

	i = -1;
	objs = m->objects;
	while (++i < m->objects_num)
	{
		draw_object(&(objs[i]), m, &(m->player));
	}
}
