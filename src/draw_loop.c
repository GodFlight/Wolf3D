#include "raycast.h"

void	sdl_put_pixel(t_sdl *sdl, int x, int y, int color)
{
	if ((x >= 0 && x < sdl->win_w) && (y >= 0 && y < sdl->win_h))
		sdl->data[x + y * sdl->win_w] = color;
}

int	draw_loop(void *m_v)
{
	t_rc_main	*m;

	m = (t_rc_main *)m_v;
	while (!(m->params & QUIT_PROGRAM))
	{
		SDL_LockMutex(m->sdl->mutex);
		raycast_and_draw(m);
		draw_objects(m);
		SDL_SetRenderTarget(m->sdl->renderer, m->sdl->texture);
		SDL_RenderClear(m->sdl->renderer);
		SDL_UpdateTexture(m->sdl->texture, NULL, (void *)m->sdl->data, m->sdl->win_w * sizeof(int));
		SDL_UnlockMutex(m->sdl->mutex);
		SDL_SetRenderTarget(m->sdl->renderer, NULL);
		SDL_RenderCopy(m->sdl->renderer, m->sdl->texture, NULL, NULL);
		SDL_RenderPresent(m->sdl->renderer);
	}
//	SDL_RenderClear(m->sdl->renderer);
//	SDL_DestroyTexture(m->sdl->texture);
//	SDL_DestroyWindow(m->sdl->win);
	return (0);
}
