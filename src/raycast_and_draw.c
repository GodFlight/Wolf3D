/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_and_draw.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 00:57:48 by rkeli             #+#    #+#             */
/*   Updated: 2019/08/10 17:27:11 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"
#include "debug_log.h"

int		**choose_side(t_rc_main *m, int **tmp_arr)
{
	int		index;

	index = m->map[(int)(m->ray.y)][(int)(m->ray.x)];
	index = (index == 0 ? 1 : m->map[(int)(m->ray.y)][(int)(m->ray.x)]);
	if (m->ray.hitx < m->ray.eps)
		tmp_arr = (m->walls[index]).texture3;
	else if (m->ray.hitx > m->ray.hity && m->ray.hity > m->ray.eps)
		tmp_arr = (m->walls[index]).texture4;
	else if (m->ray.hity > m->ray.eps)
		tmp_arr = (m->walls[index]).texture1;
	else if (m->ray.x != 0 || m->ray.y != 0)
		tmp_arr = (m->walls[index]).texture2;
	return (tmp_arr);
}

int			draw_celling(t_sdl *sdl, float h_colum, int i)
{
	int		y;
	float	offset;

	offset = (sdl->win_h / 2 - h_colum / 2);
	offset = offset > 0 ? offset : 1;
	y = 0;
	while (y < (int)offset)
	{
		sdl_put_pixel(sdl, i, y, 12000000);
		y++;
	}
	return (y);
}

void		draw_floor(t_sdl *sdl, int i, int y, t_rc_main *m)
{
	int **tmp_arr;

	tmp_arr = (m->walls[3]).texture2;
	float dist = (float)(sdl->win_w / 2 / tan(FOV / 2));
	while (y < sdl->win_h)
	{
		float row = ABS(y - sdl->win_h / 2);
//		float hz = (dist * PLAYER_HEIGHT * 2) / row / cosf(m->ray.angle - m->player.view_dir);
		float hz = (dist * PLAYER_HEIGHT * 2) / row;
//		y = y >= 0 ?
		sdl_put_pixel(sdl, i, y, tmp_arr[(int)hz % 64][i % 64]);
		y++;
	}
}

void		processing_big_column(t_rc_main *m, float h_colum, int i, int **tmp_arr)
{
	int		tmp_y;
	int		y;
	float   relation;

	relation = COLUM / h_colum;
	tmp_y = (int)((h_colum - m->sdl->win_h) / 2);
	y = -1;
	if (m->ray.hitx < m->ray.eps || (m->ray.hitx > m->ray.hity
									 && m->ray.hity > m->ray.eps))
		m->ray.hitx = m->ray.hity;
	while (++y < m->sdl->win_h)
	{
		sdl_put_pixel(m->sdl, i, y,
				tmp_arr[(int)(tmp_y * relation)][(int)(m->ray.hitx * COLUM)]);
		tmp_y++;
	}
}

static void	draw_column(t_rc_main *m, float h_colum, int i, int **tmp_arr)
{
	int 	tmp_y;
	int 	y;
	float 	offset;
	float 	relation;

	tmp_y = 0;
	relation = COLUM / h_colum;
	y = draw_celling(m->sdl, h_colum, i);
	offset = m->sdl->win_h / 2 + h_colum / 2;
	if (m->ray.hitx < m->ray.eps || (m->ray.hitx > m->ray.hity
									 && m->ray.hity > m->ray.eps))
		m->ray.hitx = m->ray.hity;
	while (y < offset - 1)
	{
		sdl_put_pixel(m->sdl, i, y,
				tmp_arr[(int)(tmp_y * relation)][(int)(m->ray.hitx * COLUM)]);
		tmp_y++;
		y++;
	}
	while (y < m->sdl->win_h)
	{
        sdl_put_pixel(m->sdl, i, y, 120);
        y++;
    }
//	draw_floor(m->sdl, i, y, m);
}

//void raycast

void		raycast_and_draw(t_rc_main *m)
{
	int		i;
	float	camera_x;
	float	ray_dir_x;
	float	ray_dir_y;
	int		w = m->sdl->win_w;
	int		h = m->sdl->win_h;
	int		map_x;
	int		map_y;
	float	side_dist_x;
	float	side_dist_y;
	float	delta_dist_x;
	float	delta_dist_y;
	float	wall_dist;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	int		line_h;
	int		draw_start;
	int		draw_end;

	i = -1;
	while (++i < w)
	{
		map_x = (int)m->player.x;
		map_y = (int)m->player.y;
		hit = 0;
		camera_x = 2.f * i / (float)w - 1.f;
		ray_dir_x = m->player.fdir_x + m->player.plane_x * camera_x;
		ray_dir_y = m->player.fdir_y + m->player.plane_y * camera_x;
		delta_dist_x = sqrtf(1 + (ray_dir_y * ray_dir_y) / (ray_dir_x * ray_dir_x));
		delta_dist_y = sqrtf(1 + (ray_dir_x * ray_dir_x) / (ray_dir_y * ray_dir_y));
		//it must work, but it not
//		delta_dist_x = abs(1.f / ray_dir_x);
//		delta_dist_y = abs(1.f / ray_dir_y);
		if (ray_dir_x < 0)
		{
			step_x = -1;
			side_dist_x = (m->player.x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1 - m->player.x) * delta_dist_x;
		}
		if (ray_dir_y < 0)
		{
			step_y = -1;
			side_dist_y = (m->player.y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1 - m->player.y) * delta_dist_y;
		}
		while (hit == 0)
		{
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			if (m->map[map_x][map_y] > 0)
				hit = 1;
		}
		if (side == 0)
			wall_dist = (map_x - m->player.x + (1 - step_x) / 2) / ray_dir_x;
		else
			wall_dist = (map_y - m->player.y + (1 - step_y) / 2) / ray_dir_y;
		line_h = (int)(h / wall_dist);
		draw_start = -line_h / 2 + h / 2;
		if (draw_start < 0)
			draw_start = 0;
		draw_end = line_h / 2 + h / 2;
		if (draw_end >= h)
			draw_end = h - 1;
		int j = -1;
		while (++j < draw_start)
			sdl_put_pixel(m->sdl, i, j, 0);
		int color;
		if (m->map[map_x][map_y] > 0 && m->map[map_x][map_y] <= 2)
			color = 200000;
		else if (m->map[map_x][map_y] > 2 && m->map[map_x][map_y] <= 4)
			color = 299999912;
		else
			color = 10000000;
		while (j < draw_end)
		{
			sdl_put_pixel(m->sdl, i, j, color);
			j++;
		}
		while (j < h)
		{
			sdl_put_pixel(m->sdl, i, j, 0);
			j++;
		}

//		column = m->sdl->win_h / (m->ray.distance
//							  * cosf(m->ray.angle - m->player.view_dir));
//		m->ray.hitx = (m->ray.x - (int)(m->ray.x));
//		m->ray.hity = (m->ray.y - (int)(m->ray.y));
//		tmp_arr = choose_side(m, tmp_arr);
//		draw_column(m, column, i, tmp_arr);*/
//		SDL_Log("%sRAY ID: %3d | %sY: %3f | %sX: %3f\n", KGRN,  i, KYEL, wlf->ray.y, KBLU, wlf->ray.x);
	}
}
