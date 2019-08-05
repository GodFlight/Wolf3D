cmake_minimum_required(VERSION 3.0)

cmake_policy(SET CMP0076 NEW)

project(LIBJTOC VERSION 1.0.0 LANGUAGES C)

add_library(jtoc STATIC)

set(${PROJECT_NAME}_INCLUDE_DIRS
        ${PROJECT_SOURCE_DIR}/include
        ${LIBFT_INCLUDE_DIRS}
        CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

include_directories(${LIBJTOC_INCLUDE_DIRS})

add_subdirectory(src)