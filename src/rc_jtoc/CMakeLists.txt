cmake_minimum_required(VERSION 3.14)

cmake_policy(SET CMP0076 NEW)

target_sources(Wolf3D PUBLIC
        rc_jtoc_get_map.c
        rc_jtoc_main_from_json.c
        rc_jtoc_win_from_json.c
        rc_jtoc_utilits.c
        rc_jtoc_get_textures.c
        rc_jtoc_obj_utilits.c
        rc_jtoc_get_default_walls.c
        rc_jtoc_get_walls.c
        rc_jtoc_processing_map.c
        rc_jtoc_get_objects.c
        rc_jtoc_get_player.c
        )

