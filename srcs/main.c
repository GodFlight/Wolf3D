//
// Created by Racquel Keli on 2019-07-22.
//

#include "wolf3d.h"

int			rgb_to_hex(int r, int g, int b)
{
	int		res = 0;
	int		alpha = 0;

	alpha |= 16777215;
	res = r << 16 | g << 8 | b;
	res &= alpha;
	return (res);
}

void	sdl_put_pixel(t_sdl *sdl, int x, int y, int color)
{
	if ((x >= 0 && x < WIN_WIDTH) && (y >= 0 && y < WIN_HEIGHT))
		sdl->data[x + y * WIN_WIDTH] = color;
}

void	sdl_init(t_sdl *sdl, t_wolf *wlf)
{
	int			running;

	running = 1;
	if ((SDL_Init(SDL_INIT_VIDEO)))
		exit(2);
	sdl->win = SDL_CreateWindow("Wolf3D", 100, 100, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_RESIZABLE);
	if (NULL == sdl->win)
		exit (1);
	sdl->renderer = SDL_CreateRenderer(sdl->win, -1, 0);
	sdl->texture = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STATIC, WIN_WIDTH, WIN_HEIGHT);
//	sdl->screen = SDL_GetWindowSurface(sdl->win);
	while (running)
	{
		drow_map(sdl, wlf);
		player_raycast(wlf, sdl);
		SDL_UpdateTexture(sdl->texture, NULL, sdl->data, WIN_WIDTH * sizeof(int));
		SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, NULL);
		SDL_RenderPresent(sdl->renderer);
		while(SDL_PollEvent(&sdl->event))
		{
			player_movenet(wlf, sdl);
			if ((SDL_QUIT == sdl->event.type) ||
				(SDL_KEYDOWN == sdl->event.type &&
				 SDL_SCANCODE_ESCAPE == sdl->event.key.keysym.scancode))
				running = 0;
		}
		SDL_RenderClear(sdl->renderer);
	}
	SDL_RenderClear(sdl->renderer);
	SDL_DestroyTexture(sdl->texture);
	SDL_DestroyWindow(sdl->win);
	SDL_Quit();
}

void	wolf_init(t_wolf *wlf)
{
//    wlf->player.x = 3.2f;
//    wlf->player.y = 2.4f;
//    wlf->player.y = 3.f;
//    wlf->player.x = 3.f;
	wlf->ray.colum = 0.f;
    wlf->player.y = 1.4f;
    wlf->player.x =  1.4f;
//    wlf->player.view_dir = 1.2f;
    wlf->player.view_dir = 0.500f;
//    wlf->player.view_dirx = f;
//    wlf->player.view_dir = 1.2f;
	map_read(wlf);
}

int		main(void)
{

	t_wolf	*wlf;
	t_sdl	sdl;

	if (!(wlf = (t_wolf*)malloc(sizeof(t_wolf))))
		exit(20);
	if (!(sdl.data = (int*)malloc(sizeof(int) * (WIN_HEIGHT * WIN_WIDTH))))
		exit(23);
	wolf_init(wlf);
	sdl_init(&sdl, wlf);

	return (0);
}