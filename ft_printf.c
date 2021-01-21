/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 15:30:39 by lelderbe          #+#    #+#             */
/*   Updated: 2021/01/21 11:22:55 by lelderbe         ###   ########.fr       */
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
	return (0);
}

static void	freespec(t_spec *e)
{
	free(e->prefix);
	free(e->itoa);
	free(e->result);
}

static int	parse_and_print(t_spec *e)
{
	if (parse(e))
	{
		if (!get_result(e))
		{
			freespec(e);
			return (0);
		}
		write(1, e->result, e->size);
		e->written = e->written + e->size;
		freespec(e);
	}
	return (1);
}

static void	clear(t_spec *e)
{
	e->flags.left = 0;
	e->flags.zero = 0;
	e->flags.plus = 0;
	e->flags.space = 0;
	e->flags.hash = 0;
	e->width = 0;
	e->precision = -1;
	e->length = 0;
	e->type = 0;
	e->value.value = 0;
	e->result = 0;
	e->size = 0;
	e->prefix = 0;
	e->itoa = 0;
	e->dsize = 0;
	e->sign = 0;
}

int			ft_printf(const char *format, ...)
{
	t_spec		e;

	e.written = 0;
	e.ptr = format;
	va_start(e.ap, format);
	while (*e.ptr)
	{
		if (*e.ptr != '%')
		{
			write(1, e.ptr++, 1);
			e.written++;
			continue ;
		}
		e.ptr++;
		clear(&e);
		if (!parse_and_print(&e))
		{
			va_end(e.ap);
			return (-1);
		}
	}
	va_end(e.ap);
	return (e.written);
}
