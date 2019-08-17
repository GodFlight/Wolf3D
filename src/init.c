#include "raycast.h"

t_rc_main	*rc_main_init(void)
{
	t_rc_main	*m;
	t_sdl		*sdl;

	if (!(m = (t_rc_main *)ft_memalloc(sizeof(t_rc_main))))
		exit(20);
	if (!(sdl = (t_sdl *)ft_memalloc(sizeof(t_sdl))))
		exit(23);
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER | SDL_INIT_AUDIO) < 0 ||
	(IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG) < 0))
		exit(2);
	init_music(m);
	sdl->state = SDL_GetKeyboardState(NULL);
	m->sdl = sdl;
	return (m);
}
