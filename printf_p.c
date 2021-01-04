/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 15:22:44 by lelderbe          #+#    #+#             */
/*   Updated: 2021/01/04 14:49:47 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	get_size(t_spec *e)
{
	int		size;

	size = ft_strlen(e->itoa) + 2;
	size = e->precision > size ? e->precision : size;
	size = e->width > size ? e->width : size;
	return (size);
}

static void	fill_width(char *result, int size, t_spec *e)
{
	ft_memset(result, ' ', size);
	if (e->flags.zero && e->precision < 0)
	{
		ft_memset(result, '0', size);
		ft_memset(result + 1, 'x', 1);
	}
	if (e->flags.left)
	{
		ft_memset(result, '0', 1);
		ft_memset(result + 1, 'x', 1);
	}
}

static void	fill_precision(char *result, int size, t_spec *e)
{
	if (e->precision < 0)
		return ;
	if (e->flags.left)
		ft_memset(result, ' ', e->precision);
	else
		ft_memset(result + (size - e->precision), ' ', e->precision);
}

static void	fill_data(char *result, int size, t_spec *e)
{
	int		i;
	char	*ptr;

	ptr = e->itoa;
	i = size - ft_strlen(ptr);
	if (e->flags.left)
	{
		i = 0 + 2;
		if (e->precision > (int)ft_strlen(ptr))
			i = e->precision - ft_strlen(ptr);
	}
	result[i - 2] = '0';
	result[i - 1] = 'x';
	while (*ptr)
	{
		result[i] = *ptr;
		i++;
		ptr++;
	}
}

char		*get_p_result(t_spec *e)
{
	char	*result;
	int		size;

	e->itoa = ft_itoa_x(e->value.c);
	size = get_size(e);
	result = malloc(sizeof(*result) * (size + 1));
	if (!result)
		return (0);
	fill_width(result, size, e);
	fill_precision(result, size, e);
	fill_data(result, size, e);
	result[size] = '\0';
	free(e->itoa);
	e->itoa = 0;
	return (result);
}
