# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkeli <rkeli@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/21 16:59:28 by rkeli             #+#    #+#              #
#    Updated: 2019/08/29 06:55:02 by rkeli            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libft.a
SRCS := ft_strlcat.c\
		ft_strlen.c\
		ft_strcmp.c\
		ft_strncmp.c\
		ft_strnequ.c\
		ft_strequ.c\
		ft_atoi.c\
		ft_isalpha.c\
		ft_isdigit.c\
		ft_isalnum.c\
		ft_isascii.c\
		ft_isprint.c\
		ft_toupper.c\
		ft_memchr.c\
		ft_memmove.c\
		ft_memset.c\
		ft_memcpy.c\
		ft_bzero.c\
		ft_memccpy.c\
		ft_memalloc.c\
		ft_striteri.c\
		ft_striter.c\
		ft_memdel.c\
		ft_strdel.c\
		ft_strclr.c\
		ft_putendl.c\
		ft_putendl_fd.c\
		ft_putchar.c\
		ft_putchar_fd.c\
		ft_putnbr.c\
		ft_putstr.c\
		ft_putstr_fd.c\
		ft_putnbr_fd.c\
		ft_strnew.c\
		ft_itoa.c\
		ft_strdup.c\
		ft_strcpy.c\
		ft_strncpy.c\
		ft_strcat.c\
		ft_strncat.c\
		ft_strchr.c\
		ft_strrchr.c\
		ft_strjoin.c\
		ft_strtrim.c\
		ft_strsub.c\
		ft_strmap.c\
		ft_strmapi.c\
		ft_strsplit.c\
		ft_strstr.c\
		ft_strnstr.c\
		ft_lstnew.c\
		ft_lstadd.c\
		ft_lstiter.c\
		ft_lstdelone.c\
		ft_lstdel.c\
		ft_lstmap.c\
		ft_lstnormdelone.c\
		ft_lstnormdel.c\
		ft_tolower.c\
		ft_memcmp.c\
		ft_updt.c\
		ft_swap.c\
		ft_sort_bubl.c\
		get_next_line.c\
		ft_itoa_base.c\
		ft_clear_double_pointer.c\
		ft_fswap.c\
		ft_isstn.c\
		ft_strhash.c\
		ft_strwcnumber.c\
		ft_quick_sort.c

OBJS := $(SRCS:.c=.o)
HEADERS := ./include/libft.h ./include/get_next_line.h
INCLUDE := -I ./include
CC	:= gcc
CFLAGS := -Wextra -Werror -Wall -O3
DIR_BIN := bin/
REMOVE := rm -rf
DIR_LIBFT := .

vpath %.c $(DIR_LIBFT)/src/
vpath %.o $(DIR_BIN)
vpath %.h $(DIR_LIBFT)./include

all: $(NAME)

$(NAME): $(OBJS)
	@ar rc $@ $(addprefix $(DIR_BIN), $(OBJS))
	@ranlib $@

$(OBJS):%.o:%.c $(HEADERS) | $(DIR_BIN)
	$(CC) -c $< $(CFLAGS) -o $(DIR_BIN)$@ $(INCLUDE) -pipe

$(DIR_BIN):
	mkdir -p $@

echo:
	echo $(OBJS)

clean:
	$(REMOVE) $(addprefix $(DIR_BIN), $(OBJS))
	$(REMOVE) $(DIR_BIN)
fclean: clean
	$(REMOVE) $(NAME)

re: fclean all
