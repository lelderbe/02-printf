/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 13:43:55 by lelderbe          #+#    #+#             */
/*   Updated: 2020/12/28 15:57:14 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

t_spec	*parse(const char **s, va_list *ap)
{
	t_spec		*result;
	const char	*ptr;
	int			i;

	ptr = *s;
	result = ft_calloc(1, sizeof(*result));
	if (!result)
		return (0);

	result->precision = -1;
	/*
	printf(" ----- elem: ------\n");
	printf("flags.left: %d\n", result->flags.left);
	printf("flags.zero: %d\n", result->flags.zero);
	printf("width: %lu\n", result->width);
	printf("precision: %lu\n", result->precision);
	printf("type: %c\n", result->type);
	printf("value.p: %td\n", result->value.p);
	printf("value.s: %td\n", result->value.s);
	printf("value.u: %ld\n", result->value.u);
	printf("value.x: %ld\n", result->value.x);
	printf("value.xx: %ld\n", result->value.xx);
	printf("value.c: %zu\n", result->value.c);
	printf("value.d: %ld\n", result->value.d);
	printf("value.i: %ld\n", result->value.i);
	printf("*txt: %p\n", result->txt);
	printf(" ----- ----- ------\n");
	*/
	//printf("sizeof spec: %ld\n", sizeof(result));
	//printf("sizeof spec: %ld\n", sizeof(*result));
	//result->txt = ft_strjoin(0,
	// flags
	while (*ptr == '0' || *ptr == '-')
	{
		if (*ptr == '0')// && !(result->flags.left))
			result->flags.zero = !result->flags.left;
			//result->flags.zero = 1;
		if (*ptr == '-')
		{
			result->flags.left = 1;
			result->flags.zero = 0;
		}
		ptr++;
	}
	/*
	if (result->flags.left)
		result->txt = ft_strjoin(result->txt, "-");
	else if (result->flags.zero)
		result->txt = ft_strjoin(result->txt, "0");
	*/
	// width
	if (*ptr == '*')
	{
		i = va_arg(*ap, int);
		if (i < 0)
		{
			result->flags.left = 1;
			//result->txt = ft_strjoin(0, "-");
			i = -i;
		}
		result->width = i;
		ptr++;
	}
	else
		while (ft_isdigit(*ptr))
		{
			result->width = result->width * 10 + (*ptr - '0');
			ptr++;
		}
	// precision
	if (*ptr == '.')
	{
		ptr++;
		result->precision = 0;
		if (*ptr == '*')
		{
			result->precision = va_arg(*ap, int);
			ptr++;
		}
		else
			while (ft_isdigit(*ptr))
			{
				result->precision = result->precision * 10 + (*ptr - '0');
				ptr++;
			}
	}
	// type
	if (*ptr == 'd')
	{
		result->type = 'd';
		result->value.d = va_arg(*ap, int);
	}
	else if (*ptr == 'i')
	{
		result->type = 'i';
		result->value.i = va_arg(*ap, int);
	}
	else if (*ptr == 'c')
	{
		result->type = 'c';
		result->value.c = va_arg(*ap, int);
	}
	else if (*ptr == 's')
	{
		result->type = 's';
		result->value.s = va_arg(*ap, char *);
	}
	else if (*ptr == 'u')
	{
		result->type = 'u';
		result->value.u = va_arg(*ap, int);
	}
	else if (*ptr == 'x')
	{
		result->type = 'x';
		result->value.x = va_arg(*ap, int);
	}
	else if (*ptr == 'X')
	{
		result->type = 'X';
		result->value.x = va_arg(*ap, int);
	}
	else if (*ptr == 'p')
	{
		result->type = 'p';
		//result->value.p = va_arg(*ap, unsigned long);
		//result->value.p = va_arg(*ap, size_t);
		result->value.p2 = va_arg(*ap, void*);
	}
	else if (*ptr == '%')
	{
		result->type = '%';
	}
	else
	{
		// add char
		return (0);
	}
	ptr++;
	*s = ptr;
	
	/*
	printf(" ----- elem: ------\n");
	printf("flags.left: %d\n", result->flags.left);
	printf("flags.zero: %d\n", result->flags.zero);
	printf("width: %d\n", result->width);
	printf("precision: %d\n", result->precision);
	printf("type: %c\n", result->type);
	printf("value.p: %p\n", result->value.p);
	printf("value.s: %p\n", result->value.s);
	printf("value.u: %ld\n", result->value.u);
	printf("value.x: %ld\n", result->value.x);
	printf("value.xx: %ld\n", result->value.xx);
	printf("value.c: %zu\n", result->value.c);
	printf("value.d: %d\n", result->value.d);
	printf("value.i: %d\n", result->value.i);
	printf("*txt: %p\n", result->txt);
	printf(" ----- ----- ------\n");
	*/
	//printf("value.d: %ld\n", result->value.d);
	//printf("value.i: %ld\n", result->value.i);
	return (result);
}
