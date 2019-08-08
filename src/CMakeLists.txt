cmake_minimum_required(VERSION 3.14)

cmake_policy(SET CMP0076 NEW)

target_sources(Wolf3D PUBLIC
        draw_interface.c
        init.c
        main.c
        main_loop.c
        physics.c
        player_raycast.c
        )

add_subdirectory(rc_jtoc)
add_subdirectory(rc_utilits)