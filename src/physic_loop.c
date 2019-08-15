
#include "raycast.h"
#include "debug_log.h"

static void	move_player(t_rc_main *m, t_sdl *sdl, float speed)
{
	if (sdl->state[SDL_SCANCODE_W])
	{
		SDL_LockMutex(sdl->mutex);
		if (m->map[(int)(m->player.x + m->player.fdir_x * speed)][(int)(m->player.y)] == 0)
			m->player.x += m->player.fdir_x * speed;
		if (m->map[(int)(m->player.x)][(int)(m->player.y + m->player.fdir_y * speed)] == 0)
			m->player.y += m->player.fdir_y * speed;
		SDL_UnlockMutex(sdl->mutex);
	}
	if (sdl->state[SDL_SCANCODE_S])
	{
		SDL_LockMutex(sdl->mutex);
		if (m->map[(int)(m->player.x - m->player.fdir_x * speed)][(int)(m->player.y)] == 0)
			m->player.x -= m->player.fdir_x * speed;
		if (m->map[(int)(m->player.x)][(int)(m->player.y - m->player.fdir_y * speed)] == 0)
			m->player.y -= m->player.fdir_y * speed;
		SDL_UnlockMutex(sdl->mutex);
	}
	if (sdl->state[SDL_SCANCODE_A])
	{
		SDL_LockMutex(sdl->mutex);
		if (m->map[(int)(m->player.x - m->player.rdir_x * speed)][(int)(m->player.y)] == 0)
			m->player.x -= m->player.rdir_x * speed;
		if (m->map[(int)(m->player.x)][(int)(m->player.y - m->player.rdir_y * speed)] == 0)
			m->player.y -= m->player.rdir_y * speed;
		SDL_UnlockMutex(sdl->mutex);
	}
	if (sdl->state[SDL_SCANCODE_D])
	{
		SDL_LockMutex(sdl->mutex);
		if (m->map[(int)(m->player.x + m->player.rdir_x * speed)][(int)(m->player.y)] == 0)
			m->player.x += m->player.rdir_x * speed;
		if (m->map[(int)(m->player.x)][(int)(m->player.y + m->player.rdir_y * speed)] == 0)
			m->player.y += m->player.rdir_y * speed;
		SDL_UnlockMutex(sdl->mutex);
	}
}

static void	rotation_player(t_rc_main *m, t_sdl *sdl, float speed)
{
	float	fdir_x;
	float	fdir_y;
	float	rdir_x;
	float	rdir_y;
	float	plane_x;
	float	plane_y;

	fdir_x = m->player.fdir_x;
	fdir_y = m->player.fdir_y;
	rdir_x = m->player.rdir_x;
	rdir_y = m->player.rdir_y;
	plane_x = m->player.plane_x;
	plane_y = m->player.plane_y;
	if (sdl->state[SDL_SCANCODE_LEFT])
	{
		SDL_LockMutex(sdl->mutex);
		m->player.fdir_x = fdir_x * cos(speed) - fdir_y * sin(speed);
		m->player.fdir_y = fdir_x * sin(speed) + fdir_y * cos(speed);
		m->player.rdir_x = rdir_x * cos(speed) - rdir_y * sin(speed);
		m->player.rdir_y = rdir_x * sin(speed) + rdir_y * cos(speed);
		m->player.plane_x = plane_x * cos(speed) - plane_y * sin(speed);
		m->player.plane_y = plane_x * sin(speed) + plane_y * cos(speed);
		SDL_UnlockMutex(sdl->mutex);
	}
	if (sdl->state[SDL_SCANCODE_RIGHT])
	{
		SDL_LockMutex(sdl->mutex);
		m->player.fdir_x = fdir_x * cos(-speed) - fdir_y * sin(-speed);
		m->player.fdir_y = fdir_x * sin(-speed) + fdir_y * cos(-speed);
		m->player.rdir_x = rdir_x * cos(-speed) - rdir_y * sin(-speed);
		m->player.rdir_y = rdir_x * sin(-speed) + rdir_y * cos(-speed);
		m->player.plane_x = plane_x * cos(-speed) - plane_y * sin(-speed);
		m->player.plane_y = plane_x * sin(-speed) + plane_y * cos(-speed);
		SDL_UnlockMutex(sdl->mutex);
	}
}

int	physic_loop(void *m_v)
{
	t_rc_main	*m;
	t_sdl		*sdl;
	Uint32		time;
	Uint32		old_time;
	Uint32		frame_time;
	float		move_speed;
	float		rot_speed;

	m = (t_rc_main *)m_v;
	sdl = m->sdl;
	time = 0;
	while (!(m->params & QUIT_PROGRAM))
	{
			old_time = time;
			time = SDL_GetTicks();
			frame_time = time - old_time;
			move_speed = frame_time * 0.003;
			rot_speed = frame_time * 0.002;
			if (sdl->state[SDL_SCANCODE_W] || sdl->state[SDL_SCANCODE_S]
				|| sdl->state[SDL_SCANCODE_A] || sdl->state[SDL_SCANCODE_D])
				move_player(m, sdl, move_speed);
			rotation_player(m, sdl, rot_speed);
	}
	return (0);
}
