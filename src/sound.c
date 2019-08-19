//
// Created by Racquel Keli on 2019-08-16.
//

#include <raycast.h>

int		init_music(t_rc_main *m)
{
	Mix_Music *mus;
	Mix_Chunk **sample;
	int result = 0;
	int flags = MIX_INIT_OGG;

	if (flags != (result = Mix_Init(flags)))
	{
		printf("Could not initialize mixer (result: %d).\n", result);
		printf("Mix_Init: %s\n", Mix_GetError());
		exit(1);
	}
	if (!(sample = ft_memalloc(sizeof(Mix_Chunk *) * 19)))
		return (-1);
	Mix_OpenAudio(22050, AUDIO_S16SYS, 4, 640);
	mus = Mix_LoadMUS(MUS_PATH);
	sample[0] = Mix_LoadWAV(WHITE_NOISE);
	sample[1] = Mix_LoadWAV(WHITE_NOISE);
	sample[2] = Mix_LoadWAV(WHITE_NOISE);
	sample[3] = Mix_LoadWAV(WHITE_NOISE);
	sample[4] = Mix_LoadWAV(SCREAM);
	sample[18] = Mix_LoadWAV(ELECTRIC_SAW);
	Mix_VolumeMusic(10);
	Mix_PlayMusic(mus, -1);
	Mix_AllocateChannels(18);
	m->sound.samples = sample;
	return (1);
}

void 	sounds_control(t_rc_main *m, char flg)
{
	if (flg == 18 && !Mix_Playing(flg))
		Mix_PlayChannelTimed(18, m->sound.samples[18], 0, 2000);
	else if (!Mix_Playing(flg) && flg != 18)
		Mix_PlayChannelTimed(flg, m->sound.samples[flg - 1], 0, 500);
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