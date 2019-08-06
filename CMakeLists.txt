cmake_minimum_required(VERSION 3.14)

cmake_policy(SET CMP0076 NEW)
project(WOLF3D LANGUAGES C)

#set(CMAKE_C_STANDARD 11)

add_executable(Wolf3D)

#add C flags
#set(GCC_COMPILE_FLAGS "-Wall -Werror -Wextra -O3")
#add_definitions(${GCC_COMPILE_FLAGS})

#add sdl2
#list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/sdl2-cmake-modules)
set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/sdl2-cmake-modules)

set_target_properties(Wolf3D
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
        )

if (NOT SDL2_FOUND)
    set(SDL2_PATH /Users/$ENV{USER}/.brew/Cellar/sdl2/2.0.9_1)
endif()

if (NOT SDL2_IMAGE_FOUND)
    set(SDL2_IMAGE_PATH /Users/$ENV{USER}/.brew/Cellar/sdl2_image/2.0.5)
endif()

if (NOT SDL2_TTF_FOUND)
    set(SDL2_TTF_PATH /Users/$ENV{USER}/.brew/Cellar/sdl2_ttf/2.0.15)
endif()

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

#add custom libs
add_subdirectory(libft)
add_subdirectory(libjtoc)

#linking libraries and includes
set(${PROJECT_NAME}_INCLUDE_DIRS
        ${PROJECT_SOURCE_DIR}/include
        ${LIBFT_INCLUDE_DIRS}
        ${LIBJTOC_INCLUDE_DIRS})
message(${WOLF3D_INCLUDE_DIRS})

include_directories(
        ${WOLF3D_INCLUDE_DIRS}
)

target_link_libraries(Wolf3D
        ft
        jtoc
        SDL2::Core
        SDL2::Image
        SDL2::TTF)

add_subdirectory(src)

#install(TARGETS Wolf3D DESTINATION .)
