/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jtoc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbednar <sbednar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 00:34:11 by sbednar           #+#    #+#             */
/*   Updated: 2019/06/02 20:35:23 by sbednar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libjtoc.h"

int			jtoc_find(const char *str, const char s, int i, int p)
{
	while (i >= 0 && str[i])
	{
		if (str[i] == s)
			return (i);
		if (p & F_ONLY_SPACES && !ft_isstn(str[i]))
			return (-1);
		i += p & F_RIGHT ? 1 : -1;
	}
	return (-1);
}

int			jtoc_find_comma(const char *str, int i)
{
	int	bro;
	int	bra;
	int	q;

	bro = 0;
	bra = 0;
	q = 0;
	while (str[i])
	{
		bro += (str[i] == '{' ? 1 : 0);
		bro -= (str[i] == '}' ? 1 : 0);
		bra += (str[i] == '[' ? 1 : 0);
		bra -= (str[i] == ']' ? 1 : 0);
		if (str[i] == '"')
			q = (q + 1) % 2;
		if (str[i] == ',' && !bro && !bra && !q)
			return (i);
		++i;
	}
	return (-1);
}

static int	jtoc_strlen_wstn(char *str)
{
	int		ns;
	int		len;
	int		q;

	len = -1;
	ns = 0;
	q = 0;
	while (str[++len])
	{
		if (str[len] == '"')
			q = (q + 1) % 2;
		if (!ft_isstn(str[len]) || q)
			++ns;
	}
	return (ns);
}

int			jtoc_remove_spaces(char **str)
{
	int		ns;
	int		len;
	int		q;
	char	*tmp;

	if (!str || !*str || !(tmp = ft_strnew(jtoc_strlen_wstn(*str))))
		return (FUNCTION_FAILURE);
	len = -1;
	ns = -1;
	q = 0;
	while (str[0][++len])
	{
		if (str[0][len] == '"')
			q = (q + 1) % 2;
		if (!ft_isstn(str[0][len]) || q)
			tmp[++ns] = str[0][len];
	}
	free(*str);
	*str = tmp;
	return (FUNCTION_SUCCESS);
}

enum e_type	jtoc_get_field_type(char *f)
{
	if (*f == '[')
		return (array);
	if (*f == '{')
		return (object);
	if (*f == '"')
		return (string);
	if (*f == '-' || (*f >= '0' && *f <= '9'))
	{
		if (*f == '-')
			++f;
		while (ft_isdigit(*f))
			++f;
		return (*f == '.' ? fractional : integer);
	}
	return (none);
}
