//
// Created by Racquel Keli on 2019-07-30.
//

#ifndef WOLF3D_DEFINE_H
#define WOLF3D_DEFINE_H

# define QUIT_PROGRAM (1 << 0)

/*
** MAP
*/

# define MAP_SCALE 30

/*
** PHYSICS
*/

# define PI_2 6.28318530717958647692528676655900576
# define PLAYER_SPEED 7
# define ROTATION_SPEED 0.1f

/*
** RAYCAST
*/

# define COLUM 64
# define FOG_DIST 3.f
# define FOV M_PI / 2
# define PLAYER_HEIGHT 32
//# define FOV 66 * M_PI / 180

/*
** COLOR
*/

# define BLACK 0x00000000
# define WHITE 0xFFFFFFFF
# define GREEN 0x00FF0000
# define GRAY 0xd3d3d3
# define DGRAY 0xa9a9a9
# define BLUE 0x0000FF00
# define RED 0xFF000000

/*
** LOGIC
*/

# define TRUE 1
# define FALSE 0

#endif //WOLF3D_DEFINE_H
