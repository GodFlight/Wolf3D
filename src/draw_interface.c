#include "wolf3d.h"

void	draw_ray(t_sdl *sdl, t_wolf *wlf)
{
	t_interface	intf;
	float		cs;
	float		sn;
	int			i;

	i = 0;
	while (i < WIN_WIDTH)
	{
		intf.angle = (wlf->player.view_dir - FOV / 2)
						 + (FOV * i / WIN_WIDTH);
		intf.distance = 0.f;
		cs = cos(intf.angle);
		sn = sin(intf.angle);
		while (intf.distance < 15.0f)
		{
			intf.x = wlf->player.x + intf.distance * cs;
			intf.y = wlf->player.y + intf.distance * sn;
			if ((wlf->map[(int)intf.y][(int)intf.x] != 0))
				break;
			sdl_put_pixel(sdl, (int)(intf.x * MAP_SCALE), (int)(intf.y
			* MAP_SCALE), BLUE);
			intf.distance += 0.03f;
		}
		i++;
	}
}

void	draw_map(t_sdl *sdl, t_wolf *wlf)
{
	int y;
	int x;

	y = 0;
	while (y < wlf->len_ymap * MAP_SCALE)
	{
		x = 0;
		while (x < wlf->len_xmap * MAP_SCALE)
		{
			if (wlf->player.y && wlf->player.x)
				sdl_put_pixel(sdl, wlf->player.x * MAP_SCALE, wlf->player.y
				* MAP_SCALE, GREEN);
			if (wlf->map[y / MAP_SCALE][x / MAP_SCALE] == 0)
				sdl_put_pixel(sdl, x, y, WHITE);
			else if (wlf->map[y / MAP_SCALE][x / MAP_SCALE] > 0)
				sdl_put_pixel(sdl, x, y, GREEN);
			x++;
		}
		y++;
	}
}

void	draw_interface(t_sdl *sdl, t_wolf *wlf)
{
	draw_map(sdl, wlf);
	draw_ray(sdl, wlf);
}
