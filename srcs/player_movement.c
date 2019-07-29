
#include "wolf3d.h"
#include "debug_log.h"

void	player_movenet(t_wolf *wlf, t_sdl *sdl)
{
	if ((wlf->player.y > 0.01 && wlf->player.y < wlf->len_ymap) && (wlf->player.x > 0.01 && wlf->player.x < wlf->len_xmap))
	{
		if (SDL_KEYDOWN == sdl->event.type && SDL_SCANCODE_W == sdl->event.key.keysym.scancode)
		{
			wlf->player.y += ((0.01f * PLAYER_SPEED) * sin(wlf->player.view_dir));
			wlf->player.x += ((0.01f * PLAYER_SPEED) * cos(wlf->player.view_dir));
			ft_bzero(sdl->data, sizeof(int) * (WIN_WIDTH * WIN_HEIGHT));
            SDL_Log("%sVertical movement: %s%f\n", KMAG, wlf->player.y, KCYN);
		}
		else if (SDL_KEYDOWN == sdl->event.type && SDL_SCANCODE_S == sdl->event.key.keysym.scancode)
		{
			wlf->player.y -= ((0.01f * PLAYER_SPEED) * sin(wlf->player.view_dir));
			wlf->player.x -= ((0.01f * PLAYER_SPEED) * cos(wlf->player.view_dir));;
			ft_bzero(sdl->data, sizeof(int) * (WIN_WIDTH * WIN_HEIGHT));
			SDL_Log("%sVertical movement: %s%f\n", KMAG, wlf->player.y, KCYN);
		}
		else if (SDL_KEYDOWN == sdl->event.type && SDL_SCANCODE_D == sdl->event.key.keysym.scancode)
		{
			wlf->player.x += (0.01f * PLAYER_SPEED);
			ft_bzero(sdl->data, sizeof(int) * (WIN_WIDTH * WIN_HEIGHT));
            SDL_Log("%sHorizontal movement: %s%f\n", KRED, wlf->player.x, KCYN);
		}
		else if (SDL_KEYDOWN == sdl->event.type && SDL_SCANCODE_A == sdl->event.key.keysym.scancode)
		{
			wlf->player.x -= (0.01f * PLAYER_SPEED);
			ft_bzero(sdl->data, sizeof(int) * (WIN_WIDTH * WIN_HEIGHT));
			SDL_Log("%sHorizontal movement: %s%f\n", KRED, wlf->player.x, KCYN);
		}
		else if (SDL_KEYDOWN == sdl->event.type && SDL_SCANCODE_E == sdl->event.key.keysym.scancode)
		{
			wlf->player.view_dir += 0.05f;
			ft_bzero(sdl->data, sizeof(int) * (WIN_WIDTH * WIN_HEIGHT));
			SDL_Log("%sTurn right: %s%f\n", KNRM, wlf->player.view_dir, KCYN);
		}
		else if (SDL_KEYDOWN == sdl->event.type && SDL_SCANCODE_Q == sdl->event.key.keysym.scancode)
		{
			wlf->player.view_dir -= 0.05f;
			ft_bzero(sdl->data, sizeof(int) * (WIN_WIDTH * WIN_HEIGHT));
			SDL_Log("%sTurn left: %s%f\n", KNRM, wlf->player.view_dir, KCYN);
		}
	}
}