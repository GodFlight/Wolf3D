//
// Created by Racquel Keli on 2019-08-16.
//

#include <raycast.h>

//# define MUS_PATH "./sound/s1.wav"

int		init_music(t_rc_main *m)
{
//	Mix_Chunk **samples;
	Mix_Music *mus;

	if ((Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 4096) == -1))
		return (-1);
	mus = Mix_LoadMUS(MUS_PATH);
	m->snd->music = mus;
	Mix_PlayMusic(mus, -1);
	Mix_AllocateChannels(4);
	return (1);
}

void	sounds(t_sdl *sdl, SDL_Event event)
{
	SDL_Scancode key;

	(void)sdl;
	key = event.key.keysym.scancode;
	if (key == 48)
	{
		if (Mix_PausedMusic() == 1)
			Mix_ResumeMusic();
		else
			Mix_PauseMusic();
	}
}