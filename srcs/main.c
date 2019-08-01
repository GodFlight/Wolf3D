#define STB_IMAGE_IMPLEMENTATION
#include "wolf3d.h"

int		main(void)
{
	t_wolf	*wlf;
	t_sdl	*sdl;
	SDL_Thread	*thread;

	sdl = sdl_init();
	wlf = wolf_init(sdl);
	map_read(wlf);
	thread = SDL_CreateThread(physics, "physics", (void *)wlf);
	SDL_DetachThread(thread);
	main_loop(sdl, wlf);
	return (0);
}