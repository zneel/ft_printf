# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/23 18:49:32 by ebouvier          #+#    #+#              #
#    Updated: 2018/11/01 13:28:57 by ebouvier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a
CC			= cc
CFLAGS		= -Wall -Wextra -Werror
SRCS		= ft_printf.c \
				ft_atoi.c \
				ft_isdigit.c \
				ft_putchar.c \
				ft_putnbr.c \
				ft_putstr.c \
				ft_strlen.c

OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs libftprintf.a $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

dev: all
	$(CC) $(CFLAGS) main.c $(OBJS)

.PHONY: all clean fclean re dev
