/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 13:43:55 by lelderbe          #+#    #+#             */
/*   Updated: 2021/01/21 11:02:02 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	parse_flags(t_spec *e)
{
	while (*e->ptr == '0' || *e->ptr == '-' ||
			*e->ptr == '+' || *e->ptr == ' ' || *e->ptr == '#')
	{
		if (*e->ptr == '0')
			e->flags.zero = !e->flags.left;
		if (*e->ptr == ' ')
			e->flags.space = !e->flags.plus;
		if (*e->ptr == '#')
			e->flags.hash = 1;
		if (*e->ptr == '-')
		{
			e->flags.left = 1;
			e->flags.zero = 0;
		}
		if (*e->ptr == '+')
		{
			e->flags.plus = 1;
			e->flags.space = 0;
		}
		e->ptr++;
	}
}

static void	parse_width(t_spec *e)
{
	if (*e->ptr == '*')
	{
		e->width = va_arg(e->ap, int);
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

static void	parse_precision(t_spec *e)
{
	if (*e->ptr == '.')
	{
		e->ptr++;
		e->precision = 0;
		if (*e->ptr == '*')
		{
			e->precision = va_arg(e->ap, int);
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
	}
}

static int	parse_value(t_spec *e)
{
	e->type = *e->ptr;
	if (*e->ptr == 'd' || *e->ptr == 'i' || *e->ptr == 'u' ||
			*e->ptr == 'x' || *e->ptr == 'X' || *e->ptr == 'o' ||
			*e->ptr == 'c')
	{
		if (e->length == 'l')
			e->value.value = va_arg(e->ap, long int);
		else if (e->length == 'L')
			e->value.value = va_arg(e->ap, long long int);
		else
			e->value.value = va_arg(e->ap, int);
	}
	else if (*e->ptr == 's' || *e->ptr == 'p' || *e->ptr == 'n')
		e->value.p = va_arg(e->ap, void*);
	else if (*e->ptr == '%')
		e->value.c = '%';
	else
		return (0);
	e->ptr++;
	return (1);
}

int			parse(t_spec *e)
{
	parse_flags(e);
	parse_width(e);
	parse_precision(e);
	e->length = *e->ptr;
	if (*e->ptr == 'h' || *e->ptr == 'l')
	{
		e->ptr++;
		if (e->length == *e->ptr)
		{
			e->length = ft_toupper(e->length);
			e->ptr++;
		}
	}
	if (!parse_value(e))
		return (0);
	return (1);
}
