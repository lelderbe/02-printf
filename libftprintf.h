/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 15:26:16 by lelderbe          #+#    #+#             */
/*   Updated: 2020/12/25 14:20:44 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <stdio.h>

typedef struct		s_spec {
	struct {
		size_t	sign : 1;
		size_t	zero : 1;
	}				flags;
	size_t			width;
	size_t			precision;
	char			type;
	char			*buf;
	union {
		ptrdiff_t	p;
		ptrdiff_t	s;
		size_t		u;
		size_t		x;
		size_t		xx;
		size_t		c;
		ssize_t		d;
		ssize_t		i;
	}				value;
}					t_spec;

t_spec				*parse(const char **s, va_list *ap);

#endif
