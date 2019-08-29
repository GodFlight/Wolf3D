cmake_minimum_required(VERSION 3.14)

cmake_policy(SET CMP0076 NEW)

target_sources(Wolf3D PUBLIC
        init.c
        main.c
        draw_loop.c
        physic_loop.c
        main_loop.c
        raycast_and_draw.c
        draw_objects.c
        sound.c
        raycast_helper.c
        screaming_control.c
        utilits.c
        )

add_subdirectory(rc_jtoc)