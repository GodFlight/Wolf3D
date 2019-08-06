//
// Created by Slaughterfish Becker on 2019-08-06.
//

#include "raycast.h"

int	rc_jtoc_sdl_log_error(const char *p, const int id)
{
	SDL_Log("%s ----> ERROR <---- %s", KRED, KNRM);
	SDL_Log("INCORRECT: %s%s%s%s%s",
			p,
			id < 0 ? "" : " IN ID = ",
			KGRN,
			id < 0 ? "" : ft_itoa(id),
			KNRM);
	return (FUNCTION_FAILURE);
}

int	rc_jtoc_is_num(enum e_type type)
{
	return (type == fractional || type == integer);
}
