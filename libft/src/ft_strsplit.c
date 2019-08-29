/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 23:21:57 by rkeli             #+#    #+#             */
/*   Updated: 2019/08/28 23:48:08 by rkeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void			free_split(char **str, size_t number_of_words)
{
	size_t index;

	index = 0;
	while (index <= number_of_words)
	{
		free(str[index]);
		index++;
	}
	free(str);
}

static size_t		symbol_count(const char *s, char c)
{
	size_t	i;

	i = 0;
	while (s[i] != c && s[i] != '\0')
		i++;
	return (i);
}

static char			*put_word_to_array(const char *s, char c,
									char **str_split, size_t number_of_words)
{
	char		*fs;
	size_t		j;

	j = 0;
	if (!(fs = (char*)malloc(sizeof(char) * (symbol_count(s, c) + 1))))
	{
		free_split(str_split, number_of_words);
		return (0);
	}
	while (s[j] != '\0' && s[j] != c)
	{
		fs[j] = s[j];
		j++;
	}
	fs[j] = '\0';
	return (fs);
}

static size_t		word_count(const char *s, char c)
{
	int			fl;
	size_t		i;
	size_t		count;

	i = 0;
	fl = 1;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && fl)
		{
			fl = 0;
			count++;
		}
		else if (s[i] == c && !fl)
			fl = 1;
		i++;
	}
	return (count);
}

char				**ft_strsplit(char const *s, char c)
{
	char		**fs;
	size_t		i;
	size_t		rmb;
	size_t		number_of_words;

	if (!s)
		return (0);
	number_of_words = word_count(s, c);
	rmb = 0;
	i = 0;
	if (!(fs = (char**)malloc(sizeof(char*) * (number_of_words + 1))))
		return (NULL);
	while (i < number_of_words)
	{
		while (s[rmb] == c && s[rmb] != '\0')
			rmb++;
		fs[i] = put_word_to_array(&s[rmb], c, fs, number_of_words);
		if (!fs[i])
			return (NULL);
		rmb = rmb + symbol_count(&s[rmb], c);
		i++;
	}
	fs[i] = NULL;
	return (fs);
}
