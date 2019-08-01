#include "wolf3d.h"

void	sdl_put_pixel(t_sdl *sdl, int x, int y, int color)
{
	if ((x >= 0 && x < WIN_WIDTH) && (y >= 0 && y < WIN_HEIGHT))
		sdl->data[x + y * WIN_WIDTH] = color;
}

void	print_image(t_sdl *sdl)
{
	int x;
	int y;

	y = -1;
	while (++y < sdl->img.height)
	{
		x = -1;
		while (++x < sdl->img.width)
			sdl->data[x + y * WIN_WIDTH] = *((int*)sdl->img.data + (x + y * sdl->img.width));
	}
}

void	main_loop(t_sdl *sdl, t_wolf *wlf)
{
	int			running;

	while (666)
	{
		SDL_LockMutex(sdl->mutex);
		player_raycast(wlf, sdl);
//		print_image(sdl);
		draw_interface(sdl, wlf);
		SDL_UpdateTexture(sdl->texture, NULL, (void *)sdl->data, WIN_WIDTH * sizeof(int));
		SDL_UnlockMutex(sdl->mutex);
		SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, NULL);
		SDL_RenderPresent(sdl->renderer);
		if (sdl->params & QUIT)
			break;
		if (SDL_PollEvent(&sdl->event))
		{
			if ((SDL_QUIT == sdl->event.type) ||
				(SDL_KEYDOWN == sdl->event.type &&
				 SDL_SCANCODE_ESCAPE == sdl->event.key.keysym.scancode))
				break;
		}
	}
	SDL_RenderClear(sdl->renderer);
	SDL_DestroyTexture(sdl->texture);
	SDL_DestroyWindow(sdl->win);
	SDL_Quit();
}
