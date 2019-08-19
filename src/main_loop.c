//
// Created by dolov on 15.08.2019.
//

#include "raycast.h"

void	main_loop(t_rc_main *m)
{
	m->scream.init_time = 0;
	while (1337)
	{
		if (m->map_h == 27 && m->map_w == 31)
		{
			if ((int)m->player.x == 17 && (int)m->player.y == 1)
			{
				m->scream.y = 1.5f;
				m->scream.x = 16.7f;
				screaming_control(m, 907, 1);
			}
			if ((int)m->player.x == 6 && (int)m->player.y == 2)
			{
				m->scream.y = 3.5f;
				m->scream.x = 6.5f;
				screaming_control(m, 906, 2);
			}
			else if ((int)m->player.x == 2 && (int)m->player.y == 16)
			{
				m->scream.y = 16.5f;
				m->scream.x = 3.5f;
				screaming_control(m, 904, 3);
			}
			else if ((int)m->player.x == 15 && (int)m->player.y == 25)
			{
				m->scream.y = 24.5f;
				m->scream.x = 15.5f;
				screaming_control(m, 909, 4);
			}
			if ((int)m->player.x == 25 && (int)m->player.y == 21)
			{
				m->scream.y = 11.5f;
				m->scream.x = 25.5f;
				if (m->scream.spawn[18] != 1)
				{
					screaming_control(m, 911, 18);
					sounds_control(m, 18);
				}
				move_scrm_control(m, 911);
			}
		}
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
