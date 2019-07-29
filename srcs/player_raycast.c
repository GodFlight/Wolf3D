
#include "wolf3d.h"
#include "debug_log.h"

void	drow_colum(t_wolf *wlf, t_sdl *sdl, float colum, int i)
{
	int y;

	y = WIN_HEIGHT / 1.2;
//	y = 0;
	float test = (WIN_HEIGHT / 2 - colum / 2);
//	while(y > WIN_HEIGHT / 2)
	test = test > 0 ? test : 1;
	while(y > test)
	{
		if (wlf->map[(int)wlf->ray.y][(int)wlf->ray.x] == 1)
			sdl_put_pixel(sdl, WIN_WIDTH / 4 + i, y, BLUE);
		else if (wlf->map[(int)wlf->ray.y][(int)wlf->ray.x] == 2)
			sdl_put_pixel(sdl, WIN_WIDTH / 4 + i, y, RED);
		y--;
	}
	SDL_Log("test %f\n", test);
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
		while (wlf->ray.distance < 10.0f)
		{
			wlf->ray.x = wlf->player.x + wlf->ray.distance * cs;
			wlf->ray.y = wlf->player.y + wlf->ray.distance * sn;
			if (wlf->ray.y >= wlf->len_ymap || wlf->ray.x >= wlf->len_xmap || wlf->ray.y <= 0 || wlf->ray.x <= 0
				|| (wlf->map[(int)wlf->ray.y][(int)wlf->ray.x] != 0))
				break;
//			else if ((wlf->ray.y >= wlf->len_ymap || wlf->ray.x >= wlf->len_xmap || wlf->ray.y <= 0 || wlf->ray.x <= 0
//					  || (wlf->map[(int)wlf->ray.y][(int)wlf->ray.x] == 0)))
			sdl_put_pixel(sdl, (int)(wlf->ray.x * MAP_SCALE), (int)(wlf->ray.y * MAP_SCALE), BLUE);
			wlf->ray.distance += 0.01f;
		}
		wlf->ray.colum = WIN_HEIGHT / (wlf->ray.distance * cos(wlf->ray.angle - wlf->player.view_dir));
//		wlf->ray.colum = WIN_HEIGHT / (wlf->ray.distance);
		drow_colum(wlf, sdl, wlf->ray.colum, i);
//		SDL_Log("%sRAY ID: %3d | %sY: %3f | %sX: %3f\n", KGRN,  i, KYEL, wlf->ray.y, KBLU, wlf->ray.x);
		i++;
	}
}

