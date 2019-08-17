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

static char	**create_tmp_arr_and_find_sizes(int fd, t_rc_main *wlf)
{
	char    *line;
	char    *all_lines;
	char    **tmp_arr;

	get_next_line(fd, &line);
	wlf->map_h = 1;
	wlf->map_w = ft_strwcnumber(line, ' ');
	all_lines = ft_strdup(line);
	free(line);
	while (get_next_line(fd, &line) == 1)
	{
	    if (ft_strwcnumber(line, ' ') != (size_t)wlf->map_w)
            return (NULL);
		all_lines = ft_str_space_plus_join_free(all_lines, line);
		free(line);
		wlf->map_h++;
	}
	tmp_arr = ft_strsplit(all_lines, ' ');
	free(all_lines);
	return (tmp_arr);
}

static int	map_read(t_rc_main *m, int fd)
{
	char	**tmp_arr;
	int		i;
	int		j;
	int		k;
	int		**map;

	i = -1;
	k = -1;
	tmp_arr = create_tmp_arr_and_find_sizes(fd, m);
	if (!tmp_arr || m->map_w == 1 || m->map_h == 1)
	    return (rc_jtoc_sdl_log_error("MAP NOT VALID (BAD READING OR STRINGS SIZE)", -1));
	map = (int **)ft_memalloc(sizeof(int *) * m->map_h);
	while (++i < m->map_h)
	{
		j = -1;
		map[i] = (int *)ft_memalloc(sizeof(int) * m->map_w);
		while (++j < m->map_w)
			map[i][j] = ft_atoi(tmp_arr[++k]);
	}
	i = -1;
	while (++i < m->map_w)
	{
		j = -1;
		printf("\n");
		while (++j < m->map_h)
			printf("%d ", map[j][i]);
	}
	m->map = map;
	ft_clear_double_pointer((void **)tmp_arr, m->map_w * m->map_h);
	return (FUNCTION_SUCCESS);
}

int rc_jtoc_get_map(t_rc_main *m, char *path)
{
	int	fd;

	if ((fd = open(path, O_RDONLY)) == -1)
		return (rc_jtoc_sdl_log_error("OPEN MAP FAILURE", -1));
	if (map_read(m, fd))
		return (FUNCTION_FAILURE);
    if (rc_jtoc_processing_map(m))
        return (rc_jtoc_sdl_log_error("MAP NOT VALID", -1));
	return (FUNCTION_SUCCESS);
}
