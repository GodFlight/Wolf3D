#include "wolf3d.h"

static int 	y_size(char **buf)
{
	int i;

	i = 0;
	while(buf[i] != NULL)
		i++;
	return (i);
}

char	*read_file()
{
	int		fd;
	int		number;
	char 	*buff;

	fd = open(MAP_PATH, O_RDONLY);
	if (!(buff = (char*)malloc(sizeof(char) * 10000)))
		exit(12);
	number = read(fd, buff, 10000);
	buff[number] = '\0';
	close(fd);
	return (buff);
}

void	map_read(t_wolf *wlf)
{
	char	**buf;
	int		x;
	int		y;

	buf = ft_strsplit(read_file(), '\n');
	y = 0;
	wlf->len_xmap = ft_strlen(buf[y]);
	wlf->len_ymap = y_size(buf);
	if (!(wlf->map = (int**)malloc(sizeof(int*) * (wlf->len_ymap + 1))))
		exit(13);
	while (buf[y])
	{
		x = 0;
		if (!(wlf->map[y] = (int*)malloc(sizeof(int) * (ft_strlen(buf[y])))))
			exit(14);
		while(buf[y][x] != '\0')
		{
			wlf->map[y][x] = buf[y][x] - 48;
			x++;
		}
		y++;
	}
	wlf->map[y] = NULL;
	y = 0;
	while (buf[y] != NULL)
	{
		free(buf[y]);
		y++;
	}
}
