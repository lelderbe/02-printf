/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/14 15:30:39 by lelderbe          #+#    #+#             */
/*   Updated: 2020/12/28 16:01:24 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

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

void	fill_d_width(char *result, int size, t_spec *spec)
{
	ft_memset(result, ' ', size);
	if (spec->flags.zero && spec->precision < 0)
		ft_memset(result, '0', size);
}

void	fill_d_precision(char *result, int size, t_spec *spec)
{
	if (spec->precision < 0)
		return ;
	if (spec->value.d < 0)
	{
		result[0] = '-';
		result++;
	}
	if (spec->flags.left)
		ft_memset(result, '0', spec->precision);
	else
		ft_memset(result + (size - spec->precision), '0', spec->precision);
}

char	*get_d_result(t_spec *spec)
{
	char	*result;
	int		size;
	int		i;
	char	*itoa;
	char	*ptr;

	itoa = ft_itoa(spec->value.d);
	ptr = itoa;
	//printf("itoa: %s\n", itoa);

	size = ft_strlen(itoa);
	size = spec->precision > size ? spec->precision : size;
	size = spec->width > size ? spec->width : size;
	//printf("size: %d\n", size);
	result = malloc(sizeof(*result) * (size + 1));
	if (!result)
		return (0);
	fill_d_width(result, size, spec);
	fill_d_precision(result, size, spec);
	i = size - ft_strlen(itoa);
	if (spec->flags.left)
	{
		i = 0;
		if (*itoa == '-')
		{
			result[0] = '-';
			i = size - ft_strlen(itoa) + 1;
			itoa++;
			if (spec->precision >= 0)
				i = size - spec->precision + (spec->precision - ft_strlen(itoa)) + 1;
		}
	}
	while (*itoa)
	{
		result[i] = *itoa;
		i++;
		itoa++;
	}
	result[size] = '\0';
	free(ptr);
	return (result);

}

static size_t	get_length(size_t n)
{
	size_t	result;

	result = 1;
	while ((n = n / 10))
		result++;
	return (result);
}

static size_t	get_length_x(size_t n)
{
	size_t	result;

	result = 1;
	while ((n = n / 16))
		result++;
	return (result);
}

char		*ft_itoa_u(size_t n)
{
	char	*result;
	size_t	length;
	int		i;
	int		j;

	length = get_length(n);
	result = (char *)malloc(sizeof(*result) * (length + 1));
	if (!result)
		return (0);
	j = 0;
	i = length - 1;
	while (i >= j)
	{
		result[i] = '0' + (n < 0 ? -(n % 10) : (n % 10));
		n = n / 10;
		i--;
	}
	result[length] = 0;
	return (result);
}

char		*ft_itoa_x(size_t n)
{
	char	*result;
	size_t	length;
	int		i;
	int		j;
	char	hex[] = "0123456789abcdef";

	length = get_length_x(n);
	result = (char *)malloc(sizeof(*result) * (length + 1));
	if (!result)
		return (0);
	j = 0;
	i = length - 1;
	while (i >= j)
	{
		result[i] = hex[(n % 16)];
		n = n / 16;
		i--;
	}
	result[length] = 0;
	return (result);
}

void	fill_u_precision(char *result, int size, t_spec *spec)
{
	if (spec->precision < 0)
		return ;
	if (spec->flags.left)
		ft_memset(result, '0', spec->precision);
	else
		ft_memset(result + (size - spec->precision), '0', spec->precision);
}

char	*get_u_result(t_spec *spec)
{
	char	*result;
	int		size;
	int		i;
	//size_t	u;
	char	*itoa;
	char	*ptr;

	itoa = 0;
	if (spec->type == 'u')
		itoa = ft_itoa_u(spec->value.u);
	else if (spec->type == 'x')
		itoa = ft_itoa_x(spec->value.x);
	else if (spec->type == 'X')
		itoa = ft_itoa_x(spec->value.x);
	//printf("%s\n", itoa);
	ptr = itoa;

	size = ft_strlen(itoa);
	size = spec->precision > size ? spec->precision : size;
	size = spec->width > size ? spec->width : size;
	//printf("size: %d\n", size);
	result = malloc(sizeof(*result) * (size + 1));
	if (!result)
		return (0);
	fill_d_width(result, size, spec);
	fill_u_precision(result, size, spec);
	//printf("%s\n", itoa);

	i = size - ft_strlen(itoa);
	if (spec->flags.left)
	{
		i = 0;
		if (spec->precision > (int) ft_strlen(itoa))
			i = spec->precision - ft_strlen(itoa);
	}
	while (*itoa)
	{
		result[i] = *itoa;
		i++;
		itoa++;
	}
	result[size] = '\0';
	free(ptr);
	return (result);
}

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

char	*get_result(t_spec *spec)
{
	if (spec->type == '%')
		return (ft_strdup("%"));
	if (spec->type == 'c')
		return (get_c_result(spec));
	if (spec->type == 's')
		return (get_s_result(spec));
	if (spec->type == 'd')
		return (get_d_result(spec));
	if (spec->type == 'u')
		return (get_u_result(spec));
	if (spec->type == 'x')
		return (get_u_result(spec));
	if (spec->type == 'X')
		return (str_toupper(get_u_result(spec)));
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
			ft_putstr_fd(next, 1);
			free(next);
			free(spec);
		}
		//format++;
	}
	va_end(ap);
	return (count);
}
