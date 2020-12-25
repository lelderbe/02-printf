/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 15:30:39 by lelderbe          #+#    #+#             */
/*   Updated: 2020/12/24 11:54:17 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	//int			i;
	//char		c;
	//char		*s;
	//unsigned	u;
	t_spec		*spec;

	va_start(ap, format);
	while (*format)
	{
		if (*format != '%')
		{
			ft_putchar_fd(*format, 1);
			format++;
			continue ;
		}
		format++;
		spec = parse(&format, &ap);
		//printf("\ntype: %c\n", spec->type);
		//printf("\nval.d: %ld\n", spec->value.d);
		ft_putnbr_fd(spec->value.d, 1);
		free(spec);
		/*
		format++;
		if (*format == 'c')
		{
			c = va_arg(ap, int);
			ft_putchar_fd(c, 1);
		}
		else if (*format == 's')
		{
			s = va_arg(ap, char *);
			ft_putstr_fd(s, 1);
		}
		else if (*format == 'd' || *format == 'i')
		{
			i = va_arg(ap, int);
			ft_putnbr_fd(i, 1);
		}
		else if (*format == 'u')
		{
			u = va_arg(ap, unsigned);
			ft_putnbr_fd(u, 1);
		}
		else if (*format == '%')
		{
			ft_putchar_fd(*format, 1);
		}
		*/
		//format++;
	}
	va_end(ap);
	return (0);
}
