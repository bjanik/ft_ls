# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bjanik <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/08 10:54:38 by bjanik            #+#    #+#              #
#    Updated: 2017/03/07 15:35:36 by bjanik           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

CC = gcc

FLAGS = -Wall -Wextra -Werror

LIBFT = libft

LIB = libft/libft.a

HEADER = includes

SRCS = srcs/main.c \
	   srcs/display.c \
	   srcs/ft_ls.c \
	   srcs/init.c \
	   srcs/parsing.c \
	   srcs/handle_l_option.c \
	   srcs/rights.c \
	   srcs/sort.c \

all : $(NAME)

$(NAME) :
	make -C $(LIBFT)
	$(CC) $(FLAGS) $(SRCS) $(LIB) -I $(HEADER) -o $(NAME)

clean :
	make clean -C $(LIBFT)

fclean :
	make fclean -C $(LIBFT)
	rm -f $(NAME)

re : fclean all
