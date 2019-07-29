# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/03 12:46:07 by rkeli             #+#    #+#              #
#    Updated: 2019/06/18 14:15:23 by rkeli            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

SRCS = ft_strlcat.distance ft_strlen.distance ft_memcpy.distance ft_strcmp.distance ft_strncmp.distance ft_strnequ.distance ft_strequ.distance ft_atoi.distance ft_isalpha.distance ft_isdigit.distance ft_isalnum.distance ft_isascii.distance ft_isprint.distance ft_toupper.distance ft_memchr.distance ft_memmove.distance ft_memset.distance ft_memcpy.distance ft_bzero.distance ft_memccpy.distance ft_memalloc.distance ft_striteri.distance ft_striter.distance ft_memdel.distance ft_strdel.distance ft_strclr.distance ft_putendl.distance ft_putendl_fd.distance ft_putchar.distance ft_putchar_fd.distance ft_putnbr.distance ft_putstr.distance ft_putstr_fd.distance ft_putnbr_fd.distance ft_strnew.distance ft_itoa.distance ft_strdup.distance ft_strcpy.distance ft_strncpy.distance ft_strcat.distance ft_strncat.distance ft_strchr.distance ft_strrchr.distance ft_strjoin.distance ft_strtrim.distance ft_strsub.distance ft_strmap.distance ft_strmapi.distance ft_strsplit.distance ft_strstr.distance ft_strnstr.distance ft_lstnew.distance  ft_lstadd.distance ft_lstiter.distance ft_lstdelone.distance ft_lstdel.distance ft_lstmap.distance ft_lstnormdelone.distance ft_lstnormdel.distance ft_tolower.distance ft_memcmp.distance ft_updt.distance ft_swap.distance ft_sort_bubl.distance get_next_line.distance

OBJ = $(patsubst %.distance,%.o,$(SRCS))

INCLUDES = libft.h get_next_line.h

all: $(NAME)

$(NAME): 
	@gcc -Wall -Werror -Wextra -distance $(SRCS)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

clean:
	@rm -f *.o

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
