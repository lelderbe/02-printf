/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 15:30:39 by lelderbe          #+#    #+#             */
/*   Updated: 2021/01/09 10:39:50 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	get_result(t_spec *e)
{
	if (e->type == 'c' || e->type == '%')
		return (process_c(e));
	if (e->type == 'p')
		return (process_p(e));
	if (e->type == 'd' || e->type == 'i')
		return (process_d(e));
	if (e->type == 'u')
		return (process_u(e));
	if (e->type == 'x')
		return (process_x(e));
	if (e->type == 'X')
		return (process_xx(e));
	if (e->type == 's')
		return (process_s(e));
	if (e->type == 'n')
		return (process_n(e));
	if (e->type == 'o')
		return (process_o(e));
	return (-1);
}

static void	freespec(t_spec *e)
{
	free(e->prefix);
	free(e->itoa);
}

static int	process(t_spec *e, const char **format)
{
	if (parse(e) == -1)
	{
		ft_putchar_fd('%', 1);
		e->written++;
	}
	else
	{
		if (get_result(e) == -1)
		{
			freespec(e);
			return (-1);
		}
		write(1, e->result, e->size);
		e->written = e->written + e->size;
		*format = e->ptr;
		freespec(e);
	}
	return (1);
}

static void	init(t_spec *e)
{
	e->flags.left = 0;
	e->flags.zero = 0;
	e->flags.sign = 0;
	e->flags.space = 0;
	e->flags.hash = 0;
	e->width = 0;
	e->precision = -1;
	e->type = 0;
	e->value.value = 0;
	e->ptr = 0;
	e->result = 0;
	e->size = 0;
	e->prefix = 0;
	e->itoa = 0;
	e->dsize = 0;
	e->sign = 0;
}

int			ft_printf(const char *format, ...)
{
	va_list		ap;
	t_spec		e;

	va_start(ap, format);
	e.ap = &ap;
	e.written = 0;
	while (*format)
	{
		if (*format != '%')
		{
			ft_putchar_fd(*format, 1);
			e.written++;
			format++;
			continue ;
		}
		format++;
		init(&e);
		e.ptr = format;
		if (process(&e, &format) == -1)
		{
			va_end(ap);
			return (-1);
		}
	}
	va_end(ap);
	return (e.written);
}
