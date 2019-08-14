/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_interface.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 00:57:35 by rkeli             #+#    #+#             */
/*   Updated: 2019/08/14 11:08:06 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

//static void	draw_ray(t_rc_main *m)
//{
//	t_interface	intf;
//	float		cs;
//	float		sn;
//	int			i;
//
//	i = 0;
//	while (i < m->sdl->win_w)
//	{
//		intf.angle = (1 - FOV / 2)
//						 + (FOV * i / m->sdl->win_w);
//		intf.distance = 0.f;
//		cs = cos(intf.angle);
//		sn = sin(intf.angle);
//		while (intf.distance < 15.0f)
//		{
//			intf.x = m->player.x + intf.distance * cs;
//			intf.y = m->player.y + intf.distance * sn;
//			if ((m->map[(int)intf.y][(int)intf.x] != 0))
//				break;
//			sdl_put_pixel(m->sdl, (int)(intf.x * MAP_SCALE), (int)(intf.y
//			* MAP_SCALE), BLUE);
//			intf.distance += 0.03f;
//		}
//		i++;
//	}
//}
//
//static void	draw_map(t_rc_main *m)
//{
//	int y;
//	int x;
//
//	y = 0;
//	while (y < m->map_h * MAP_SCALE)
//	{
//		x = 0;
//		while (x < m->map_w * MAP_SCALE)
//		{
//			if (m->player.y && m->player.x)
//				sdl_put_pixel(m->sdl, m->player.x * MAP_SCALE,
//						m->player.y * MAP_SCALE, GREEN);
//			if (m->map[y / MAP_SCALE][x / MAP_SCALE] == 0)
//				sdl_put_pixel(m->sdl, x, y, WHITE);
//			else if (m->map[y / MAP_SCALE][x / MAP_SCALE] > 0)
//				sdl_put_pixel(m->sdl, x, y, GREEN);
//			x++;
//		}
//		y++;
//	}
//}
//
//void	draw_interface(t_rc_main *m)
//{
//	draw_map(m);
//	draw_ray(m);
//}
