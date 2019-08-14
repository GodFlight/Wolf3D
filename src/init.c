#include "raycast.h"

static t_sdl	*sdl_init(void)
{
	t_sdl		*sdl;

	if (!(sdl = (t_sdl *)ft_memalloc(sizeof(t_sdl))))
		exit(23);
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER) < 0 ||
		IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) < 0)
		exit(2);
	sdl->state = SDL_GetKeyboardState(NULL);
	return (sdl);
}

t_rc_main	*rc_main_init(void)
{
	t_rc_main	*m;

	if (!(m = (t_rc_main *)ft_memalloc(sizeof(t_rc_main))))
		exit(20);
	//TODO IT'S JSON WORK!
	m->player.y = 1.6f;
	m->player.x = 1.6f;
	m->player.fdir_x = -1.f;
	m->player.fdir_y = 0.f;
	m->player.rdir_x = 0.f;
	m->player.rdir_y = 1.f;
	m->player.plane_x = 0;
	m->player.plane_y = 0.66f;
//	m->flr.eps = 0.01f;
	m->objects_num = 0;
	///////////////////////
	m->sdl = sdl_init();
	return (m);
}
