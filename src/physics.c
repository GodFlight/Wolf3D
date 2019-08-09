
#include "raycast.h"
#include "debug_log.h"

#ifndef DEBUG

static void	move_player(t_rc_main *wlf, t_sdl *sdl)
{
	float	normal_speed;
	float	cash_sin;
	float	cash_cos;
	float	abs_viev;

	if (wlf->player.view_dir < 0)
		abs_viev = (float)((fmod(wlf->player.view_dir, CIRCLE_ANGLE)) + (CIRCLE_ANGLE));
	else
		abs_viev = (float)fmod(wlf->player.view_dir, CIRCLE_ANGLE);
	normal_speed = 0.01f * PLAYER_SPEED;
	cash_sin = (float)(sin((double)abs_viev));
	cash_cos = (float)(cos((double)abs_viev));
	if (sdl->state[SDL_SCANCODE_W])
	{
		SDL_LockMutex(sdl->mutex);
		wlf->player.y += (normal_speed * cash_sin);
		wlf->player.x += (normal_speed * cash_cos);
		SDL_UnlockMutex(sdl->mutex);
	}
	if (sdl->state[SDL_SCANCODE_S])
	{
		SDL_LockMutex(sdl->mutex);
		wlf->player.y -= (normal_speed * cash_sin);
		wlf->player.x -= (normal_speed * cash_cos);;
		SDL_UnlockMutex(sdl->mutex);
	}
	if (sdl->state[SDL_SCANCODE_A])
	{
		SDL_LockMutex(sdl->mutex);
		wlf->player.x += ((normal_speed - 0.06f) * cash_sin);
		wlf->player.y -= ((normal_speed - 0.06f) * cash_cos);
		SDL_UnlockMutex(sdl->mutex);
	}
	if (sdl->state[SDL_SCANCODE_D])
	{
		SDL_LockMutex(sdl->mutex);
		wlf->player.x -= ((normal_speed - 0.06f) * cash_sin);
		wlf->player.y += ((normal_speed - 0.06f) * cash_cos);
		SDL_UnlockMutex(sdl->mutex);
	}
	if (sdl->state[SDL_SCANCODE_ESCAPE])
		wlf->sdl->params |= WOLF_QUIT;
}

static void	rotation_player(t_rc_main *wlf, t_sdl *sdl)
{
	if (sdl->state[SDL_SCANCODE_RIGHT])
	{
		SDL_LockMutex(sdl->mutex);
		wlf->player.view_dir += ROTATION_SPEED;
		SDL_UnlockMutex(sdl->mutex);
	}
	if (sdl->state[SDL_SCANCODE_LEFT])
	{
		SDL_LockMutex(sdl->mutex);
		wlf->player.view_dir -= ROTATION_SPEED;
		SDL_UnlockMutex(sdl->mutex);
	}
}

#else
static void	move_player(t_rc_main *wlf, t_sdl *sdl)
{
	float normal_speed;

	normal_speed = 0.01f * PLAYER_SPEED;
	if (sdl->state[SDL_SCANCODE_W])
	{
		SDL_LockMutex(sdl->mutex);
		wlf->player.y += (normal_speed * sin(wlf->player.view_dir));
		wlf->player.x += (normal_speed * cos(wlf->player.view_dir));
		SDL_Log("%sVertical movement: %s%f\n", KMAG, KCYN, wlf->player.y);
		SDL_UnlockMutex(sdl->mutex);
	}
	if (sdl->state[SDL_SCANCODE_S])
	{
		SDL_LockMutex(sdl->mutex);
		wlf->player.y -= (normal_speed * sin(wlf->player.view_dir));
		wlf->player.x -= (normal_speed * cos(wlf->player.view_dir));;
		SDL_Log("%sVertical movement: %s%f\n", KMAG, KCYN,wlf->player.y);
		SDL_UnlockMutex(sdl->mutex);
	}
	if (sdl->state[SDL_SCANCODE_A])
	{
		SDL_LockMutex(sdl->mutex);
		wlf->player.x -= ((normal_speed - 0.1) * sin(wlf->player.view_dir));
		wlf->player.y -= ((normal_speed - 0.1) * cos(wlf->player.view_dir));
		SDL_Log("%sVertical movement: %s%f\n", KMAG, KCYN,wlf->player.y);
		SDL_UnlockMutex(sdl->mutex);
	}
	if (sdl->state[SDL_SCANCODE_D])
	{
		SDL_LockMutex(sdl->mutex);
		wlf->player.x += ((normal_speed - 0.1) * sin(wlf->player.view_dir));
		wlf->player.y += ((normal_speed - 0.1) * cos(wlf->player.view_dir));
		SDL_Log("%sVertical movement: %s%f\n", KMAG, KCYN,wlf->player.y);
		SDL_UnlockMutex(sdl->mutex);
	}
	if (sdl->state[SDL_SCANCODE_ESCAPE])
		wlf->sdl->params |= QUIT;
}

static void	rotation_player(t_rc_main *wlf, t_sdl *sdl)
{
	if (sdl->state[SDL_SCANCODE_RIGHT])
	{
		SDL_LockMutex(sdl->mutex);
		wlf->player.view_dir += 0.05f;
		SDL_Log("%sTurn right: %s%f\n", KNRM, KCYN,wlf->player.view_dir);
		SDL_UnlockMutex(sdl->mutex);
	}
	if (sdl->state[SDL_SCANCODE_LEFT])
	{
		SDL_LockMutex(sdl->mutex);
		wlf->player.view_dir -= 0.05f;
		SDL_Log("%sTurn left: %s%f\n", KNRM, KCYN,wlf->player.view_dir);
		SDL_UnlockMutex(sdl->mutex);
	}
}
#endif

int	physics(void *wolf)
{
	t_rc_main	*wlf;
	t_sdl		*sdl;

	wlf = (t_rc_main *)wolf;
	sdl = wlf->sdl;
	while (!(sdl->params & WOLF_QUIT))
	{
		if (sdl->state[SDL_SCANCODE_W] || sdl->state[SDL_SCANCODE_S]
		|| sdl->state[SDL_SCANCODE_A] || sdl->state[SDL_SCANCODE_D])
			move_player(wlf, sdl);
		rotation_player(wlf, sdl);
		SDL_Delay(15);
	}
	return (1);
}
