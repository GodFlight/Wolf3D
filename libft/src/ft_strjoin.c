/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 23:20:45 by rkeli             #+#    #+#             */
/*   Updated: 2019/08/28 23:48:08 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*strconc;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	if (!(strconc = (char*)malloc(sizeof(char) *
				(ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	while (s2[i] != '\0' || s1[j] != '\0')
	{
		if (s1[j] != '\0')
			while (s1[j] != '\0')
			{
				strconc[j] = s1[j];
				j++;
			}
		strconc[j + i] = s2[i];
		i++;
	}
	strconc[j + i] = '\0';
	return (strconc);
}
