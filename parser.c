/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 13:43:55 by lelderbe          #+#    #+#             */
/*   Updated: 2020/12/30 12:18:55 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	get_flags(t_spec *e)
{
	while (*e->ptr == '0' || *e->ptr == '-' ||
			 *e->ptr == '+' || *e->ptr == ' ' || *e->ptr == '#')
	{
		if (*e->ptr == '0')
			e->flags.zero = !e->flags.left;
		if (*e->ptr == ' ')
			e->flags.space = !e->flags.sign;
		if (*e->ptr == '#')
			e->flags.hash = 1;
		if (*e->ptr == '-')
		{
			e->flags.left = 1;
			e->flags.zero = 0;
		}
		if (*e->ptr == '+')
		{
			e->flags.sign = 1;
			//e->flags.hash = 0;
			e->flags.space = 0;
		}
		e->ptr++;
	}
}

static void	get_width(va_list *ap, t_spec *e)
{
	int	i;

	if (*e->ptr == '*')
	{
		i = va_arg(*ap, int);
		if (i < 0)
		{
			e->flags.left = 1;
			e->flags.zero = 0;
			i = -i;
		}
		e->width = i;
		e->ptr++;
	}
	else
	{
		while (ft_isdigit(*e->ptr))
		{
			e->width = e->width * 10 + (*e->ptr - '0');
			e->ptr++;
		}
	}
}

static void	get_precision(va_list *ap, t_spec *e)
{
	if (*e->ptr == '.')
	{
		e->ptr++;
		e->precision = 0;
		if (*e->ptr == '*')
		{
			e->precision = va_arg(*ap, int);
			e->ptr++;
		}
		else
		{
			while (ft_isdigit(*e->ptr))
			{
				e->precision = e->precision * 10 + (*e->ptr - '0');
				e->ptr++;
			}
		}
		if (e->precision >= 0 || !e->value.p)
			e->flags.zero = 0;
	}
}

static int	get_value(va_list *ap, t_spec *e)
{
	e->type = *e->ptr;
	if (*e->ptr == 'd')
		e->value.d = va_arg(*ap, int);
	else if (*e->ptr == 'i')
		e->value.i = va_arg(*ap, int);
	else if (*e->ptr == 'c')
		e->value.c = va_arg(*ap, int);
	else if (*e->ptr == 's')
		e->value.s = va_arg(*ap, char *);
	else if (*e->ptr == 'u')
		e->value.u = va_arg(*ap, int);
	else if (*e->ptr == 'x')
		e->value.x = va_arg(*ap, int);
	else if (*e->ptr == 'X')
		e->value.x = va_arg(*ap, int);
	else if (*e->ptr == 'p')
		e->value.p = va_arg(*ap, void*);
	else if (*e->ptr == '%')
		e->value.c = '%';//va_arg(*ap, int);
	else
		return (0);
	e->ptr++;
	return (1);
}

static void	print_e(t_spec *e)
{
	(void)e;
#ifdef DEBUG
	printf(" ----- elem: ------\n");
	printf("flags.left: %d\n", e->flags.left);
	printf("flags.zero: %d\n", e->flags.zero);
	printf("width: %d\n", e->width);
	printf("precision: %d\n", e->precision);
	printf("type: %c\n", e->type);
	printf("value.p: %p\n", e->value.p);
	printf("value.s: %p\n", e->value.s);
	printf("value.u: %u\n", e->value.u);
	printf("value.x: %u\n", e->value.x);
	printf("value.c: %zu\n", e->value.c);
	printf("value.d: %d\n", e->value.d);
	printf("value.i: %d\n", e->value.i);
	printf("*ptr: %s\n", e->ptr);
	printf(" ----- ----- ------\n");
#endif
}

t_spec	*parse(const char *s, va_list *ap)
{
	t_spec		*e;

	e = ft_calloc(1, sizeof(*e));
	if (!e)
		return (0);
	e->precision = -1;
	e->ptr = s;
	print_e(e);
	get_flags(e);
	get_width(ap, e);
	get_precision(ap, e);
	if (!get_value(ap, e))
		return (0);
	print_e(e);
	return (e);
}
