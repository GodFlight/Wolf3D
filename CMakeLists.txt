cmake_minimum_required(VERSION 3.14)
project(Wolf3D C)

set(CMAKE_C_STANDARD 11)
set(GCC_COMPILE_FLAGS "-O3")

link_directories(/Users/$ENV{USER}/.brew/Cellar/sdl2/2.0.9_1/lib)
link_directories(/Users/$ENV{USER}/.brew/Cellar/sdl2_image/2.0.5/lib)
#link_directories(/Users/rkeli/Desktop/Wolf3D/stb)
include_directories(include)
include_directories(libft)

add_executable(Wolf3D
        include/wolf3d.h
        libft/ft_abs.c
        libft/ft_atoi.c
        libft/ft_bzero.c
        libft/ft_isalnum.c
        libft/ft_isalpha.c
        libft/ft_isascii.c
        libft/ft_isdigit.c
        libft/ft_isprint.c
        libft/ft_itoa.c
        libft/ft_itoa_base.c
        libft/ft_lstadd.c
        libft/ft_lstdel.c
        libft/ft_lstdelone.c
        libft/ft_lstiter.c
        libft/ft_lstmap.c
        libft/ft_lstnew.c
        libft/ft_lstnormdel.c
        libft/ft_lstnormdelone.c
        libft/ft_memalloc.c
        libft/ft_memccpy.c
        libft/ft_memchr.c
        libft/ft_memcmp.c
        libft/ft_memcpy.c
        libft/ft_memdel.c
        libft/ft_memmove.c
        libft/ft_memset.c
        libft/ft_putchar.c
        libft/ft_putchar_fd.c
        libft/ft_putendl.c
        libft/ft_putendl_fd.c
        libft/ft_putnbr.c
        libft/ft_putnbr_fd.c
        libft/ft_putstr.c
        libft/ft_putstr_fd.c
        libft/ft_sort_bubl.c
        libft/ft_strcat.c
        libft/ft_strchr.c
        libft/ft_strclr.c
        libft/ft_strcmp.c
        libft/ft_strcpy.c
        libft/ft_strdel.c
        libft/ft_strdup.c
        libft/ft_strequ.c
        libft/ft_striter.c
        libft/ft_striteri.c
        libft/ft_strjoin.c
        libft/ft_strlcat.c
        libft/ft_strlen.c
        libft/ft_strmap.c
        libft/ft_strmapi.c
        libft/ft_strncat.c
        libft/ft_strncmp.c
        libft/ft_strncpy.c
        libft/ft_strnequ.c
        libft/ft_strnew.c
        libft/ft_strnstr.c
        libft/ft_strrchr.c
        libft/ft_strsplit.c
        libft/ft_strstr.c
        libft/ft_strsub.c
        libft/ft_strtrim.c
        libft/ft_swap.c
        libft/ft_tolower.c
        libft/ft_toupper.c
        libft/ft_updt.c
        libft/get_next_line.c
        libft/get_next_line.h
        libft/libft.h srcs/main.c srcs/map_read.c srcs/player_movement.c srcs/player_raycast.c include/debug_log.h include/define.h srcs/init.c srcs/main_loop.c srcs/utilits.c)


target_include_directories(Wolf3D PRIVATE /Users/$ENV{USER}/.brew/Cellar/sdl2/2.0.9_1/include/SDL2)
target_include_directories(Wolf3D PRIVATE /Users/$ENV{USER}/.brew/Cellar/sdl2_image/2.0.5/include/SDL2)
target_link_libraries(Wolf3D
        "SDL2"
        "SDL2_image"
        )
