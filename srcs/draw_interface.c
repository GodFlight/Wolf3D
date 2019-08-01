#include "wolf3d.h"

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
				sdl_put_pixel(sdl, wlf->player.x * MAP_SCALE, wlf->player.y * MAP_SCALE, GREEN);
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
}
