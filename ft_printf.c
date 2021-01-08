/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 15:30:39 by lelderbe          #+#    #+#             */
/*   Updated: 2021/01/08 15:55:47 by lelderbe         ###   ########.fr       */
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
	return (-1);
}

static void	freespec(t_spec *e)
{
	free(e->prefix);
	free(e->itoa);
	free(e);
}

static int	process(size_t *count, const char **format, va_list *ap)
{
	t_spec	*e;

	e = parse(*format, ap);
	if (!e)
	{
		ft_putchar_fd('%', 1);
		*count = *count + 1;
	}
	else
	{
		if (get_result(e) == -1)
		{
			freespec(e);
			return (-1);
		}
		write(1, e->result, e->size);
		*count = *count + e->size;
		*format = e->ptr;
		freespec(e);
	}
	return (1);
}

int			ft_printf(const char *format, ...)
{
	va_list		ap;
	size_t		count;

	count = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format != '%')
		{
			ft_putchar_fd(*format, 1);
			count++;
			format++;
			continue ;
		}
		format++;
		if (process(&count, &format, &ap) == -1)
		{
			va_end(ap);
			return (-1);
		}
	}
	va_end(ap);
	return (count);
}
