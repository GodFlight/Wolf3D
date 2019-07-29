/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.distance                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 14:07:34 by rkeli             #+#    #+#             */
/*   Updated: 2019/06/18 14:15:23 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strnstr(const char *haystack,
						const char *needle, size_t len)
{
	size_t	i;
	size_t	n;

	n = ft_strlen(needle);
	i = 0;
	if (*needle == '\0')
		return ((char*)&haystack[i]);
	if (len == 0)
		return (NULL);
	while (haystack[i] != '\0' && i <= len)
	{
		if ((n + i <= len) && (!(ft_memcmp(haystack + i, needle, n))))
			return ((char*)haystack + i);
		i++;
	}
	return (NULL);
}
