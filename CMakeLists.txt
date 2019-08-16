cmake_minimum_required(VERSION 3.14)

cmake_policy(SET CMP0076 NEW)
project(WOLF3D LANGUAGES C)

add_executable(Wolf3D)

#add sdl2
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/sdl2-cmake-modules)

set_target_properties(Wolf3D
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        )

if (APPLE)
    if (NOT SDL2_FOUND)
        set(SDL2_PATH /Users/$ENV{USER}/.brew/Cellar/sdl2/2.0.9_1)
    endif()

    if (NOT SDL2_IMAGE_FOUND)
        set(SDL2_IMAGE_PATH /Users/$ENV{USER}/.brew/Cellar/sdl2_image/2.0.5)
    endif()

    if (NOT SDL2_TTF_FOUND)
        set(SDL2_TTF_PATH /Users/$ENV{USER}/.brew/Cellar/sdl2_ttf/2.0.15)
    endif()

    if (NOT SDL2_MIXER_FOUND)
        set(SDL2_MIXER_PATH /Users/$ENV{USER}/.brew/Cellar/sdl2_ttf/2.0.4)
    endif()

endif()

if (NOT APPLE)
    set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
    set(THREADS_PREFER_PTHREAD_FLAG TRUE)
    find_package(Threads REQUIRED)
    if(NOT CMAKE_THREAD_LIBS_INIT)
        set(SDL2_THREADS_NOT_FOUND "Could NOT find Threads (Threads is required by SDL2).")
        if(SDL2_FIND_REQUIRED)
            message(FATAL_ERROR ${SDL2_THREADS_NOT_FOUND})
        endif()
    endif()
endif()

find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

#add C flags
if (APPLE)
    set(GCC_COMPILE_FLAGS "-Wall -Werror -Wextra -O3 -D APPLE___")
else()
    set(GCC_COMPILE_FLAGS "-O3")
endif()
add_definitions(${GCC_COMPILE_FLAGS})

#add custom libs
add_subdirectory(libft)
add_subdirectory(libjtoc)


#linking libraries and includes
set(${PROJECT_NAME}_INCLUDE_DIRS
        ${PROJECT_SOURCE_DIR}/include
        ${LIBFT_INCLUDE_DIRS}
        ${LIBJTOC_INCLUDE_DIRS})
message(${${PROJECT_NAME}_INCLUDE_DIRS})

include_directories(
        ${WOLF3D_INCLUDE_DIRS}
)

target_link_libraries(Wolf3D
        ft
        jtoc
        SDL2::Core
        SDL2::Main
        SDL2::Image
        SDL2::Mixer
        SDL2::TTF)

add_subdirectory(src)

install(TARGETS Wolf3D DESTINATION .)
