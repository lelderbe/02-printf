# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/14 15:22:49 by lelderbe          #+#    #+#              #
#    Updated: 2021/01/08 15:33:29 by lelderbe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= ft_printf.c parser.c process.c utils.c process_s.c process_p.c process_u.c process_c.c process_d.c process_x.c process_xx.c process_n.c

#BONUS_SRCS	= 

HEADERS		= libftprintf.h

#ifdef BONUS
#	OBJS = ${COMMON_OBJS} ${BONUS_OBJS}
#else
#	OBJS = ${COMMON_OBJS}
#endif

OBJS		= ${SRCS:.c=.o}

#BONUS_OBJS	= ${BONUS_SRCS:.c=.o}

NAME		= libftprintf.a
LIBFT_NAME	= libft.a
LIBFT_DIR	= libft

CC			= gcc

AR			= ar

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror

%.o:		%.c ${HEADERS}
			#cd ${LIBFT_DIR} && ${MAKE} all
			${MAKE} -C ${LIBFT_DIR} all
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:		${NAME}

#${NAME}:	LIBFT ${OBJS}
${NAME}:	${OBJS}
			cp ${LIBFT_DIR}/${LIBFT_NAME} ${NAME}
			#${AR} rc ${NAME} ${OBJS} libft/*.o
			${AR} rc ${NAME} ${OBJS}

LIBFT:		RULE
			#cd libft && ${MAKE} all
			${MAKE} -C ${LIBFT_DIR} all

RULE:

#bonus:		
#			@$(MAKE) BONUS=1 ${NAME}

clean:
			${RM} ${OBJS}
			${RM} ${BONUS_OBJS}
			cd libft && ${MAKE} clean

fclean:		clean
			${RM} ${NAME}
			cd libft && ${MAKE} fclean

re:			fclean all

.PHONY:		all clean fclean re
