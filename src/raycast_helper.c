
#include "raycast.h"

int		step_x_calculate(t_rc_main *m, float ray_dir_x)
{
	int step_x;

	if (ray_dir_x < 0)
	{
		step_x = -1;
		m->flr.side_dist_x = (m->player.x - m->wls.map_x)
							 * m->player.delta_dist_x;
	}
	else
	{
		step_x = 1;
		m->flr.side_dist_x = (m->wls.map_x + 1 - m->player.x)
							 * m->player.delta_dist_x;
	}
	return (step_x);
}

int		step_y_calculate(t_rc_main *m, float ray_dir_y)
{
	int step_y;

	if (ray_dir_y < 0)
	{
		step_y = -1;
		m->flr.side_dist_y = (m->player.y - m->wls.map_y)
							 * m->player.delta_dist_y;
	}
	else
	{
		step_y = 1;
		m->flr.side_dist_y = (m->wls.map_y + 1 - m->player.y)
							 * m->player.delta_dist_y;
	}
	return (step_y);
}

void		wall_dist_and_hit_x_calculate(t_rc_main *m, float ray_dir_x,
										  float ray_dir_y)
{
	if (m->wls.side == 0)
	{
		m->flr.wall_dist = (m->wls.map_x - m->player.x
							+ (1.f - (float)m->flr.step_x) / 2) / ray_dir_x;
		m->flr.hit_x = m->player.y + m->flr.wall_dist * ray_dir_y;
	}
	else
	{
		m->flr.wall_dist = (m->wls.map_y - m->player.y
							+ (1 - m->flr.step_y) / 2) / ray_dir_y;
		m->flr.hit_x = m->player.x + m->flr.wall_dist * ray_dir_x;
	}
}

void		flr_or_clng_offset_calculate(t_rc_main *m, float ray_dir_x,
										 float ray_dir_y)
{
	if(m->wls.side == 0 && ray_dir_x > 0)
	{
		m->flr.floor_wall_x = m->wls.map_x;
		m->flr.floor_wall_y = m->wls.map_y + m->flr.hit_x;
	}
	else if(m->wls.side == 0 && ray_dir_x < 0)
	{
		m->flr.floor_wall_x = m->wls.map_x + 1.0f;
		m->flr.floor_wall_y = m->wls.map_y + m->flr.hit_x;
	}
	else if(m->wls.side == 1 && ray_dir_y > 0)
	{
		m->flr.floor_wall_x = m->wls.map_x + m->flr.hit_x;
		m->flr.floor_wall_y = m->wls.map_y;
	}
	else
	{
		m->flr.floor_wall_x = m->wls.map_x + m->flr.hit_x;
		m->flr.floor_wall_y = m->wls.map_y + 1.0f;
	}
}

void		find_dist_y(t_rc_main *m, float ray_dir_x, float ray_dir_y)
{
	int		hit;

	hit = 0;
	m->flr.step_x = step_x_calculate(m, ray_dir_x);
	m->flr.step_y = step_y_calculate(m, ray_dir_y);
	while (hit == 0)
	{
		if (m->flr.side_dist_x < m->flr.side_dist_y)
		{
			m->flr.side_dist_x += m->player.delta_dist_x;
			m->wls.map_x += m->flr.step_x;
			m->wls.side = 0;
		}
		else
		{
			m->flr.side_dist_y += m->player.delta_dist_y;
			m->wls.map_y += m->flr.step_y;
			m->wls.side = 1;
		}
		if (m->map[m->wls.map_x][m->wls.map_y] > 0)
			hit = 1;
	}
	wall_dist_and_hit_x_calculate(m, ray_dir_x, ray_dir_y);
	m->flr.hit_x -= floorf((m->flr.hit_x));
}