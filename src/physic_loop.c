
#include "raycast.h"
#include "debug_log.h"

static void	move_player(t_rc_main *m, t_sdl *sdl, float speed)
{
	float	dir_mult_speed_x;
	float	dir_mult_speed_y;

	if ((sdl->state[SDL_SCANCODE_W] || sdl->state[SDL_SCANCODE_S]) && (sdl->state[SDL_SCANCODE_A] || sdl->state[SDL_SCANCODE_D]))
		speed *= 0.5;

	if (sdl->state[SDL_SCANCODE_W] || sdl->state[SDL_SCANCODE_S])
	{
		dir_mult_speed_x = m->player.fdir_x * speed;
		dir_mult_speed_y = m->player.fdir_y * speed;
		if (sdl->state[SDL_SCANCODE_W])
		{
			SDL_LockMutex(sdl->mutex);
			if (m->phys_map[(int) (m->player.x + dir_mult_speed_x)][(int) (m->player.y)] == 0)
				m->player.x += dir_mult_speed_x;
			if (m->phys_map[(int) m->player.x][(int) (m->player.y + dir_mult_speed_y)] == 0)
				m->player.y += dir_mult_speed_y;
			if (m->phys_map[(int) (m->player.x + 0.2f)][(int) (m->player.y)] != 0)
				m->player.x = (int) (m->player.x + 1.f) - 0.2f;
			else if (m->phys_map[(int) (m->player.x - 0.2f)][(int) (m->player.y)] != 0)
				m->player.x = (int) (m->player.x) + 0.2f;
			if (m->phys_map[(int) (m->player.x)][(int) (m->player.y + 0.2f)] != 0)
				m->player.y = (int) (m->player.y + 1.f) - 0.2f;
			else if (m->phys_map[(int) (m->player.x)][(int) (m->player.y - 0.2f)] != 0)
				m->player.y = (int) (m->player.y) + 0.2f;
			SDL_UnlockMutex(sdl->mutex);
		}
		else
		{
			SDL_LockMutex(sdl->mutex);
			if (m->phys_map[(int) (m->player.x - dir_mult_speed_x)][(int) (m->player.y)] == 0)
				m->player.x -= dir_mult_speed_x;
			if (m->phys_map[(int) m->player.x][(int) (m->player.y - dir_mult_speed_y)] == 0)
				m->player.y -= dir_mult_speed_y;
			if (m->phys_map[(int) (m->player.x + 0.2f)][(int) (m->player.y)] != 0)
				m->player.x = (int) (m->player.x + 1.f) - 0.2f;
			else if (m->phys_map[(int) (m->player.x - 0.2f)][(int) (m->player.y)] != 0)
				m->player.x = (int) (m->player.x) + 0.2f;
			if (m->phys_map[(int) (m->player.x)][(int) (m->player.y + 0.2f)] != 0)
				m->player.y = (int) (m->player.y + 1.f) - 0.2f;
			else if (m->phys_map[(int) (m->player.x)][(int) (m->player.y - 0.2f)] != 0)
				m->player.y = (int) (m->player.y) + 0.2f;
			SDL_UnlockMutex(sdl->mutex);
		}
	}
	if (sdl->state[SDL_SCANCODE_A] || sdl->state[SDL_SCANCODE_D])
	{
		dir_mult_speed_x = m->player.rdir_x * speed;
		dir_mult_speed_y = m->player.rdir_y * speed;
		if (sdl->state[SDL_SCANCODE_A])
		{
			SDL_LockMutex(sdl->mutex);
			if (m->phys_map[(int) (m->player.x - dir_mult_speed_x)][(int) (m->player.y)] == 0)
				m->player.x -= dir_mult_speed_x;
			if (m->phys_map[(int) m->player.x][(int) (m->player.y - dir_mult_speed_y)] == 0)
				m->player.y -= dir_mult_speed_y;
			if (m->phys_map[(int) (m->player.x + 0.2f)][(int) (m->player.y)] != 0)
				m->player.x = (int) (m->player.x + 1.f) - 0.2f;
			else if (m->phys_map[(int) (m->player.x - 0.2f)][(int) (m->player.y)] != 0)
				m->player.x = (int) (m->player.x) + 0.2f;
			if (m->phys_map[(int) (m->player.x)][(int) (m->player.y + 0.2f)] != 0)
				m->player.y = (int) (m->player.y + 1.f) - 0.2f;
			else if (m->phys_map[(int) (m->player.x)][(int) (m->player.y - 0.2f)] != 0)
				m->player.y = (int) (m->player.y) + 0.2f;
			SDL_UnlockMutex(sdl->mutex);
		}
		else
		{
			SDL_LockMutex(sdl->mutex);
			if (m->phys_map[(int) (m->player.x + dir_mult_speed_x)][(int) (m->player.y)] == 0)
				m->player.x += dir_mult_speed_x;
			if (m->phys_map[(int) m->player.x][(int) (m->player.y + dir_mult_speed_y)] == 0)
				m->player.y += dir_mult_speed_y;
			if (m->phys_map[(int) (m->player.x + 0.2f)][(int) (m->player.y)] != 0)
				m->player.x = (int) (m->player.x + 1.f) - 0.2f;
			else if (m->phys_map[(int) (m->player.x - 0.2f)][(int) (m->player.y)] != 0)
				m->player.x = (int) (m->player.x) + 0.2f;
			if (m->phys_map[(int) (m->player.x)][(int) (m->player.y + 0.2f)] != 0)
				m->player.y = (int) (m->player.y + 1.f) - 0.2f;
			else if (m->phys_map[(int) (m->player.x)][(int) (m->player.y - 0.2f)] != 0)
				m->player.y = (int) (m->player.y) + 0.2f;
			SDL_UnlockMutex(sdl->mutex);
		}
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
	float	sin_speed;
	float	cos_speed;

	fdir_x = m->player.fdir_x;
	fdir_y = m->player.fdir_y;
	rdir_x = m->player.rdir_x;
	rdir_y = m->player.rdir_y;
	plane_x = m->player.plane_x;
	plane_y = m->player.plane_y;
	if (sdl->state[SDL_SCANCODE_LEFT] || sdl->state[SDL_SCANCODE_Q])
	{
		cos_speed = cosf(speed);
		sin_speed = sinf(speed);
		SDL_LockMutex(sdl->mutex);
		m->player.fdir_x = fdir_x * cos_speed - fdir_y * sin_speed;
		m->player.fdir_y = fdir_x * sin_speed + fdir_y * cos_speed;
		m->player.rdir_x = rdir_x * cos_speed - rdir_y * sin_speed;
		m->player.rdir_y = rdir_x * sin_speed + rdir_y * cos_speed;
		m->player.plane_x = plane_x * cos_speed - plane_y * sin_speed;
		m->player.plane_y = plane_x * sin_speed + plane_y * cos_speed;
		SDL_UnlockMutex(sdl->mutex);
	}
	if (sdl->state[SDL_SCANCODE_RIGHT] || sdl->state[SDL_SCANCODE_E])
	{
		cos_speed = cosf(-speed);
		sin_speed = sinf(-speed);
		SDL_LockMutex(sdl->mutex);
		m->player.fdir_x = fdir_x * cos_speed - fdir_y * sin_speed;
		m->player.fdir_y = fdir_x * sin_speed + fdir_y * cos_speed;
		m->player.rdir_x = rdir_x * cos_speed - rdir_y * sin_speed;
		m->player.rdir_y = rdir_x * sin_speed + rdir_y * cos_speed;
		m->player.plane_x = plane_x * cos_speed - plane_y * sin_speed;
		m->player.plane_y = plane_x * sin_speed + plane_y * cos_speed;
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
		if (sdl->state[SDL_SCANCODE_LSHIFT])
		    move_speed = frame_time * 0.0015;
		else
            move_speed = frame_time * 0.001;
		rot_speed = frame_time * 0.003;
		if (sdl->state[SDL_SCANCODE_W] || sdl->state[SDL_SCANCODE_S]
			|| sdl->state[SDL_SCANCODE_A] || sdl->state[SDL_SCANCODE_D])
			move_player(m, sdl, move_speed);
		rotation_player(m, sdl, rot_speed);
	}
	return (0);
}
