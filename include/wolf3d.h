/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 15:16:27 by rkeli             #+#    #+#             */
/*   Updated: 2019/07/23 18:04:50 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H

# include "libft.h"
# include <SDL.h>
# include <SDL_image.h>
# include <math.h>
#include <fcntl.h>
//# define WIN_HEIGHT 1315
# define WIN_HEIGHT 1080
# define WIN_WIDTH 1920
//# define WIN_WIDTH 2560
# define MAP_PATH "/Users/rkeli/Desktop/Wolf3D/maps/map_01"
# define MAP_PATH_TWO "/Users/rkeli/Desktop/Wolf3D/maps/map_02"
# define BLACK 0x00000000
# define WHITE 0xFFFFFFFF
# define GREEN 0x00FF0000
# define GRAY 0xC6E3E400
# define BLUE 0x0000FF00
# define RED 0xFF000000
# define PLAYER_SPEED 10.0f
# define MAP_SCALE 30
//# define FOV M_PI / 3
# define TRUE 1
# define FALSE 0

typedef struct	s_player_ray
{
	float 		x;
	float 		y;
	float 		colum;
	float		i;
	float 		angle;
	float 		distance;
}				t_player_ray;

typedef struct	s_wlf_player
{
	float 		x;
	float 		y;
	float 		view_dirx;
	float 		view_diry;
	float 		view_dir;
	short		running;
}				t_wlf_player;

typedef struct	s_sdl
{
	SDL_Window		*win;
	SDL_Renderer	*renderer;
	SDL_Surface		*screen;
	SDL_Surface		*image;
	SDL_Event		event;
	SDL_Texture		*texture;
	SDL_Rect		*rect;
	int 			*data;
	int 			x;
	int 			y;
}				t_sdl;

typedef struct	s_wolf
{
	int				**map;
	int				len_xmap;
	int				len_ymap;
	float 			x;
	float 			y;
	t_wlf_player	player;
	t_player_ray	ray;
}				t_wolf;

void	map_read(t_wolf *wlf);
void	sdl_put_pixel(t_sdl *sdl, int x, int y, int color);
void	drow_map(t_sdl *sdl, t_wolf *wlf);
void	player_movenet(t_wolf *wlf, t_sdl *sdl);
void 	player_raycast(t_wolf *wlf, t_sdl *sdl);
void	drow_colum(t_wolf *wlf, t_sdl *sdl, float colum, int i);
//void	drow_colum(t_wolf *wlf, t_sdl *sdl);
//void	three_d_render();

#endif
