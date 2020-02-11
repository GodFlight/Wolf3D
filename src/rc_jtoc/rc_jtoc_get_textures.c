/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_jtoc_get_textures.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbecker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/18 23:58:54 by sbecker           #+#    #+#             */
/*   Updated: 2019/08/22 00:42:29 by sbecker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycast.h"

static int		**texture_load(int y, int x, unsigned char *img_data,
				t_textures *textures)
{
	int y_tx;
	int x_tx;
	int x_d;
	int y_d;
	int **arr;

	y_d = 0;
	y_tx = (y >= 64 ? y - 65 : y);
	if (!(arr = (int **)ft_memalloc(sizeof(int *) * 64)))
		exit(39);
	while (++y_tx < y)
	{
		if (!(arr[y_d] = (int *)ft_memalloc(sizeof(int) * 64)))
			exit(36);
		x_d = 0;
		x_tx = x - 65;
		while (++x_tx < x)
		{
			arr[y_d][x_d] = *((int*)img_data + (x_tx + y_tx * textures->w));
			x_d++;
		}
		y_d++;
	}
	return (arr);
}

static	t_list	*get_textures(t_conf_json *conf, t_textures *textures,
				unsigned char *img_data, int y)
{
	t_list		*tmp;
	int			**arr;
	int			x;

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
	return (tmp);
}

static int		get_textures_from_texture_pack(t_conf_json *conf,
				char *path, t_textures *textures)
{
	int				y;
	unsigned char	*img_data;
	t_list			*tmp;

	if (!(img_data = stbi_load(path, &textures->w, &textures->h,
	&textures->bpp, 4)))
		return (FUNCTION_FAILURE);
	y = 0;
	while (++y < (textures->h / 64 + 1))
		tmp = get_textures(conf, textures, img_data, y);
	free(img_data);
	conf->textures = tmp;
	return (FUNCTION_SUCCESS);
}

int				rc_jtoc_get_textures(t_conf_json *conf, t_jnode *node)
{
	t_jnode		*tmp;
	t_textures	*textures;
	char		*path;

	while (node)
	{
		textures = (t_textures *)ft_memalloc(sizeof(t_textures));
		if (node->type != object)
			return (rc_jtoc_sdl_log_error("TEXTURE TYPE ERROR", -1));
		if (!(tmp = jtoc_node_get_by_path(node, "path")) || tmp->type != string)
			return (rc_jtoc_sdl_log_error("TEXTURE PATH ERROR", -1));
		path = jtoc_get_string(tmp);
		get_textures_from_texture_pack(conf, path, textures);
		node = node->right;
		free(textures);
	}
	return (FUNCTION_SUCCESS);
}
