# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ebouvier <ebouvier@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/23 18:49:32 by ebouvier          #+#    #+#              #
#    Updated: 2018/10/19 00:26:59 by ebouvier         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libftprintf.a
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
SRCS		= ft_printf.c
OBJS		= $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	ar rcs tmplibftprintf.a $(OBJS)
	libtool -static -o $(NAME) tmplibftprintf.a libft/libft.a
	rm -rf tmplibftprintf.a

clean:
	make -C libft clean
	rm -f $(OBJS)

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

dev: all
	@$(CC) $(CFLAGS) main.c helpers.c libftprintf.a

.PHONY: all clean fclean re
