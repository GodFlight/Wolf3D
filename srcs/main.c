#define STB_IMAGE_IMPLEMENTATION
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
	sdl->img.data = stbi_load("/Users/rkeli/Desktop/Wolf3D/textures/wall01.bmp",
			&sdl->img.width, &sdl->img.height, &sdl->img.bpp, 0);
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
	if (!(sdl->texture = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, WIN_WIDTH, WIN_HEIGHT)))
		exit(3);
	sdl_texture_load(sdl);
}

void	print_image(t_sdl *sdl)
{
	int x;
	int y;

	y = 0;
	while (y < sdl->img.height)
	{
		x = 0;
		while (x < sdl->img.width)
		{
			sdl->data[x + y * WIN_WIDTH] = *((int*)sdl->img.data + (x + y * sdl->img.width));
			x++;
		}
		y++;
	}
//	printf("y : [%i]\n", y);
}

void	sdl_loop(t_sdl *sdl, t_wolf *wlf)
{
	int			running;

	running = 1;
	while (running)
	{

		drow_map(sdl, wlf);
		player_raycast(wlf, sdl);
		print_image(sdl);
		SDL_UpdateTexture(sdl->texture, NULL, (void *)sdl->data, WIN_WIDTH * sizeof(int));
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
	wolf_init(wlf);
	sdl_init(&sdl);
	sdl_loop(&sdl, wlf);

	return (0);
}