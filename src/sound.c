//
// Created by Racquel Keli on 2019-08-16.
//

#include <raycast.h>

int		init_music(t_rc_main *m)
{
	Mix_Music *mus;
	int result = 0;
	int flags = MIX_INIT_OGG;

	if (!m)
		mus = NULL;
	if (flags != (result = Mix_Init(flags)))
	{
		printf("Could not initialize mixer (result: %d).\n", result);
		printf("Mix_Init: %s\n", Mix_GetError());
		exit(1);
	}
	Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
	mus = Mix_LoadMUS(MUS_PATH);
	Mix_PlayMusic(mus, -1);
	return (1);
}

void	sounds(t_sdl *sdl, SDL_Event event)
{
	SDL_Scancode key;

	key = event.key.keysym.scancode;
	if (key == SDL_SCANCODE_SPACE && sdl->event.type == SDL_KEYDOWN)
	{
		if (Mix_PausedMusic() == -1)
			Mix_ResumeMusic();
		else
			Mix_PauseMusic();
	}
}