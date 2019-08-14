#include "raycast.h"

int 		rgb_mod(int color, float mod)
{
	char r = color >> 24;
	char g = (color << 8) >> 24;
	char b = (color << 16) >> 24;
	r = (float)r * mod;
	g = (float)g * mod;
	b = (float)b * mod;
	return (r << 16 | g << 8 | b);
}

int			rgb_to_hex(char r, char g, char b, char a)
{
	int		res = 0;
//	int		alpha = 0;

//	alpha |= 16777215;
	res = r << 24 | g << 16 | b << 8 | a;
//	res &= alpha;
	return (res);
}

int		clmp(int a, int min, int max)
{
	if (a > max)
		a = max;
	else if (a < min)
		a = min;
	return (a);
}
