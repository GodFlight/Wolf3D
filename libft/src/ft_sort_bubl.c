/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_bubl.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 23:19:24 by rkeli             #+#    #+#             */
/*   Updated: 2019/08/28 23:48:08 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_sort_bubl(int ac, char **av)
{
	int		i;
	int		j;
	char	*swap;

	i = 2;
	while (i < ac)
	{
		j = i;
		while (j > 0 && (ft_strcmp(av[j], av[j - 1]) < 0))
		{
			swap = av[j];
			av[j] = av[j - 1];
			av[j - 1] = swap;
			j--;
		}
		i++;
	}
}
