
#include "wolf3d.h"
#include "debug_log.h"

//TODO A/D - going left/right
//TODO arrow - change ray view

static void	player_movenet(t_wolf *wlf, t_sdl *sdl)
{
	float normal_speed;

	normal_speed = 0.01f * PLAYER_SPEED;
	if (sdl->state[SDL_SCANCODE_W])
	{
		wlf->player.y += (normal_speed * sin(wlf->player.view_dir));
		wlf->player.x += (normal_speed * cos(wlf->player.view_dir));
		#ifdef DEBUG
		SDL_Log("%sVertical movement: %s%f\n", KMAG, KCYN, wlf->player.y);
		#endif
	}
	else if (sdl->state[SDL_SCANCODE_S])
	{
		wlf->player.y -= (normal_speed * sin(wlf->player.view_dir));
		wlf->player.x -= (normal_speed * cos(wlf->player.view_dir));;
		#ifdef DEBUG
		SDL_Log("%sVertical movement: %s%f\n", KMAG, KCYN,wlf->player.y);
		#endif
	}
	if (sdl->state[SDL_SCANCODE_RIGHT])
	{
		wlf->player.view_dir += 0.05f;
		#ifdef DEBUG
		SDL_Log("%sTurn right: %s%f\n", KNRM, KCYN,wlf->player.view_dir);
		#endif
	}
	if (sdl->state[SDL_SCANCODE_LEFT])
	{
		wlf->player.view_dir -= 0.05f;
		#ifdef DEBUG
		SDL_Log("%sTurn left: %s%f\n", KNRM, KCYN,wlf->player.view_dir);
		#endif
	}
//	ft_bzero(sdl->data, WIN_HEIGHT * WIN_WIDTH * sizeof(int));
	if (sdl->state[SDL_SCANCODE_ESCAPE])
		wlf->sdl->params |= QUIT;
}

int	physics(void *wolf)
{
	t_wolf *wlf = (t_wolf *)wolf;

	while (666)
	{
		player_movenet(wlf, wlf->sdl);
		SDL_Delay(20);
	}
}
