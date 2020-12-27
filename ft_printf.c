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
	{
		ft_putchar_fd(spec->value.c, 1);
		count++;
	}
	if (spec->type == 's')
	{
		ft_putstr_fd((char *)spec->value.s, 1);
		count = ft_strlen((const char *)spec->value.s);
	}
	return (count);
}


char	*get_c_result(t_spec *spec)
{
		char	*result;
		size_t	size;
		int		i;

		size = spec->width ? spec->width : 1;
		result = malloc(sizeof(*result) * (size + 1));
		if (!result)
			return (0);
		ft_memset(result, ' ', size);
		if (spec->flags.left)
			i = 0;
		else
			i = size - 1;
		result[i] = spec->value.c;
		result[size] = '\0';
		return (result);
}

char	*get_s_result(t_spec *spec)
{
		char	*result;
		int		size;
		int		i;

		size = ft_strlen(spec->value.s);
		size = spec->precision >= 0 && size > spec->precision ? spec->precision : size;
		size = spec->width && spec->width > size ? spec->width : size; 
		result = malloc(sizeof(*result) * (size + 1));
		if (!result)
			return (0);
		ft_memset(result, ' ', size);
		if (spec->flags.left)
			i = 0;
		else
		{
			if (size < (int) ft_strlen(spec->value.s))
				i = 0;
			else
				i = size - ft_strlen(spec->value.s);
		}
		while (*spec->value.s && i < size)
		{
			result[i] = *spec->value.s;
			i++;
			(spec->value.s)++;
		}
		result[size] = '\0';
		return (result);
}

char	*get_result(t_spec *spec)
{
	if (spec->type == 'c')
		return (get_c_result(spec));
	if (spec->type == 's')
		return (get_s_result(spec));
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
		spec = parse(&format, &ap);
		if (!spec)
		{
			ft_putchar_fd('%', 1);
			count++;
		}
		else
		{
			next = get_result(spec);
			count = count + ft_strlen(next);
			//count += print_spec(spec);
			//printf("\ntype: %c\n", spec->type);
			//printf("\nval.d: %ld\n", spec->value.d);
			//ft_putnbr_fd(spec->value.d, 1);
			ft_putstr_fd(next, 1);
			free(next);
			free(spec);
		}
		//format++;
	}
	va_end(ap);
	return (count);
}
