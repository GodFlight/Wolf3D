//
// Created by Racquel Keli on 2019-07-30.
//

#ifndef WOLF3D_DEFINE_H
#define WOLF3D_DEFINE_H

# define QUIT_PROGRAM (1 << 0)
# define MAP_WITH_SCREAMER 1

/*
**	SOUND
*/

# define MUS_PATH "./sound/scary.wav"
# define WHITE_NOISE "./sound/white_noise.wav"
# define CHAIN_SAW "./sound/chainsaw.wav"
# define SCREAM "./sound/scream.wav"

/*
** RAYCAST
*/

# define COLUM 64
# define FOG_DIST 1.8f
# define FOG_DIST_OBJ 1.95f

/*
** COLOR
*/

# define KNRM				"\x1B[0m"
# define KRED				"\x1B[31m"
# define KGRN				"\x1B[32m"
# define KYEL				"\x1B[33m"
# define KBLU				"\x1B[34m"
# define KMAG				"\x1B[35m"
# define KCYN				"\x1B[36m"
# define KWHT				"\x1B[37m"

#endif //WOLF3D_DEFINE_H
