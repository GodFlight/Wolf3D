//
// Created by Slaughterfish Becker on 2019-08-06.
//

#include "raycast.h"

static int **
texture_load(int y, int x, unsigned char *img_data, t_textures *textures)
{
	int y_tx;
	int x_tx;
	int x_d;
	int y_d;
	int **arr;

	y_d = 0;
	y_tx = (y >= 64 ? y - 64 : y);
	if (!(arr = (int **)ft_memalloc(sizeof(int *) * textures->w)))
		exit(39);
	while (y_tx <= y)
	{
		if (!(arr[y_d] = (int *)ft_memalloc(sizeof(int) * textures->h)))
			exit(36);
		x_d = 0;
		x_tx = x - 64;
		while (x_tx < x)
		{
			arr[y_d][x_d] = *((int*)img_data + (x_tx + y_tx * textures->w));
			x_d++;
			x_tx++;
		}
		y_d++;
		y_tx++;
	}
	return (arr);
}

static int get_textures_from_texture_pack(t_conf_json *conf, char *path)
{
	int				y;
	int				x;
	unsigned char	*img_data = 0;
	int				**arr;
	t_list			*tmp;
	t_textures		*textures;

	textures = (t_textures *)ft_memalloc(sizeof(t_textures));
	img_data = stbi_load(path, &textures->w,
                         &textures->h, &textures->bpp, 4);
	y = 0;
	while (++y < (textures->h / 64 + 1))
	{
		x = 0;
		while (++x < (textures->w / 64) + 1)
		{
			tmp = ft_lstnew(NULL, 0);
			x = (x == textures->w ? 0 : x * 64);
			arr = texture_load(y * 64, x, img_data, textures);
			tmp->content = (void *)arr;
			tmp->content_size = ++(conf->index);
			ft_lstadd(&conf->textures, tmp);
			x = x / 64;
		}
	}
	conf->textures = tmp;
	return (FUNCTION_SUCCESS);
}

int rc_jtoc_get_textures(t_conf_json *conf, t_jnode *node)
{
	t_jnode *tmp;
	char	*path;

	while (node)
	{
		if (node->type != object)
			return (rc_jtoc_sdl_log_error("TEXTURE TYPE ERROR", -1));
		if (!(tmp = jtoc_node_get_by_path(node, "path")) || tmp->type != string)
			return (rc_jtoc_sdl_log_error("TEXTURE PATH ERROR", -1));
		path = jtoc_get_string(tmp);
		get_textures_from_texture_pack(conf, path);
		node = node->right;
	}
	return (FUNCTION_SUCCESS);
}
