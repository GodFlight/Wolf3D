# define STB_IMAGE_IMPLEMENTATION
#include "raycast.h"

#ifdef APPLE___
int		main()
{
	t_conf_json	conf;
    t_rc_main	*m;
    SDL_Thread	*thread;

    m = rc_main_init();
    if (rc_jtoc_main_from_json(m, "./json/config.json", &conf))
    	exit(0);
    m->sdl->mutex = SDL_CreateMutex();
    thread = SDL_CreateThread(draw_loop, "draw_loop", (void *)m);
    SDL_DetachThread(thread);
	thread = SDL_CreateThread(physic_loop, "physic_loop", (void *)m);
	SDL_DetachThread(thread);
    main_loop(m);
    return (0);
}
#else
int		SDL_main(int argc, char *argv[])
{
    t_conf_json	conf;
    t_rc_main	*m;
    SDL_Thread	*thread;

    m = rc_main_init();
    if (rc_jtoc_main_from_json(m, "./json/config.json", &conf))
        exit(0);
    m->sdl->mutex = SDL_CreateMutex();
    thread = SDL_CreateThread(draw_loop, "draw_loop", (void *)m);
    SDL_DetachThread(thread);
    thread = SDL_CreateThread(physic_loop, "physic_loop", (void *)m);
    SDL_DetachThread(thread);
    main_loop(m);
    return (0);
}
#endif
