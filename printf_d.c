/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 13:02:18 by lelderbe          #+#    #+#             */
/*   Updated: 2020/12/31 13:22:04 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	get_size(t_spec *e)
{
	int		size;
	char	*itoa;

	itoa = ft_itoa(e->value.d);
	size = ft_strlen(itoa);
	if (e->precision == 0 && e->value.d == 0)
		size =  0;
	size = e->precision > size ? e->precision : size;
	size = e->width > size ? e->width : size;
	free(itoa);
	return (size);
}

static void	fill_width(char *result, int size, t_spec *e)
{
	ft_memset(result, ' ', size);
	if (e->flags.zero && e->precision < 0)
		ft_memset(result, '0', size);
}

static void	fill_precision(char *result, int size, t_spec *e)
{
	if (e->precision < 0)
		return ;
	if (e->value.d < 0)
	{
		result[0] = '-';
		result++;
	}
	if (e->flags.left)
		ft_memset(result, '0', e->precision);
	else
		ft_memset(result + (size - e->precision), '0', e->precision);
}

static void	fill_data(char *result, int size, t_spec *e)
{
	//int		pos;
	int		i;
	//int		max;
	char	*itoa;
	char	*ptr;

	itoa = ft_itoa(e->value.d);
	ptr = itoa;

	i = size - ft_strlen(itoa);
	if (e->flags.left)
	{
		i = 0;
		if (*itoa == '-')
		{
			result[0] = '-';
			i = size - ft_strlen(itoa) + 1;
			itoa++;
			if (e->precision >= 0)
				i = size - e->precision + (e->precision - ft_strlen(itoa)) + 1;
		}
	}
	while (*itoa)
	{
		if (e->precision == 0 && e->value.d == 0)
			break ;
		result[i] = *itoa;
		i++;
		itoa++;
	}
	free(ptr);
}

char	*get_d_result(t_spec *e)
{
	char	*result;
	int		size;

	size = get_size(e);
	//printf("size: %d\n", size);
	result = malloc(sizeof(*result) * (size + 1));
	if (!result)
		return (0);
	fill_width(result, size, e);
	fill_precision(result, size, e);
	fill_data(result, size, e);
	result[size] = '\0';
	return (result);
}
