#include "raycast.h"

int		main(void)
{
	t_rc_main	*rc_main;
	t_sdl	*sdl;
	SDL_Thread	*thread;

	rc_main = rc_main_init(sdl);
	rc_jtoc_main_from_json(rc_main, "../json/config.json");
	sdl->mutex = SDL_CreateMutex();
	thread = SDL_CreateThread(physics, "physics", (void *)rc_main);
	SDL_DetachThread(thread);
	main_loop(rc_main);
	return (0);
}