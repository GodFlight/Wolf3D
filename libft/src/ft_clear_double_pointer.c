//
// Created by Slaughterfish Becker on 2019-08-06.
//

#include "libft.h"

void    ft_clear_double_pointer(void **arr, int size)
{
	int i;

	if (arr && *arr)
	{
		i = 0;
		while (i < size)
		{
			free(arr[i]);
			arr[i] = NULL;
			i++;
		}
		free(arr);
	}
}
