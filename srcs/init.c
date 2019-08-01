#include "wolf3d.h"

t_wolf	*wolf_init(t_sdl *sdl)
{
	t_wolf	*wolf;

	if (!(wolf = (t_wolf *)ft_memalloc(sizeof(t_wolf))))
		exit(20);
	wolf->ray.colum = 0.f;
	wolf->player.y = 1.4f;
	wolf->player.x =  1.4f;
	wolf->player.view_dir = 0.5f;
	wolf->ray.eps = 0.01f;
	wolf->sdl = sdl;
	return (wolf);
}

void	sdl_texture_load(t_sdl *sdl)
{
	sdl->img.data = stbi_load("../textures/wall01.bmp",
			&sdl->img.width, &sdl->img.height, &sdl->img.bpp, 0);
}

t_sdl	*sdl_init(void)
{
	t_sdl		*sdl;

	if (!(sdl = (t_sdl *)ft_memalloc(sizeof(t_sdl))))
		exit(23);
	if (!(sdl->data = (int *)ft_memalloc(sizeof(int) * (WIN_HEIGHT * WIN_WIDTH))))
		exit(23);
	if ((SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER)))
		exit(2);
	sdl->win = SDL_CreateWindow("Wolf3D", 100, 100, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_RESIZABLE);
	if (NULL == sdl->win)
		exit (1);
	if (!(sdl->renderer = SDL_CreateRenderer(sdl->win, -1, 0)))
		exit (2);
	if (!(sdl->texture = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_STATIC, WIN_WIDTH, WIN_HEIGHT)))
		exit(3);
	sdl->state = SDL_GetKeyboardState(NULL);
	sdl_texture_load(sdl);
	return (sdl);
}
