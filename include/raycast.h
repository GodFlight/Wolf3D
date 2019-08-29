

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
# include <SDL.h>
# include <SDL_mixer.h>
# include <SDL_image.h>
# include "libft.h"
# include "define.h"
# include "stb_image.h"
# include <math.h>
# include <fcntl.h>
# include "libjtoc.h"
# include "rc_jtoc.h"

typedef struct		s_flr
{
	int				step_x;
	int				step_y;
	float			side_dist_x;
	float			side_dist_y;
	float			wall_dist;
	float			hit_x;
	float			floor_wall_x;
	float			floor_wall_y;
	float			floor_x;
	float			floor_y;
}					t_flr;

typedef struct		s_wls
{
	int				side;
	int				map_x;
	int				map_y;
}					t_wls;

typedef struct		s_rc_player
{
	float			x;
	float			y;
	float			fdir_x;
	float			fdir_y;
	float			rdir_x;
	float			rdir_y;
	float			plane_x;
	float			plane_y;
	float			camera_x;
	float 			delta_dist_x;
	float			delta_dist_y;
	float			intensity;
	float 			current_dist;
}					t_rc_player;

typedef struct		s_sdl
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
	int				win_h;
	int				win_w;
	char 			*win_title;
}					t_sdl;

typedef struct		s_wall
{
	int				id;
	int				type;
	int				**texture1;
	int				**texture2;
	int				**texture3;
	int				**texture4;
}					t_wall;


typedef struct		s_object
{
	float			x;
	float			y;
	float 			*intensity;
	int				id;
	int				**texture;
}					t_object;

typedef struct		s_scream
{
	int 			*spawn;
	t_object		*obj;
	char 			flg;
	Uint32			init_time;
	float 			x;
	float 			y;
}					t_scream;

typedef struct		s_sound
{
	Mix_Chunk		**samples;
}					t_sound;

typedef struct		s_ray_cast_main
{
	t_rc_player		player;
	t_flr			flr;
	t_wls			wls;
	t_wall			*walls;
	t_object		*objects;
	t_sdl			*sdl;
	t_sound			sound;
	t_scream		scream;
	int				objects_num;
	int				**map;
	int				**phys_map;
	int				map_w;
	int				map_h;
	int				params;
	float			*z_buffer;
	char 			choose_map;
}					t_rc_main;

int					rc_jtoc_is_num(enum e_type type);
int					rc_jtoc_fill_texture_by_index(int ***texture, t_conf_json *conf, t_jnode *n, int id);
int					rc_jtoc_sdl_log_error(const char *p, const int id);
int					rc_jtoc_main_from_json(t_rc_main *m, const char *path, t_conf_json *conf);
int					rc_jtoc_win_from_json(t_rc_main *m, t_jnode *n_w);
int					rc_jtoc_get_map(t_rc_main *m, char *path);
int					rc_jtoc_get_textures(t_conf_json *conf, t_jnode *node);
int					rc_jtoc_get_walls(t_rc_main *m, t_conf_json *conf, t_jnode *n);
int					rc_jtoc_get_default_walls(t_wall *walls, t_conf_json *conf, t_jnode *n);
int					rc_jtoc_processing_map(t_rc_main *m);
int					rc_jtoc_get_objects(t_rc_main *m, t_conf_json *conf, t_jnode *n);
int					rc_jtoc_get_player(t_rc_main *m, t_jnode *n);
void				main_loop(t_rc_main *m);
int					physic_loop(void *m_v);
int					draw_loop(void *m_v);

void				sdl_put_pixel(t_sdl *sdl, int x, int y, int color);
void 				raycast_and_draw(t_rc_main *m);
void				draw_objects(t_rc_main *m);
int					step_y_calculate(t_rc_main *m, float ray_dir_y);
int					step_x_calculate(t_rc_main *m, float ray_dir_x);
void				wall_dist_and_hit_x_calculate(t_rc_main *m, float ray_dir_x,
										  float ray_dir_y);
void				find_dist_y(t_rc_main *m, float ray_dir_x, float ray_dir_y);
void				flr_or_clng_offset_calculate(t_rc_main *m, float ray_dir_x,
										 float ray_dir_y);
t_rc_main			*rc_main_init();
int					rgb_mod(float mod, int rgb);
float				clmp(float a, float min, float max);
int					init_music(t_rc_main *m);
void				sounds(t_sdl *sdl, SDL_Event event);
void 				sounds_control(t_rc_main *m, char flg);

void 				screaming_control(t_rc_main *m, int obj_id, char flg);
void 				move_scrm_control(t_rc_main *m, int obj_id);
void 				tp_obj(t_rc_main *m, t_object *obj, int obj_id, int tick);
void				choose_obj_pos(t_rc_main *m, float pos_x, float pos_y, int obj_id, char flg);
void				check_pos(t_rc_main *m);

#endif
