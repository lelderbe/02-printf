/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 14:13:04 by lelderbe          #+#    #+#             */
/*   Updated: 2021/01/04 16:07:05 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	fill_width(char *result, int size, t_spec *e)
{
	ft_memset(result, ' ', size);
	if (e->flags.zero && e->precision < 0)
		ft_memset(result, '0', size);
}

static void	fill_precision(char *result, int size, t_spec *e)
{
	(void)result;
	(void)size;
	(void)e;
}

static void	fill_data(char *result, int size, t_spec *e)
{
	int		pos;

	if (e->flags.left)
		pos = 0;
	else
		pos = size - 1;
	result[pos] = e->value.c;
}

static int	get_size(t_spec *e)
{
	int		size;

	(void)e;
	size = e->width ? e->width : 1;
	return (size);
}

static int	print_width(t_spec *e)
{
	int	count;
	int	i;

	count = 0;
	i = e->flags.left ? 0 : 1;
	while (e->width - i)
	{
		if (e->flags.zero)
			write(1, '0', 1);
		else 
			write(1, ' ', 1);
		e->width -= 1;
		count++;
	}
	return (count);
}

static int	print(t_spec *e)
{
	int	count;

	count = 0;
	// no sign
	// width
	if (e->flags.left)
	{
		write(1, (unsigned char)e->value.c, 1);
		count++;
		e->width -= 1;
	}
	count += print_width(e);
	if (!e->flags.left)
	{
		write(1, (unsigned char)e->value.c, 1);
		count++;
		e->width -= 1;
	}

	return (count);
}

char		*get_c_result(t_spec *e)
{
	char	*result;
	size_t	size;

	size = get_size(e);
	result = malloc(sizeof(*result) * (size + 1));
	if (!result)
		return (0);
	fill_width(result, size, e);
	fill_precision(result, size, e);
	fill_data(result, size, e);
	result[size] = '\0';
	return (result);
}
