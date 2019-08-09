/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_raycast.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 00:57:48 by rkeli             #+#    #+#             */
/*   Updated: 2019/08/09 11:54:32 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "raycast.h"
#include "debug_log.h"

int		draw_celling(t_sdl *sdl, float h_colum, int i)
{
	int y;
	float offset;

	offset = (sdl->win_h / 2 - h_colum / 2);
	offset = offset > 0 ? offset : 1;
	y = 0;
	while (y < (int)offset)
	{
		sdl_put_pixel(sdl, i, y, DGRAY);
		y++;
	}
	return (y);
}

void	draw_floor(t_sdl *sdl, int i, int y)
{
	while (y < sdl->win_h)
	{
		sdl_put_pixel(sdl, i, y, DGRAY);
		y++;
	}
}

void	processing_big_column(t_rc_main *m, float h_colum, int i)
{
	int 	**tmp_arr;
	int		index;
	int		tmp_y;
	int		y;
	float   relation;

	relation = COLUM / h_colum;
	tmp_y = (int)((h_colum - m->sdl->win_h) / 2);
	y = -1;
	index = m->map[(int)(m->ray.y)][(int)(m->ray.x)];
	index = (index == 0 ? 1 : index);
	tmp_arr = ((t_wall *)m->objs[index].data)->state1->texture_north;
	if (m->ray.hitx < m->ray.eps || (m->ray.hitx > m->ray.hity
									 && m->ray.hity > m->ray.eps))
		m->ray.hitx = m->ray.hity;
	while (++y < m->sdl->win_h)
	{
		sdl_put_pixel(m->sdl, i, y, tmp_arr[(int)(tmp_y * relation)][(int)(m->ray.hitx * COLUM)]);
		tmp_y++;
	}
}

static void	draw_column(t_rc_main *m, float h_colum, int i)
{
	int 	**tmp_arr;
	int 	index;
	int 	tmp_y;
	int 	y;
	float 	offset;
	float 	relation;

	tmp_y = 0;
	relation = COLUM / h_colum;
	y = draw_celling(m->sdl, h_colum, i);
	offset = m->sdl->win_h / 2 + h_colum / 2;
	index = m->map[(int)(m->ray.y)][(int)(m->ray.x)];
	index = (index == 0 ? 1 : index);
	tmp_arr = ((t_wall *)m->objs[index].data)->state1->texture_north;
	if (m->ray.hitx < m->ray.eps || (m->ray.hitx > m->ray.hity
									 && m->ray.hity > m->ray.eps))
		m->ray.hitx = m->ray.hity;
	while (y < offset - 1)
	{
		sdl_put_pixel(m->sdl, i, y, tmp_arr[(int)(tmp_y * relation)][(int)(m->ray.hitx * COLUM)]);
		tmp_y++;
		y++;
	}
	draw_floor(m->sdl, i, y);
}

void 	player_raycast(t_rc_main *m)
{
    float	cs;
    float 	sn;
    int		i;
    float	column;

    i = 0;
    while (i < m->sdl->win_w)
    {
		m->ray.angle = (m->player.view_dir - FOV / 2)
					   + (FOV * i / m->sdl->win_w);
		m->ray.distance = 0.f;
		cs = cos(m->ray.angle);
		sn = sin(m->ray.angle);
		while (m->ray.distance < 15.0f)
		{
			m->ray.x = m->player.x + m->ray.distance * cs;
			m->ray.y = m->player.y + m->ray.distance * sn;
			if ((m->map[(int)m->ray.y][(int)m->ray.x] != 0))
				break;
			m->ray.distance += 0.01f;
		}
		column = m->sdl->win_h / (m->ray.distance
							  * cos(m->ray.angle - m->player.view_dir));
		m->ray.hitx = (m->ray.x - (int)m->ray.x);
		m->ray.hity = (m->ray.y - (int)m->ray.y);
		if (column > m->sdl->win_h)
			processing_big_column(m, column, i);
		else
			draw_column(m, column, i);
//		SDL_Log("%sRAY ID: %3d | %sY: %3f | %sX: %3f\n", KGRN,  i, KYEL, wlf->ray.y, KBLU, wlf->ray.x);
		i++;
	}
}
