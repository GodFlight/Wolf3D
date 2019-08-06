#include "raycast.h"

int			rgb_to_hex(int r, int g, int b)
{
	int		res = 0;
	int		alpha = 0;

	alpha |= 16777215;
	res = r << 16 | g << 8 | b;
	res &= alpha;
	return (res);
}
