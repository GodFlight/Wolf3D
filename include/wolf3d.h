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
# define STB_IMAGE_IMPLEMENTATION

# include "libft.h"
# include "define.h"
# include <SDL.h>
# include "stb_image.h"
# include <SDL_image.h>
# include <math.h>
# include <fcntl.h>
# include "libjtoc.h"


# define KNRM				"\x1B[0m"
# define KRED				"\x1B[31m"
# define KGRN				"\x1B[32m"
# define KYEL				"\x1B[33m"
# define KBLU				"\x1B[34m"
# define KMAG				"\x1B[35m"
# define KCYN				"\x1B[36m"
# define KWHT				"\x1B[37m"

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
	float 		view_dir;
}				t_wlf_player;

typedef struct	s_img
{
	unsigned char	*data;
	int 			width;
	int 			height;
	int 			bpp;
	int             **texture;
}				t_img;

typedef struct	s_sdl
{
	SDL_Window		*win;
	SDL_Renderer	*renderer;
	SDL_Surface		**texture_pack;
	t_img			img;
	SDL_Event		event;
	SDL_Texture		*texture;
	SDL_Rect		*rect;
	int 			*data;
	int 			x;
	int 			y;
	const Uint8		*state;
	SDL_mutex		*mutex;
	int				params;
}				t_sdl;

typedef struct	s_interface
{
	float	x;
	float 	y;
	float 	angle;
	float 	distance;
}				t_interface;

typedef struct	s_object
{
	int	type;
	int	*texture;
}				t_obj;

typedef struct	s_wolf
{
	int				**map;
	int				w_map;
	int				h_map;
	float 			x;
	float 			y;
	t_obj			*objs;
	t_wlf_player	player;
	t_player_ray	ray;
	t_sdl			*sdl;
}				t_wolf;

void	sdl_put_pixel(t_sdl *sdl, int x, int y, int color);
void 	player_raycast(t_wolf *wlf, t_sdl *sdl);
void	draw_colum(t_wolf *wlf, t_sdl *sdl, float h_colum, int i);
void	draw_ray(t_sdl *sdl, t_wolf *wlf);
void	main_loop(t_sdl *sdl, t_wolf *wlf);
int		physics(void *wlf);

//init
t_wolf	*wolf_init(t_sdl *sdl);
t_sdl	*sdl_init(void);
int	map_read(t_wolf *wlf, int fd);

//utilits
int		rgb_to_hex(int r, int g, int b);

//interface
void	draw_interface(t_sdl *sdl, t_wolf *wlf);
void	draw_map(t_sdl *sdl, t_wolf *wlf);

#endif
