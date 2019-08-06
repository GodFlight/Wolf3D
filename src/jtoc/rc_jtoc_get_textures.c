//
// Created by Slaughterfish Becker on 2019-08-06.
//

#include "raycast.h"

static int	get_textures_from_texture_pack(t_rc_main *wlf, t_conf_json *conf, char *path)
{
	int y;
	int x;
	int *img_data;

	img_data = stbi_load(path, &wlf->textures.w,
						 &wlf->textures.h, &wlf->textures.bpp, 4);
	y = -1;
	while (++y < wlf->textures.h)
	{
		//TODO create new node in list conf->textures, content this node will link on texture's t int array
	}
}

int	rc_jtoc_get_textures(t_rc_main *wlf, t_conf_json *conf, t_jnode *n_texture)
{
	t_jnode *tmp;
	char	*path;

	conf->textures = NULL;
	while (n_texture)
	{
		if (n_texture->type != object)
			return (rc_jtoc_sdl_log_error("TEXTURE TYPE ERROR", -1));
		if (!(tmp = jtoc_node_get_by_path(tmp, "path")) || tmp->type != string)
			return (rc_jtoc_sdl_log_error("TEXTURE PATH ERROR", -1));
		path = jtoc_get_string(tmp);
		if (!(tmp = jtoc_node_get_by_path(tmp, "type")) || tmp->type != string)
			return (rc_jtoc_sdl_log_error("TEXTURE TYPE ERROR", -1));
		if (!(ft_strcmp(jtoc_get_string(tmp), "texture_pack")))
			get_textures_from_texture_pack(wlf, conf, path);
		n_texture = n_texture->right;
	}
}
