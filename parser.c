/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/25 13:43:55 by lelderbe          #+#    #+#             */
/*   Updated: 2020/12/25 14:58:24 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

t_spec	*parse(const char **s, va_list *ap)
{
	t_spec		*result;
	const char	*ptr;

	ptr = *s;
	result = ft_calloc(1, sizeof(*result));
	if (!result)
		return (0);

	printf("flags.sign: %d\n", result->flags.sign);
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
	//printf("sizeof spec: %ld\n", sizeof(result));
	//printf("sizeof spec: %ld\n", sizeof(*result));
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
		result->value.s = va_arg(*ap, ptrdiff_t);
	}
	else if (*ptr == 'u')
	{
		result->type = 'u';
		result->value.u = va_arg(*ap, int);
	}
	else
	{
		return (0);
	}
	ptr++;
	*s = ptr;

	printf("flags.sign: %d\n", result->flags.sign);
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
	//printf("value.d: %ld\n", result->value.d);
	//printf("value.i: %ld\n", result->value.i);
	return (result);
}
