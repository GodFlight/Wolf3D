//
// Created by Slaughterfish Becker on 2019-08-06.
//

#include "raycast.h"

int	rc_jtoc_win_from_json(t_rc_main *m, t_jnode *n_w)
{
	t_jnode	*tmp;
	t_sdl	*sdl;

	sdl = m->sdl;
	if (!(tmp = jtoc_node_get_by_path(n_w, "title")) || tmp->type != string)
		return (rc_jtoc_sdl_log_error("MISSING WIN TITLE", -1));
	sdl->win_title = ft_strdup(jtoc_get_string(tmp));
	if (!(tmp = jtoc_node_get_by_path(n_w, "size.x")) || !(rc_jtoc_is_num(tmp->type)))
		return (rc_jtoc_sdl_log_error("WINDOW SIZE.X ERROR", -1));
	sdl->win_w = jtoc_get_int(tmp);
	if (!(tmp = jtoc_node_get_by_path(n_w, "size.y")) || !(rc_jtoc_is_num(tmp->type)))
		return (rc_jtoc_sdl_log_error("WINDOW SIZE.Y ERROR", -1));
	sdl->win_h = jtoc_get_int(tmp);
	if (!(sdl->data = (int *)ft_memalloc(sizeof(int) * (sdl->win_w * sdl->win_h))))
		return (rc_jtoc_sdl_log_error("MALLOC ERROR", -1));
	if (!(sdl->win = SDL_CreateWindow("Wolf3D", SDL_WINDOWPOS_CENTERED,
			SDL_WINDOWPOS_CENTERED, sdl->win_w, sdl->win_h, SDL_WINDOW_RESIZABLE)))
		return (rc_jtoc_sdl_log_error("CREATE WINDOW ERROR", -1));
	if (!(sdl->renderer = SDL_CreateRenderer(sdl->win, -1, 0)))
		return (rc_jtoc_sdl_log_error("CREATE WINDOW RENDERER ERROR", -1));
//	if (!(sdl->texture = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_ARGB8888,
//			SDL_TEXTUREACCESS_STATIC, sdl->win_w, sdl->win_h)))
	if (!(sdl->texture = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_RGBA32,
	SDL_TEXTUREACCESS_STATIC, sdl->win_w, sdl->win_h)))
//		if (!(sdl->texture = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_BGR888,
//											   SDL_TEXTUREACCESS_STATIC, sdl->win_w, sdl->win_h)))
		return (rc_jtoc_sdl_log_error("CREATE WINDOW TEXTURE ERROR", -1));
	m->z_buffer = (float *)ft_memalloc(sizeof(float) * sdl->win_w);
	return (FUNCTION_SUCCESS);
}
