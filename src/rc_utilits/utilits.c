#include "raycast.h"

int rgb_mod(float mod, int r, int g, int b)
{
	int		color;
	Uint8	r_s;
	Uint8	g_s;
	Uint8	b_s;

	r_s = (0.f - r) * mod + r;
	g_s = (0.f - g) * mod + g;
	b_s = (0.f - b) * mod + b;
	color = ((((r_s & 0xFF) << 16)) + (((g_s & 0xFF) << 8)) + (((b_s & 0xFF))));
	return (color);
}

int			rgb_to_hex(char r, char g, char b)
{
	int		res = 0;
//	int		alpha = 0;

//	alpha |= 16777215;
	res = r << 24 | g << 16 | b;
//	res &= alpha;
	return (res);
}

float		clmp(float a, float min, float max)
{
	if (a > max)
		a = max;
	else if (a < min)
		a = min;
	return (a);
}
