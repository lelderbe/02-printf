/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 15:26:16 by lelderbe          #+#    #+#             */
/*   Updated: 2021/01/04 15:02:15 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

//# define DEBUG

# include "libft/libft.h"
# include <stdarg.h>
# include <stdio.h>

typedef struct		s_spec {
	struct {
		size_t	left : 1;
		size_t	zero : 1;
	}				flags;
	int				width;
	int				precision;
	char			type;
	union {
		size_t		padding;
		void		*p;
		char		*s;
		unsigned	u;
		unsigned	x;
		unsigned char	c;
		int			d;
		int			i;
	}				value;
	const char		*ptr;
	char			*itoa;
}					t_spec;

t_spec				*parse(const char *s, va_list *ap);
char				*get_c_result(t_spec *e);
char				*get_s_result(t_spec *e);
char				*get_p_result(t_spec *e);
char				*get_u_result(t_spec *e);
char				*get_d_result(t_spec *e);
char				*get_x_result(t_spec *e);
char				*ft_itoa_u(size_t n);
char				*ft_itoa_x(size_t n);

#endif
