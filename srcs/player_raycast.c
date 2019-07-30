
#include "wolf3d.h"
#include "debug_log.h"

void 	drow_celling(t_wolf *wlf, t_sdl *sdl, int i)
{
	float x;
	float y;

	float offset = (WIN_HEIGHT / 2 - wlf->ray.colum / 2);
	y = WIN_HEIGHT;
//	x = wlf->ray.x;
	offset = offset > 0 ? offset : 1;
	while (offset > 0)
	{
		sdl_put_pixel(sdl, (int)(WIN_WIDTH / 4 + i + 25), (int)offset, DGRAY);
		offset--;
	}
}

void 	drow_floor(t_wolf *wlf, t_sdl *sdl, int i)
{
	float x;
	float y;

	float offset = (WIN_HEIGHT / 2 + wlf->ray.colum / 2);
	y = WIN_HEIGHT;
	offset = offset > 0 ? offset : 1;
	while (y > offset)
	{
		sdl_put_pixel(sdl, (int)(WIN_WIDTH / 4 + i + 25), (int)y, GRAY);
		y--;
	}

}

void	drow_colum(t_wolf *wlf, t_sdl *sdl, float colum, int i)
{
	int		y;
	float	offset;

	y = WIN_HEIGHT / 2;
	offset = (WIN_HEIGHT / 2 - colum / 2);
	offset = offset > 0 ? offset : 1;
	while(y > offset)
	{
		if (wlf->map[(int)wlf->ray.y][(int)wlf->ray.x] == 1)
			sdl_put_pixel(sdl, WIN_WIDTH / 4 + i + 25, y, BLUE);
		else if (wlf->map[(int)wlf->ray.y][(int)wlf->ray.x] == 2)
			sdl_put_pixel(sdl, WIN_WIDTH / 4 + i + 25, y, RED);
		y--;
	}
	y = WIN_HEIGHT / 2;
	offset = (WIN_HEIGHT / 2 + colum / 2);
	offset = offset > 0 ? offset : 1;
	while(y < offset)
	{
		if (wlf->map[(int)wlf->ray.y][(int)wlf->ray.x] == 1)
			sdl_put_pixel(sdl, WIN_WIDTH / 4 + i + 25, y, BLUE);
		else if (wlf->map[(int)wlf->ray.y][(int)wlf->ray.x] == 2)
			sdl_put_pixel(sdl, WIN_WIDTH / 4 + i + 25, y, RED);
		y++;
	}
}

void 	player_raycast(t_wolf *wlf, t_sdl *sdl)
{
    float	cs;
    float 	sn;
    float	fov;
    int		i;

    i = 0;
    fov = M_PI / 3;
    while (i < WIN_WIDTH)
    {
    	wlf->ray.angle = (wlf->player.view_dir - fov / 2) + (fov * i / WIN_WIDTH);
		wlf->ray.distance = 0.f;
		cs = cos(wlf->ray.angle);
		sn = sin(wlf->ray.angle);
		while (wlf->ray.distance < 15.0f)
		{
			wlf->ray.x = wlf->player.x + wlf->ray.distance * cs;
			wlf->ray.y = wlf->player.y + wlf->ray.distance * sn;
			if (wlf->ray.y >= wlf->len_ymap || wlf->ray.x >= wlf->len_xmap || wlf->ray.y <= 0 || wlf->ray.x <= 0
				|| (wlf->map[(int)wlf->ray.y][(int)wlf->ray.x] != 0))
				break;
			sdl_put_pixel(sdl, (int)(wlf->ray.x * MAP_SCALE), (int)(wlf->ray.y * MAP_SCALE), BLUE);
			wlf->ray.distance += 0.01f;
		}
		wlf->ray.colum = WIN_HEIGHT / (wlf->ray.distance * cos(wlf->ray.angle - wlf->player.view_dir));
		drow_colum(wlf, sdl, wlf->ray.colum, i);
		drow_floor(wlf, sdl, i);
		drow_celling(wlf, sdl, i);
//		SDL_Log("%sRAY ID: %3d | %sY: %3f | %sX: %3f\n", KGRN,  i, KYEL, wlf->ray.y, KBLU, wlf->ray.x);
		i++;
	}
}
