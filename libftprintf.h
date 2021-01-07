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

# ifdef __linux__
#  define P_NULL_TEXT	"(nil)"
#  define S_NULL_TEXT	"(null)"
# endif

# ifdef __APPLE__
#  define P_NULL_TEXT	"(null)"
#  define S_NULL_TEXT	"(null)"
# endif

//# define DEBUG

# include "libft/libft.h"
# include <stdarg.h>
# include <stdio.h>

typedef struct		s_spec {
	struct {
		size_t	left : 1;
		size_t	zero : 1;
		size_t	sign : 1;
		size_t	space : 1;
		size_t	hash : 1;
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
	char			*result;
	int				size;
	char			*prefix;
	char			*itoa;
	int				dsize;
	int				psize;
	int				count;
	int				sign;
}					t_spec;

t_spec				*parse(const char *s, va_list *ap);
int					get_c_result(t_spec *e);
int					get_d_result(t_spec *e);
int					get_x_result(t_spec *e);
int					get_p_result(t_spec *e);
int					get_u_result(t_spec *e);
int					get_s_result(t_spec *e);
char				*ft_itoa_mod(int n);
char				*ft_itoa_u(size_t n);
char				*ft_itoa_x(size_t n);
void				fill_width2(t_spec *e);
void				fill_precision2(t_spec *e);
void				fill_data2(t_spec *e);


#endif
