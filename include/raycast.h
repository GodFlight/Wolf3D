

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
# include "libjtoc.h"
# include "rc_jtoc.h"


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


typedef struct	s_flr
{
	int		map_x;
	int		map_y;
	int 	step_x;
	int 	step_y;
	int 	side;
	int		draw_start;
	float	side_dist_x;
	float	side_dist_y;
	float	wall_dist;
	float 	hit_x;
	float	floor_wall_x;
	float	floor_wall_y;
	float	floor_x;
	float	floor_y;
}				t_flr;

typedef struct	s_rc_player
{
	float		x;
	float		y;
	float		fdir_x;
	float		fdir_y;
	float		rdir_x;
	float		rdir_y;
	float		plane_x;
	float		plane_y;
	float		camera_x;
	float 		delta_dist_x;
	float		delta_dist_y;
	float		intensity;
}				t_rc_player;

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

typedef struct	s_wall
{
	int			id;
	int			type;
	int         state;
	int			**texture1;
	int			**texture2;
	int			**texture3;
	int			**texture4;
	int			**texture5;
	int			**texture6;
	int			**texture7;
	int			**texture8;
}				t_wall;


typedef struct	s_object
{
	float		x;
	float		y;
	int			id;
	int			**texture;
}				t_object;

typedef struct	s_ray_cast_main
{
	t_rc_player		player;
	t_flr			flr;
	t_wall			*walls;
	t_object		*objects;
	int				objects_num;
	int				**map;
	int				**phys_map;
	int				map_w;
	int				map_h;
	t_sdl			*sdl;
}				t_rc_main;

int		rc_jtoc_is_num(enum e_type type);
int		rc_jtoc_fill_texture_by_index(int ***texture, t_conf_json *conf, t_jnode *n, int id);
int		rc_jtoc_sdl_log_error(const char *p, const int id);
int		rc_jtoc_main_from_json(t_rc_main *m, const char *path);
int		rc_jtoc_win_from_json(t_rc_main *m, t_jnode *n_w);
int		rc_jtoc_get_map(t_rc_main *m, char *path);
int		rc_jtoc_get_textures(t_conf_json *conf, t_jnode *node);
int		rc_jtoc_get_texture_state(int *state, t_jnode *n, int obj_id);
int		rc_jtoc_get_walls(t_rc_main *m, t_conf_json *conf, t_jnode *n);
int		rc_jtoc_get_default_walls(t_wall *walls, t_conf_json *conf, t_jnode *n);
int		rc_jtoc_processing_map(t_rc_main *m);

void	sdl_put_pixel(t_sdl *sdl, int x, int y, int color);
void 	raycast_and_draw(t_rc_main *m);
void	draw_objects(t_rc_main *m);
void	main_loop(t_rc_main *m);
int		physics(void *m);
int		step_y_calculate(t_rc_main *m, float ray_dir_y);
int		step_x_calculate(t_rc_main *m, float ray_dir_x);
void	wall_dist_and_hit_x_calculate(t_rc_main *m, float ray_dir_x,
										  float ray_dir_y);
void	find_dist_y(t_rc_main *m, float ray_dir_x, float ray_dir_y);
void	flr_or_clng_offset_calculate(t_rc_main *m, float ray_dir_x,
										 float ray_dir_y);
t_rc_main	*rc_main_init();
int		rgb_to_hex(char r, char g, char b, char a);
void	draw_interface(t_rc_main *m);
int 		rgb_mod(int color, float mod);
int		clmp(int a, int min, int max);

#endif
