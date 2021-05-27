# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/14 15:22:49 by lelderbe          #+#    #+#              #
#    Updated: 2021/01/10 12:38:44 by lelderbe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= ft_printf.c parser.c utils.c \
			  process.c process_s.c process_p.c process_u.c process_c.c \
			  process_d.c process_x.c process_xx.c process_n.c process_o.c

HEADERS		= libftprintf.h

OBJS		= ${SRCS:.c=.o}

NAME		= libftprintf.a

LIBFT		= libft.a
LIBFT_DIR	= libft/

INCLUDES	= -I${LIBFT_DIR}

CC			= gcc

AR			= ar

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror

%.o:		%.c ${HEADERS}
			${CC} ${CFLAGS} ${INCLUDES} -c $< -o ${<:.c=.o}

all:		${NAME}

${NAME}:	${LIBFT_DIR}${LIBFT} ${OBJS}
			cp ${LIBFT_DIR}${LIBFT} ${NAME}
			${AR} rc ${NAME} ${OBJS}

${LIBFT_DIR}${LIBFT}:	${LIBFT_DIR}
			${MAKE} -C ${LIBFT_DIR} bonus

bonus:		${NAME}

clean:
			${RM} ${OBJS}
			${MAKE} -C ${LIBFT_DIR} clean

fclean:		clean
			${RM} ${NAME}
			${MAKE} -C ${LIBFT_DIR} fclean
#			cd libft && ${MAKE} fclean

re:			fclean all

.PHONY:		all clean fclean re
