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
/*
static int	str_toupper(char *s)
{
	int		count;

	count = 0;
	while(*s)
	{
		*s = ft_toupper(*s);
		s++;
		count++;
	}
	return (count);
}
*/
int			get_result(t_spec *e)
{
	if (e->type == 'c' || e->type == '%')
		return (get_c_result(e));
	if (e->type == 'p')
		return (get_p_result(e));
	if (e->type == 'd' || e->type == 'i')
		return (get_d_result(e));
	if (e->type == 'u')
		return (get_u_result(e));
	if (e->type == 'x')
		return (get_x_result(e));
	if (e->type == 'X')
		return (process_xx(e));
	/*
	{
		get_x_result(e);
		return (str_toupper(e->result));
	}
	*/
	if (e->type == 's')
		return (get_s_result(e));
	return (0);
}

static void	freespec(t_spec *e)
{
	(void)e;
	free(e->prefix);
	e->prefix = 0;
	free(e->itoa);
	e->itoa = 0;
	free(e);
	e = 0;
}

int			ft_printf(const char *format, ...)
{
	va_list		ap;
	t_spec		*e;
	size_t		count;
	int			result;

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
		e = parse(format, &ap);
		if (!e)
		{
			ft_putchar_fd('%', 1);
			count++;
		}
		else
		{
			result = get_result(e);
			if (result == -1)
			{
				freespec(e);
				va_end(ap);
				return (-1);
			}
			count = count + result;
			write(1, e->result, e->size);
			format = e->ptr;
			freespec(e);
		}
	}
	va_end(ap);
	return (count);
}
