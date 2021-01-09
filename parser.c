/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 13:43:55 by lelderbe          #+#    #+#             */
/*   Updated: 2021/01/09 12:05:57 by lelderbe         ###   ########.fr       */
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

static void	get_width(t_spec *e)
{
	if (*e->ptr == '*')
	{
		e->width = va_arg(*e->ap, int);
		if (e->width < 0)
		{
			e->flags.left = 1;
			e->flags.zero = 0;
			e->width = -e->width;
		}
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

static void	get_precision(t_spec *e)
{
	int		sign;

	sign = 1;
	if (*e->ptr == '.')
	{
		e->ptr++;
		e->precision = 0;
		if (*e->ptr == '*')
		{
			e->precision = va_arg(*e->ap, int);
			e->ptr++;
		}
		else
		{
			if (*e->ptr == '-')
			{
				sign = -1;
				e->ptr++;
			}
			while (ft_isdigit(*e->ptr))
			{
				e->precision = e->precision * 10 + (*e->ptr - '0');
				e->ptr++;
			}
		}
	}
	e->precision = e->precision * sign;
}

static int	get_value(t_spec *e)
{
	e->type = *e->ptr;
	if (*e->ptr == 'd' || *e->ptr == 'i' || *e->ptr == 'u')
		e->value.value = va_arg(*e->ap, int);
	else if (*e->ptr == 'c')
		e->value.value = va_arg(*e->ap, int);
	else if (*e->ptr == 's')
		e->value.s = va_arg(*e->ap, char *);
	//else if (*e->ptr == 'u')
	//	e->value.u = va_arg(*e->ap, int);
	else if (*e->ptr == 'x')
		e->value.x = va_arg(*e->ap, int);
	else if (*e->ptr == 'X')
		e->value.x = va_arg(*e->ap, int);
	else if (*e->ptr == 'p')
		e->value.p = va_arg(*e->ap, void*);
	else if (*e->ptr == 'n')
		e->value.n = va_arg(*e->ap, int*);
	else if (*e->ptr == 'o')
		e->value.o = va_arg(*e->ap, int);
	else if (*e->ptr == '%')
		e->value.c = '%';
	else
		return (-1);
	e->ptr++;
	if (e->precision >= 0 && e->type != '%' && e->type != 'c' && e->type != 's')
	//if (e->precision >= 0 && e->type != '%')
		e->flags.zero = 0;
	return (1);
}

static void	print_e(t_spec *e)
{
	(void)e;
#ifdef DEBUG
	printf(" ----- elem: ------\n");
	printf("%30s %d\n", "flags.left: ", e->flags.left);
	printf("%30s %d\n", "flags.zero: ", e->flags.zero);
	printf("%30s %d\n", "flags.sign: ", e->flags.sign);
	printf("%30s %d\n", "flags.space: ", e->flags.space);
	printf("%30s %d\n", "flags.hash: ", e->flags.hash);
	printf("%30s\n", "-------------------------------------------");
	printf("%30s %ld\n", "int width: ", e->width);
	printf("%30s %d\n", "int precision: ", e->precision);
	printf("%30s %c\n", "char type: ", e->type);
	printf("%30s %lu\n", "size_t value.value: ", e->value.value);
	printf("%30s %p\n", "void *value.p: ", e->value.p);
	printf("%30s %p\n", "char *value.s: ", e->value.s);
	printf("%30s %u\n", "unsigned value.u: ", e->value.u);
	printf("%30s %u\n", "unsigned value.x: ", e->value.x);
	printf("%30s %d\n", "unsigned char value.c: ", e->value.c);
	printf("%30s %d\n", "int value.d: ", e->value.d);
	printf("%30s %d\n", "int value.i: ", e->value.i);
	printf("%30s\n", "-------------------------------------------");
	printf("%30s %s\n", "const char *ptr: ", e->ptr);
	printf("%30s %p\n", "va_list *ap: ", e->ap);
	printf("%30s %s\n", "char *result: ", e->result);
	printf("%30s %d\n", "int size: ", e->size);
	printf("%30s %s\n", "char *prefix: ", e->prefix);
	printf("%30s %s\n", "char *itoa: ", e->itoa);
	printf("%30s %d\n", "int dsize: ", e->dsize);
	printf("%30s %d\n", "int sign: ", e->sign);
	printf("%30s %d\n", "int written: ", e->written);
	printf("%30s\n", "-------------------------------------------");
#endif
}

int			parse(t_spec *e)
{
	//print_e(e);
	get_flags(e);
	get_width(e);
	get_precision(e);
	if (get_value(e) == -1)
		return (-1);
	print_e(e);
	return (1);
}
