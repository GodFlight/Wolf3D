cmake_minimum_required(VERSION 3.14)

cmake_policy(SET CMP0076 NEW)

target_sources(Wolf3D PUBLIC
        setup_game_from_json.c
        init.c
        map_read.c
        )

