//
// Created by Racquel Keli on 2019-07-30.
//

#ifndef WOLF3D_DEFINE_H
#define WOLF3D_DEFINE_H

# define WOLF_QUIT (1 << 0)

/*
** WINDOW
*/

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080

/*
** MAP
*/

# define MAP_PATH "../maps/map_01"
# define MAP_PATH_TWO "/Users//Desktop/Wolf3D/maps/map_02"
# define MAP_SCALE 30

/*
** PHYSICS
*/

# define PLAYER_SPEED 20
# define ROTATION_SPEED 0.08f

/*
** RAYCAST
*/

# define COLUM 64
# define FOV M_PI / 3

/*
** COLOR
*/

# define BLACK 0x00000000
# define WHITE 0xFFFFFFFF
# define GREEN 0x00FF0000
# define GRAY 0xC6E3E400
# define DGRAY 0xa9a9a900
# define BLUE 0x0000FF00
# define RED 0xFF000000

/*
** LOGIC
*/

# define TRUE 1
# define FALSE 0

#endif //WOLF3D_DEFINE_H
