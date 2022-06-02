# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vfiszbin <vfiszbin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/30 18:00:38 by vfiszbin          #+#    #+#              #
#    Updated: 2022/06/02 10:42:33 by vfiszbin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT_A = ./libft/libft.a

NAME = so_long

SRCS =	so_long.c\
		move_player.c\
		read_map.c\
		draw_map.c\
		check_map.c\

OBJS = ${SRCS:.c=.o}

INCLUDES = so_long.h

CC = gcc

RM = rm -f

FLAGS = -Wall -Wextra -Werror -g

LIBS = -L ./mlx -lmlx -L/usr/X11/include/../lib -lXext -lX11

.c.o: ${INCLUDES}
	${CC} ${FLAGS} -c $ $< -o ${<:.c=.o}

all: makemlx makelibft ${NAME}

makemlx:
	${MAKE} -C ./mlx

makelibft:
	${MAKE} -C ./libft

${NAME} : ${OBJS}
	
	${CC} ${FLAGS} ${OBJS} ${LIBFT_A} -o ${NAME} ${LIBS}

clean:
	${MAKE} clean -C ./mlx
	${MAKE} clean -C ./libft
	${RM} *.o

fclean: clean
	${MAKE} fclean -C ./libft
	${RM} *.o
	${RM} so_long

re: fclean all

.PHONY: all clean fclean re