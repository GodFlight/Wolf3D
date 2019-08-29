/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 23:22:19 by rkeli             #+#    #+#             */
/*   Updated: 2019/08/28 23:48:08 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char	*str;
	size_t	i;
	size_t	rmb;
	size_t	j;

	j = 0;
	i = 0;
	if (!s)
		return (0);
	rmb = ft_strlen(s);
	while (s[i] == '\n' || s[i] == '\t' || s[i] == ' ')
		i++;
	if (i == rmb)
		return (ft_memalloc(1));
	while (s[rmb - 1] == '\n' || s[rmb - 1] == '\t' || s[rmb - 1] == ' ')
		rmb--;
	rmb--;
	if (!(str = (char *)malloc(sizeof(char) * (rmb - i + 2))))
		return (0);
	while (i <= rmb)
		str[j++] = s[i++];
	str[j] = '\0';
	return (str);
}
