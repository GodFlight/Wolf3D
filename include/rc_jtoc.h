//
// Created by dolov on 13.08.2019.
//

#ifndef RC_JTOC_H
#define RC_JTOC_H

typedef struct	s_textures
{
	int				num;
	int				w;
	int				h;
	int				bpp;
}				t_textures;

typedef struct	s_conf_json
{
	t_list		*textures;
	int			index;
}				t_conf_json;

#endif
