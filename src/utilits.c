#include "raycast.h"

int			rgb_mod(float mod, int rgb)
{
	int		color;
	Uint8	r_s;
	Uint8	g_s;
	Uint8	b_s;

	r_s = (0.f - ((rgb >> 16) & 0xFF)) * mod + ((rgb >> 16) & 0xFF);
	g_s = (0.f - ((rgb >> 8) & 0xFF)) * mod + ((rgb >> 8) & 0xFF);
	b_s = (0.f - (rgb & 0xFF)) * mod + (rgb & 0xFF);
	color = ((((r_s & 0xFF) << 16)) + (((g_s & 0xFF) << 8)) + (((b_s & 0xFF))));
	return (color);
}

float		clmp(float a, float min, float max)
{
	if (a > max)
		a = max;
	else if (a < min)
		a = min;
	return (a);
}
