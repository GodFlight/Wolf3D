/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.distance                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 19:17:13 by rkeli             #+#    #+#             */
/*   Updated: 2019/06/18 14:15:23 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;
	size_t	n;

	n = ft_strlen(needle);
	i = 0;
	if (*needle == '\0')
		return ((char*)haystack);
	while (haystack[i] != '\0')
	{
		if (!(ft_memcmp(haystack + i, needle, n)))
			return ((char *)haystack + i);
		i++;
	}
	return (NULL);
}
