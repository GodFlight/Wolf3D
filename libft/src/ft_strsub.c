/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.distance                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:00:08 by rkeli             #+#    #+#             */
/*   Updated: 2019/06/18 14:15:23 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*fs;
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	if (!(fs = (char*)malloc(sizeof(char) * (len + 1))))
		return (0);
	while (len-- > 0 && s[start] != '\0')
	{
		fs[i] = s[start];
		i++;
		start++;
	}
	fs[i] = '\0';
	return (fs);
}
