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
# include "define.h"
# include <SDL.h>
# include "stb_image.h"
# include <SDL_image.h>
# include <math.h>
# include <fcntl.h>


typedef struct	s_player_ray
{
	float 		hitx;
	float 		hity;
	float 		x;
	float 		y;
	float		i;
	float		eps;
	float 		colum;
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

typedef struct	s_img
{
	unsigned char	*data;
	int 			width;
	int 			height;
	int 			bpp;
}				t_img;

typedef struct	s_sdl
{
	SDL_Window		*win;
	SDL_Renderer	*renderer;
	SDL_Surface		*screen;
	SDL_Surface		**texture_pack;
	t_img			img;
	SDL_Event		event;
	SDL_Texture		*texture;
	SDL_Texture		*texture_p;
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
	int 			t_id;
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
void	drow_colum(t_wolf *wlf, t_sdl *sdl, float h_colum, int i);
t_wolf	*wolf_init(void);
t_sdl	*sdl_init(void);
void	main_loop(t_sdl *sdl, t_wolf *wlf);
int		rgb_to_hex(int r, int g, int b);

#endif
