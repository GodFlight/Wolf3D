#include "wolf3d.h"

char    *ft_str_space_plus_join_free(char *s, char const *s1)
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

char    **create_tmp_arr_and_find_sizes(int fd, t_picture *map)
{
	char    *line;
	char    *all_lines;
	char    **tmp_arr;

	get_next_line(fd, &line);
	map->size_y = 1;
	map->size_x = ft_strwcnumber(line, ' ');
	all_lines = ft_strdup(line);
	free(line);
	while (get_next_line(fd, &line) == 1)
	{
		all_lines = ft_str_space_plus_join_free(all_lines, line);
		free(line);
		map->size_y++;
	}
	tmp_arr = ft_strsplit(all_lines, ' ');
	free(line);
	free(all_lines);
	return (tmp_arr);
}

void	map_read(t_wolf *wlf);
{
	char    **tmp_arr;
	int     i;

	tmp_arr = create_tmp_arr_and_find_sizes(fd, map);
}