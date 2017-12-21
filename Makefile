# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bjanik <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/02/08 10:54:38 by bjanik            #+#    #+#              #
#    Updated: 2017/04/10 20:22:49 by bjanik           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_ls

CC = gcc

FLAGS = -Wall -Wextra -Werror

LIBFT = libft

LIB = libft/libft.a

HEADER = includes

SRCS = srcs/main.c \
	   srcs/errors.c \
	   srcs/display.c \
	   srcs/ft_ls.c \
	   srcs/linked_list.c \
	   srcs/parsing.c \
	   srcs/handle_l_option.c \
	   srcs/rights.c \
	   srcs/merge_sort.c \
	   srcs/max.c \
	   srcs/links.c \
	   srcs/options.c \

all : $(NAME)

$(NAME) :
	make -C $(LIBFT)
	$(CC) $(FLAGS) $(SRCS) $(LIB) -I $(HEADER) -I $(LIBFT) -o $(NAME)

clean :
	make clean -C $(LIBFT)

fclean :
	make fclean -C $(LIBFT)
	rm -f $(NAME)

re : fclean all
