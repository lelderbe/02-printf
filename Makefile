# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/14 15:22:49 by lelderbe          #+#    #+#              #
#    Updated: 2020/12/30 15:26:00 by lelderbe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= ft_printf.c printf_utils.c parser.c printf_c.c printf_s.c printf_p.c

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
