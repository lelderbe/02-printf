/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 15:30:39 by lelderbe          #+#    #+#             */
/*   Updated: 2021/01/04 14:37:06 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static char	*str_toupper(char *s)
{
	char	*result;

	result = s;
	while(*s)
	{
		*s = ft_toupper(*s);
		s++;
	}
	return (result);
}

char	*get_result(t_spec *e)
{
	if (e->type == 'c' || e->type == '%')
		return (get_c_result(e));
	if (e->type == 's')
		return (get_s_result(e));
	if (e->type == 'd')
		return (get_d_result(e));
	if (e->type == 'u')
		return (get_u_result(e));
	if (e->type == 'x')
		return (get_x_result(e));
	if (e->type == 'X')
		return (str_toupper(get_x_result(e)));
	if (e->type == 'p')
		return (get_p_result(e));
	return (0);
}

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	t_spec		*spec;
	size_t		count;
	char		*next;

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
		spec = parse(format, &ap);
		if (!spec)
		{
			ft_putchar_fd('%', 1);
			count++;
		}
		else
		{
			next = get_result(spec);
			count = count + ft_strlen(next);
			ft_putstr_fd(next, 1);
			format = spec->ptr;
			free(next);
			//if (ft_strncmp(spec->value.s, "(null)", 6))
			//	free(spec->value.s);
			free(spec);
		}
		//format++;
	}
	va_end(ap);
	return (count);
}
