//
// Created by Slaughterfish Becker on 2019-08-06.
//

#include "raycast.h"

int	rc_jtoc_sdl_log_error(const char *p, const int id)
{
	SDL_Log("%s ----> ERROR <---- %s", KRED, KNRM);
	SDL_Log("INCORRECT: %s%s%s%s%s",
			p,
			id < 0 ? "" : " IN ID = ",
			KGRN,
			id < 0 ? "" : ft_itoa(id),
			KNRM);
	return (FUNCTION_FAILURE);
}

int	rc_jtoc_is_num(enum e_type type)
{
	return (type == fractional || type == integer);
}

static t_list	*get_node_by_index_in_content_size(t_list *lst, int index)
{
    while (lst)
    {
        if (lst->content_size == (size_t)index)
            return (lst);
        lst = lst->next;
    }
    return (NULL);
}

int	rc_jtoc_fill_texture_by_index(int ***texture, t_conf_json *conf, t_jnode *n)
{
    t_jnode	*tmp;
    t_list	*cur_lst;

    if (!(tmp = jtoc_node_get_by_path(n, "index")) || !rc_jtoc_is_num(tmp->type))
        return (rc_jtoc_sdl_log_error("TEXTURE INDEX FAILURE", -1));
    cur_lst = get_node_by_index_in_content_size(conf->textures, jtoc_get_int(tmp));
    if (cur_lst == NULL)
        return (rc_jtoc_sdl_log_error("GET TEXTURE BY INDEX FAILURE", -1));
    *texture = (int **)cur_lst->content;
    return (FUNCTION_SUCCESS);
}
