#define STB_IMAGE_IMPLEMENTATION
#include "wolf3d.h"

int		main(void)
{
	t_wolf	*wlf;
	t_sdl	*sdl;

	wlf = wolf_init();
	sdl = sdl_init();
	map_read(wlf);
	main_loop(sdl, wlf);
	return (0);
}