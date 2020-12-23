# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/14 15:22:49 by lelderbe          #+#    #+#              #
#    Updated: 2020/12/23 16:47:13 by lelderbe         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		= ft_printf.c

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

CC			= gcc

AR			= ar

RM			= rm -f

CFLAGS		= -Wall -Wextra -Werror

%.o:		%.c ${HEADERS}
			cd libft && ${MAKE} all
			${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

all:		${NAME}

${NAME}:	LIBFT ${OBJS}
			cp libft/libft.a ${NAME}
			${AR} rc ${NAME} ${OBJS}

LIBFT:		RULE
			cd libft && ${MAKE} all

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
