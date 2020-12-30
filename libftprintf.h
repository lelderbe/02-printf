/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 15:26:16 by lelderbe          #+#    #+#             */
/*   Updated: 2020/12/30 15:28:49 by lelderbe         ###   ########.fr       */
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
		void		*p;
		char		*s;
		unsigned int u;
		unsigned int x;
		size_t		c;
		int			d;
		int			i;
	}				value;
	const char		*ptr;
}					t_spec;

t_spec				*parse(const char *s, va_list *ap);
char				*get_c_result(t_spec *spec);
char				*get_s_result(t_spec *spec);
char				*get_p_result(t_spec *spec);
char				*ft_itoa_u(size_t n);
char				*ft_itoa_x(size_t n);

#endif
