#include "raycast.h"

static char	*ft_str_space_plus_join_free(char *s, char const *s1)
{
	char    *check;
	char    *a;
	int     i;

	i = 0;
	check = s;
	a = (char*)malloc(ft_strlen(s) + ft_strlen(s1) + 2);
	if (a)
	{
		while (*s)
		{
			a[i++] = *s;
			s++;
		}
		a[i++] = ' ';
		while (*s1)
		{
			a[i++] = *s1;
			s1++;
		}
		a[i] = '\0';
	}
	free(check);
	return (a);
}
//TODO сделать обработку строк разной длины
static char	**create_tmp_arr_and_find_sizes(int fd, t_rc_main *wlf)
{
	char    *line;
	char    *all_lines;
	char    **tmp_arr;

	get_next_line(fd, &line);
	wlf->h_map = 1;
	wlf->w_map = ft_strwcnumber(line, ' ');
	all_lines = ft_strdup(line);
	free(line);
	while (get_next_line(fd, &line) == 1)
	{
		all_lines = ft_str_space_plus_join_free(all_lines, line);
		free(line);
		wlf->h_map++;
	}
	tmp_arr = ft_strsplit(all_lines, ' ');
	free(line);
	free(all_lines);
	return (tmp_arr);
}

static int	map_read(t_rc_main *wlf, int fd)
{
	char	**tmp_arr;
	int		i;
	int		j;
	int		k;
	int		**map;

	i = -1;
	k = -1;
	tmp_arr = create_tmp_arr_and_find_sizes(fd, wlf);
//TODO сделать обработку строк разной длины
	if (!tmp_arr)
		return (FUNCTION_FAILURE);
	map = (int **)ft_memalloc(sizeof(int *) * wlf->h_map);
	while (++i < wlf->h_map)
	{
		j = -1;
		map[i] = (int *)ft_memalloc(sizeof(int) * wlf->w_map);
		while (++j < wlf->w_map)
			map[i][j] = ft_atoi(tmp_arr[++k]);
	}
	wlf->map = map;
	ft_clear_double_pointer((void **)tmp_arr, wlf->w_map * wlf->h_map);
	return (FUNCTION_SUCCESS);
}

int	rc_jtoc_get_map(t_rc_main *wlf, char *path)
{
	int	fd;

	if (!(fd = open(path, O_RDONLY)))
		return (rc_jtoc_sdl_log_error("OPEN MAP FAILURE", -1));
	if (map_read(wlf, fd))
		return (FUNCTION_FAILURE);
	return (FUNCTION_SUCCESS);
}
