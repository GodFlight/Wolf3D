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

void	sdl_texture_load(t_sdl *sdl)
{
	SDL_Surface	*surface;

	if (!(sdl->texture_pack = ft_memalloc(sizeof(SDL_Surface *) * 4)))
		exit (4);
	if (!(sdl->texture_pack[0] = SDL_LoadBMP("/Users/rkeli/Desktop/Wolf3D/textures/WALL2.bmp")))
		exit (5);
	if (!(sdl->texture_pack[1] = SDL_LoadBMP("/Users/rkeli/Desktop/Wolf3D/textures/WALL5.bmp")))
		exit (6);
	if (!(sdl->texture_pack[2] = SDL_LoadBMP("/Users/rkeli/Desktop/Wolf3D/textures/WALL6.bmp")))
		exit (7);
	if (!(sdl->texture_pack[3] = SDL_LoadBMP("/Users/rkeli/Desktop/Wolf3D/textures/WALL7.bmp")))
		exit (8);

//	if (!(sdl->texture_pack = ft_memalloc(sizeof(SDL_Texture *) * 4)))
//		exit(4);
//	if (!(surface = SDL_LoadBMP("/Users/rkeli/Desktop/Wolf3D/textures/WALL2.bmp")) ||
//		!(sdl->texture_pack[0] = SDL_CreateTextureFromSurface(sdl->renderer, surface)))
//		exit(5);
//	SDL_FreeSurface(surface);
//	if (!(surface = SDL_LoadBMP("/Users/rkeli/Desktop/Wolf3D/textures/WALL5.bmp")) ||
//		!(sdl->texture_pack[1] = SDL_CreateTextureFromSurface(sdl->renderer, surface)))
//		exit(6);
//	SDL_FreeSurface(surface);
//	if (!(surface = SDL_LoadBMP("/Users/rkeli/Desktop/Wolf3D/textures/WALL6.bmp")) ||
//		!(sdl->texture_pack[2] = SDL_CreateTextureFromSurface(sdl->renderer, surface)))
//		exit(7);
//	SDL_FreeSurface(surface);
//	if (!(surface = SDL_LoadBMP("/Users/rkeli/Desktop/Wolf3D/textures/WALL7.bmp")) ||
//		!(sdl->texture_pack[3] = SDL_CreateTextureFromSurface(sdl->renderer, surface)))
//		exit(8);
//	SDL_FreeSurface(surface);
}

void	sdl_init(t_sdl *sdl)
{
	if ((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER)))
		exit(2);
//	if (SDL_Init(SDL_INIT_EVERYTHING))
//		exit(2);
	sdl->win = SDL_CreateWindow("Wolf3D", 100, 100, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_RESIZABLE);
	if (NULL == sdl->win)
		exit (1);
	if (!(sdl->renderer = SDL_CreateRenderer(sdl->win, -1, 0)))
		exit (2);
	if (!(sdl->texture = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, WIN_WIDTH, WIN_HEIGHT)))
		exit(3);
	sdl_texture_load(sdl);
}

void test(t_sdl *sdl, t_wolf *wlf)
{
//	void *pixels = 0;
//	int pitch = 0;
	int i = 0;
	int j = 0;

//	SDL_Log("huita: %d\n", SDL_LockTexture(sdl->texture_pack[0], NULL, &pixels, &pitch));
//	SDL_Log("ERROR: %s", SDL_GetError());
	int pitch = sdl->texture_pack[0]->pitch;
//	int test = (int)sdl->texture_pack[0]->pixels[0]	;
	SDL_LockSurface(sdl->texture_pack[0]);
	while (i < sdl->texture_pack[0]->pitch)
	{
		int *a = (int*)sdl->texture_pack[0]->pixels;
//		while (j < 64)
//		{
			sdl_put_pixel(sdl, i + 20, 30, a[i]);
			sdl_put_pixel(sdl, i + 20, 31, a[i + 30]);
			sdl_put_pixel(sdl, i + 20, 32, a[i + 60]);
//			j++;
//		}
		i++;
	}
	SDL_Log("%d\n", (int)sdl->texture_pack[0]->pixels);
	SDL_UnlockSurface(sdl->texture_pack[0]);
//	SDL_UnlockTexture(sdl->texture_pack[0]);
}

void	sdl_loop(t_sdl *sdl, t_wolf *wlf)
{
	int			running;
	int 		y;
	int 		x;

	running = 1;
	while (running)
	{
		drow_map(sdl, wlf);
		player_raycast(wlf, sdl);
//		test(sdl, wlf);
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
	}
//		SDL_RenderClear(sdl->renderer);
//	int i;
//
//	i = 0;
//	while (i < 3)
//	{
//		SDL_FreeSurface(sdl->texture_pack[0]);
//		i++;
//	}
	SDL_RenderClear(sdl->renderer);
	SDL_DestroyTexture(sdl->texture);
	SDL_DestroyWindow(sdl->win);
	SDL_Quit();
}

void	wolf_init(t_wolf *wlf)
{
	wlf->ray.colum = 0.f;
    wlf->player.y = 1.4f;
    wlf->player.x =  1.4f;
    wlf->player.view_dir = 0.500f;
	map_read(wlf);
}

int		main(void)
{
	t_wolf	*wlf;
	t_sdl	sdl;

	if (!(wlf = (t_wolf *)ft_memalloc(sizeof(t_wolf))))
		exit(20);
	if (!(sdl.data = (int *)ft_memalloc(sizeof(int) * (WIN_HEIGHT * WIN_WIDTH))))
		exit(23);
//	if (!(sdl.event = (SDL_Event*)malloc(sizeof(SDL_Event))))
//		exit(24);
	wolf_init(wlf);
	sdl_init(&sdl);
	sdl_loop(&sdl, wlf);

	return (0);
}