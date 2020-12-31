/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_p.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 15:22:44 by lelderbe          #+#    #+#             */
/*   Updated: 2020/12/31 14:11:20 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	get_size(t_spec *e)
{
	int		size;
	char	*itoa;

	itoa = ft_itoa_x(e->value.c);
	size = ft_strlen(itoa) + 2;
	size = e->precision > size ? e->precision : size;
	size = e->width > size ? e->width : size;
	free(itoa);
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
	//int		pos;
	int		i;
	//int		max;
	char	*itoa;
	char	*ptr;

	itoa = ft_itoa_x(e->value.c);
	ptr = itoa;
	i = size - ft_strlen(itoa);
	if (e->flags.left)
	{
		i = 0 + 2;
		if (e->precision > (int) ft_strlen(itoa))
			i = e->precision - ft_strlen(itoa);
	}
	while (*itoa)
	{
		result[i] = *itoa;
		i++;
		itoa++;
	}
	free(ptr);
	/*
	if (e->precision >= 0)
	{
		max = e->precision > (int)ft_strlen(e->value.s) ?
			ft_strlen(e->value.s) : e->precision;
		i = 0;
		pos = e->flags.left ? 0 : size - max;
	}
	else
	{
		max = size;
		i = 0;
		pos = e->flags.left ? 0 : size - ft_strlen(e->value.s);
	}
	while (e->value.s[i] && i < max)
	{
		result[pos + i] = e->value.s[i];
		i++;
	}
	*/
}

char	*get_p_result(t_spec *e)
{
	char	*result;
	int		size;

	//itoa = ft_strjoin("0x", itoa);
	//free(ptr);
	//ptr = itoa;
	//printf("%s\n", itoa);
	//printf("size: %d\n", size);
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
