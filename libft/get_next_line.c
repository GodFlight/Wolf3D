/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.distance                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/12 13:35:22 by rkeli             #+#    #+#             */
/*   Updated: 2019/06/18 14:15:23 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			find_break_line(int fd, char **rmb, char **line)
{
	size_t	index;

	index = 0;
	while (1)
	{
		if (rmb[fd][index] == ENDL)
		{
			*line = ft_strsub(rmb[fd], 0, index);
			if (!(rmb[fd] = ft_updt(rmb[fd], ft_strdup(&rmb[fd][++index]))))
				return (-1);
			break ;
		}
		else if (rmb[fd][index] == END)
		{
			if (!(*line = ft_strdup(rmb[fd])))
				return (-1);
			ft_strdel(&rmb[fd]);
			break ;
		}
		index++;
	}
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static char		*rmb[FD_MAX_SIZE];
	char			buff[BUFF_SIZE + 1];
	size_t			number;

	if (fd > FD_MAX_SIZE || fd < 0 || !line ||
		BUFF_SIZE < 1 || read(fd, buff, 0) < 0)
		return (-1);
	rmb[fd] = !rmb[fd] ? ft_strnew(1) : rmb[fd];
	while ((number = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[number] = END;
		if (!(rmb[fd] = ft_updt(rmb[fd], ft_strjoin(rmb[fd], buff))))
			return (-1);
		if (ft_strchr(buff, ENDL))
			break ;
	}
	if (*(rmb[fd]) == 0)
		return (0);
	return (find_break_line(fd, rmb, line));
}
