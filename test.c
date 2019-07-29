#include "wolf3d.h"

//int main(void)
//{
//    int running = 1;
//    char *sdl;
//
//    SDL_Event event;
//
//    if ((SDL_Init(SDL_INIT_EVERYTHING)))
//    	exit(2);
//    SDL_Window *win = SDL_CreateWindow("Hello World!", 100, 100, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);
//    if (NULL == win)
//        exit (1);
//
//    while (running)
//        while(SDL_PollEvent(&event))
//            if((SDL_QUIT == event.type) || (SDL_KEYDOWN == event.type && SDL_SCANCODE_ESCAPE == event.key.keysym.scancode))
//                running = 0;
//
//    SDL_DestroyWindow(win);
//    SDL_Quit();
//    return (0);
//}