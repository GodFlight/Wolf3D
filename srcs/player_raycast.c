
#include "wolf3d.h"
#include "debug_log.h"

int		draw_celling(t_sdl *sdl, float h_colum, int i)
{
	int y;
	float offset;

	offset = (WIN_HEIGHT / 2 - h_colum / 2);
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
	while (y < WIN_HEIGHT)
	{
		sdl_put_pixel(sdl, i, y, DGRAY);
		y++;
	}
}

void	processing_big_colum(t_wolf *wlf, t_sdl *sdl, float h_colum, int i)
{
	int		tmp_y;
	int		y;
	float relation;

	relation = COLUM / h_colum;
	wlf->ray.eps = 0.01f;
	tmp_y = (int)((h_colum - WIN_HEIGHT) / 2);
	y = -1;
	if (wlf->ray.hitx < wlf->ray.eps || (wlf->ray.hitx > wlf->ray.hity
								&& wlf->ray.hity > wlf->ray.eps))
		wlf->ray.hitx = wlf->ray.hity;
	while (++y < WIN_HEIGHT)
	{
		if (wlf->map[(int)wlf->ray.y][(int)wlf->ray.x] == 1)
		{
			sdl_put_pixel(sdl, i, y, *((int *)sdl->img.data
			+ ((int)(wlf->ray.hitx * COLUM + (int)(tmp_y * relation)
			* sdl->img.width))));
			tmp_y++;
		}
		else if (wlf->map[(int)wlf->ray.y][(int)wlf->ray.x] == 2)
			sdl_put_pixel(sdl, i, y, RED);
	}
}

void	draw_colum(t_wolf *wlf, t_sdl *sdl, float h_colum, int i)
{
	int 	y;
	float 	offset;
	int 	tmp_y;
	float 	relation;

	tmp_y = 0;
	relation = COLUM / h_colum;
	y = draw_celling(sdl, h_colum, i);
	offset = WIN_HEIGHT / 2 + h_colum / 2;
	if (wlf->ray.hitx < wlf->ray.eps || (wlf->ray.hitx > wlf->ray.hity
										&& wlf->ray.hity > wlf->ray.eps))
		wlf->ray.hitx = wlf->ray.hity;
	while (y < offset - 1)
	{
		if (wlf->map[(int) wlf->ray.y][(int) wlf->ray.x] == 1)
		{
			sdl_put_pixel(sdl, i, y,
					 *((int *) sdl->img.data +	((int) (wlf->ray.hitx * COLUM
					 + (int) (tmp_y * relation) * sdl->img.width))));
			tmp_y++;
		}
		else if (wlf->map[(int) wlf->ray.y][(int) wlf->ray.x] == 2)
			sdl_put_pixel(sdl, i, y, RED);
		y++;
	}
	draw_floor(sdl, i, y);
}

void 	player_raycast(t_wolf *wlf, t_sdl *sdl)
{
    float	cs;
    float 	sn;
    int		i;

    i = 0;
    while (i < WIN_WIDTH)
    {
    	wlf->ray.angle = (wlf->player.view_dir - FOV / 2)
    			+ (FOV * i / WIN_WIDTH);
		wlf->ray.distance = 0.f;
		cs = cos(wlf->ray.angle);
		sn = sin(wlf->ray.angle);
		while (wlf->ray.distance < 15.0f)
		{
			wlf->ray.x = wlf->player.x + wlf->ray.distance * cs;
			wlf->ray.y = wlf->player.y + wlf->ray.distance * sn;
			if ((wlf->map[(int)wlf->ray.y][(int)wlf->ray.x] != 0))
				break;
//			sdl_put_pixel(sdl, (int)(wlf->ray.x * MAP_SCALE), (int)(wlf->ray.y * MAP_SCALE), BLUE);
			wlf->ray.distance += 0.01f;
		}
		wlf->ray.colum = WIN_HEIGHT / (wlf->ray.distance
				* cos(wlf->ray.angle - wlf->player.view_dir));
		wlf->ray.hitx = (wlf->ray.x - (int)wlf->ray.x);
		wlf->ray.hity = (wlf->ray.y - (int)wlf->ray.y);
		if (wlf->ray.colum > WIN_HEIGHT)
			processing_big_colum(wlf, sdl, wlf->ray.colum, i);
		else
			draw_colum(wlf, sdl, wlf->ray.colum, i);
//		SDL_Log("%sRAY ID: %3d | %sY: %3f | %sX: %3f\n", KGRN,  i, KYEL, wlf->ray.y, KBLU, wlf->ray.x);
		i++;
	}
}
