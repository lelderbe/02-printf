/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftprintf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 15:26:16 by lelderbe          #+#    #+#             */
/*   Updated: 2021/01/10 11:38:21 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# ifdef __linux__
#  define S_NULL_TEXT	"(null)"
# endif

# ifdef __APPLE__
#  define S_NULL_TEXT	"(null)"
# endif

# define DEBUG

# include "libft/libft.h"
# include <stdarg.h>
# include <stdio.h>

typedef struct				s_spec {
	struct {
		size_t	left : 1;
		size_t	zero : 1;
		size_t	plus : 1;
		size_t	space : 1;
		size_t	hash : 1;
	}						flags;
	ssize_t					width;
	int						precision;
	char					length;
	char					type;
	union {
		size_t				value;
		void				*p;
		char				*s;
		signed char			*hhn;
		short				*hn;
		int					*n;
		long				*ln;
		long long			*lln;
		unsigned char		hhu;
		unsigned short		hu;
		unsigned int		u;
		unsigned long		lu;
		unsigned long long	llu;
		unsigned int		x;
		unsigned int		o;
		unsigned char		c;
		int					d;
		int					i;
		short int			h;
		char				hh;
		long int			l;
		long long int		ll;
	}						value;
	const char				*ptr;
	va_list					*ap;
	char					*result;
	int						size;
	char					*prefix;
	char					*itoa;
	int						dsize;
	int						sign;
	int						written;
}							t_spec;

int							ft_printf(const char *format, ...);
int							parse(t_spec *e);
int							process_c(t_spec *e);
int							process_d(t_spec *e);
int							process_p(t_spec *e);
int							process_u(t_spec *e);
int							process_s(t_spec *e);
int							process_x(t_spec *e);
int							process_xx(t_spec *e);
int							process_n(t_spec *e);
int							process_o(t_spec *e);
void						fill_width2(t_spec *e);
void						fill_precision2(t_spec *e);
void						fill_data2(t_spec *e);
char						*ft_itoa_mod(long long int n);
char						*ft_itoa_u(size_t n, int base);
void						debug_print_e(t_spec *e);

#endif
