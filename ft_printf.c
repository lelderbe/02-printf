/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 15:30:39 by lelderbe          #+#    #+#             */
/*   Updated: 2020/12/25 14:47:14 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int		ft_putnbr(ssize_t n)
{
	(void)n;
	return (0);
}

int		ft_putunbr(size_t n)
{
	(void)n;
	return (0);
}

int		print_spec(t_spec *spec)
{
	int	count;

	count = 0;
	if (spec->type == 'd')
		ft_putnbr_fd(spec->value.d, 1);
	if (spec->type == 'i')
		ft_putnbr_fd(spec->value.i, 1);
	if (spec->type == 'u')
		printf("%zu\n", spec->value.u);
		//ft_putnbr_fd(spec->value.u, 1);
	if (spec->type == 'c')
		ft_putchar_fd(spec->value.c, 1);
	if (spec->type == 's')
	{
		ft_putstr_fd((char *)spec->value.s, 1);
		count = ft_strlen((const char *)spec->value.s);
	}
	return (count);
}

int		ft_printf(const char *format, ...)
{
	va_list		ap;
	t_spec		*spec;
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
		spec = parse(&format, &ap);
		if (!spec)
		{
			ft_putchar_fd('%', 1);
			count++;
		}
		else
		{
			count += print_spec(spec);
			//printf("\ntype: %c\n", spec->type);
			//printf("\nval.d: %ld\n", spec->value.d);
			//ft_putnbr_fd(spec->value.d, 1);
			free(spec);
		}
		//format++;
	}
	va_end(ap);
	return (count);
}
