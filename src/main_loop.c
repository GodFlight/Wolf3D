//
// Created by dolov on 15.08.2019.
//

#include "raycast.h"

void	main_loop(t_rc_main *m)
{
	m->scream.init_time = 0;
	while (1337)
	{
		if (m->choose_map == MAP_WITH_SCREAMER)
			check_pos(m);
		if (SDL_PollEvent(&m->sdl->event))
		{
			sounds(m->sdl, m->sdl->event);
			if ((m->sdl->event.type == SDL_QUIT) ||
				(m->sdl->event.type == SDL_KEYDOWN &&
				 m->sdl->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
			{
				m->params |= QUIT_PROGRAM;
				break;
			}
		}
	}
	SDL_Quit();
	IMG_Quit();
	Mix_Quit();
	exit(0);
}
