#include "raycast.h"

void	sdl_put_pixel(t_sdl *sdl, int x, int y, int color)
{
	if ((x >= 0 && x < sdl->win_w) && (y >= 0 && y < sdl->win_w))
		sdl->data[x + y * sdl->win_w] = color;
}

void	main_loop(t_rc_main *m)
{
	while (666)
	{
		SDL_LockMutex(m->sdl->mutex);
		player_raycast(m);
        SDL_SetRenderTarget(m->sdl->renderer, m->sdl->texture);
        SDL_RenderClear(m->sdl->renderer);
		draw_interface(m);
		SDL_UpdateTexture(m->sdl->texture, NULL, (void *)m->sdl->data, m->sdl->win_w * sizeof(int));
		SDL_UnlockMutex(m->sdl->mutex);
        SDL_SetRenderTarget(m->sdl->renderer, NULL);
		SDL_RenderCopy(m->sdl->renderer, m->sdl->texture, NULL, NULL);
		SDL_RenderPresent(m->sdl->renderer);
		if (SDL_PollEvent(&m->sdl->event))
		{
			if ((m->sdl->event.type == SDL_QUIT) ||
				(m->sdl->event.type == SDL_KEYDOWN &&
				 m->sdl->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE))
			{
				m->sdl->params |= WOLF_QUIT;
				break;
			}
		}
	}
	SDL_RenderClear(m->sdl->renderer);
	SDL_DestroyTexture(m->sdl->texture);
	SDL_DestroyWindow(m->sdl->win);
	SDL_Quit();
}
