//
// Created by Racquel Keli on 2019-08-18.
//

#include <raycast.h>

void		tp_obj(t_rc_main *m, t_object *obj, int obj_id, int tick)
{
	Uint32 		time;

	time = SDL_GetTicks();
	if ((float)time - m->scream.init_time > (float)tick)
	{
		obj->x = 1000.f + ((float)obj_id / 100.f);
		obj->y = 1000.f + ((float)obj_id / 100.f);
	}
}

t_object 	*get_scrm_obj(t_rc_main *m, int id)
{
	int i;

	i = -1;
	while (++i < m->objects_num)
	{
		if (m->objects[i].id == id)
			return (&(m->objects[i]));
	}
	return (NULL);
}

void move_scrm_control(t_rc_main *m, int obj_id)
{
	if (m->scream.obj->y == m->player.y || m->scream.obj->x == m->player.x)
		tp_obj(m, m->scream.obj, obj_id, m->scream.flg);
	if ((((int)m->scream.obj->x + 1 != (int)m->player.x)
	&& (m->scream.obj->y + 0.2f != (int)m->player.y)))
		m->scream.obj->y += 0.00005f;
	else if ((int)m->player.x != 25 && (int)m->player.y != 21)
		tp_obj(m, m->scream.obj, obj_id, 3000);
	else if ((int)m->scream.obj->y >= 22)
		tp_obj(m, m->scream.obj, obj_id, 100);
}

void	screaming_control(t_rc_main *m, int obj_id, char flg)
{
	m->scream.obj = get_scrm_obj(m, obj_id);
	if (m->scream.flg != 0)
		tp_obj(m, m->scream.obj, obj_id, 400);
	if (m->scream.obj->y == m->player.y || m->scream.obj->x == m->player.x)
		tp_obj(m, m->scream.obj, obj_id, flg);
	if (m->scream.flg != flg && flg != 18 && m->scream.spawn[(int)flg] == 0)
	{
		if (m->scream.obj != NULL)
		{
			m->scream.init_time = SDL_GetTicks();
			m->scream.obj->y = m->scream.y;
			m->scream.obj->x = m->scream.x;
			m->scream.flg = flg;
			m->scream.spawn[(int)flg] = 1;
			sounds_control(m, m->scream.flg);
		}
	}
	else if (m->scream.flg != flg && flg == 18 && m->scream.spawn[18] == 0)
	{
		m->scream.init_time = SDL_GetTicks();
		m->scream.obj->y = m->scream.y;
		m->scream.obj->x = m->scream.x;
		m->scream.flg = flg;
		m->scream.spawn[18] = 1;
	}
}
