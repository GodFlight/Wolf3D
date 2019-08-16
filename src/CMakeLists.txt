cmake_minimum_required(VERSION 3.14)

cmake_policy(SET CMP0076 NEW)

target_sources(Wolf3D PUBLIC
        draw_interface.c
        init.c
        main.c
        draw_loop.c
        physic_loop.c
        main_loop.c
        raycast_and_draw.c
        draw_objects.c
        sound.c
        raycast_helper.c
        )

add_subdirectory(rc_jtoc)
add_subdirectory(rc_utilits)