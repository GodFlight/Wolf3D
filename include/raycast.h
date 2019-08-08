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

//obj params
# define OBJ_IS_DESTRUCTIBLE	(1 << 0)

typedef struct	s_conf_json
{
	t_list		*textures;
	int			index;
}				t_conf_json;

typedef struct	s_player_ray
{
	float 		hitx;
	float 		hity;
	float 		x;
	float 		y;
	float		i;
	float		eps;
	float 		angle;
	float 		distance;
}				t_player_ray;

typedef struct	s_wlf_player
{
	float 		x;
	float 		y;
	float 		view_dir;
}				t_wlf_player;

typedef struct	s_sdl
{
	SDL_Window		*win;
	SDL_Renderer	*renderer;
	SDL_Event		event;
	SDL_Texture		*texture;
	int 			*data;
	int 			x;
	int 			y;
	const Uint8		*state;
	SDL_mutex		*mutex;
	int				params;
	int				win_h;
	int				win_w;
	char			*win_title;
}				t_sdl;

typedef struct	s_interface
{
	float	x;
	float 	y;
	float 	angle;
	float 	distance;
}				t_interface;

typedef struct	s_wall_texture_state
{
	int			**texture_north;
	int			**texture_south;
	int			**texture_west;
	int			**texture_east;
}				t_wts;

typedef struct	s_wall
{
	t_wts	*state1;
	t_wts	*state2;
	t_wts	*state3;
}				t_wall;

typedef struct	s_object
{
	int			id;
	int			type;
	int			state;
	int			params;
	void		*data;
}				t_object;

typedef struct	s_textures
{
	int				num;
	int				w;
	int				h;
	int				bpp;
}				t_textures;

typedef struct	s_ray_cast_main
{
	t_textures		textures;

	int				**map;
	int				w_map;
	int				h_map;
	float 			x;		//what is it?
	float 			y;		//?
	t_object		*objs;
	t_wlf_player	player;
	t_player_ray	ray;
	t_sdl			*sdl;
}				t_rc_main;

//jtoc
int		rc_jtoc_main_from_json(t_rc_main *m, const char *path);
int		rc_jtoc_win_from_json(t_rc_main *m, t_jnode *n_w);
int		rc_jtoc_sdl_log_error(const char *p, const int id);
int		rc_jtoc_is_num(enum e_type type);
int		rc_jtoc_get_map(t_rc_main *wlf, char *path);
int		rc_jtoc_get_textures(t_rc_main *wlf, t_conf_json *conf, t_jnode *n_texture);
int		rc_jtoc_get_obj(t_rc_main *m, t_jnode *n, t_conf_json *conf);
int		rc_jtoc_get_texture_state(int *state, t_jnode *n, int obj_id);
int		rc_jtoc_get_wall_obj(t_object *obj, t_jnode *n, t_conf_json *conf);

void	sdl_put_pixel(t_sdl *sdl, int x, int y, int color);
void 	player_raycast(t_rc_main *m);
void	main_loop(t_rc_main *m);
int		physics(void *m);

//init
t_rc_main	*rc_main_init();

//utilits
int		rgb_to_hex(int r, int g, int b);


//interface
void	draw_interface(t_rc_main *m);

#endif
