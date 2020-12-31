/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_u.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 12:23:16 by lelderbe          #+#    #+#             */
/*   Updated: 2020/12/31 13:01:00 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	get_size(t_spec *e)
{
	int		size;
	char	*itoa;

	itoa = ft_itoa_u(e->value.u);
	size = ft_strlen(itoa);
	if (e->precision == 0 && e->value.u == 0)
		size =  0;
	size = e->precision > size ? e->precision : size;
	size = e->width > size ? e->width : size;
	free(itoa);
	return (size);
}

void	fill_width(char *result, int size, t_spec *e)
{
	ft_memset(result, ' ', size);
	if (e->flags.zero && e->precision < 0)
		ft_memset(result, '0', size);
}

void	fill_precision(char *result, int size, t_spec *e)
{
	if (e->precision < 0)
		return ;
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

	itoa = ft_itoa_u(e->value.u);
	ptr = itoa;
	i = size - ft_strlen(itoa);
	if (e->flags.left)
	{
		i = 0;
		if (e->precision > (int) ft_strlen(itoa))
			i = e->precision - ft_strlen(itoa);
	}
	while (*itoa)
	{
		if (e->precision == 0 && e->value.u == 0)
			break ;
		result[i] = *itoa;
		i++;
		itoa++;
	}
	free(ptr);
}

char	*get_u_result(t_spec *e)
{
	char	*result;
	int		size;
	//size_t	u;

	//itoa = 0;
	//if (spec->type == 'u')
		/*
	else if (spec->type == 'x')
		itoa = ft_itoa_x(e->value.x);
	else if (spec->type == 'X')
		itoa = ft_itoa_x(e->value.x);
		*/
	//printf("%s\n", itoa);
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
