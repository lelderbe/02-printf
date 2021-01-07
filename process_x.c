/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 13:02:18 by lelderbe          #+#    #+#             */
/*   Updated: 2021/01/04 13:59:58 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	get_size(t_spec *e)
{
	int		size;

	size = ft_strlen(e->itoa);
	if (e->precision == 0 && e->value.d == 0)
		size =  0;
	size = e->precision > size ? e->precision : size;
	if (e->flags.hash)
		size = size + ft_strlen(e->prefix);
	//if (e->value.d < 0)
	//	size++;
	size = e->width > size ? e->width : size;
	return (size);
}
/*
static void	fill_width(t_spec *e)
{
	if (e->flags.zero)
	{
		ft_memset(e->result, '0', e->size);
		if (e->sign)
		{
			ft_memcpy(e->result, e->prefix, ft_strlen(e->prefix));
			e->sign = 0;
		}
	}
	else
		ft_memset(e->result, ' ', e->size);
}
*/
/*
static void	fill_precision(t_spec *e)
{
	int		i;

	if (e->precision < 0 || e->precision <= e->dsize)
		return ;
	i = 0;
	if (!e->flags.left)
	{
		i = e->size - e->precision;
		if (e->sign)
			i = i - ft_strlen(e->prefix);
	}
	if (e->sign)
	{
		ft_memcpy(e->result + i, e->prefix, ft_strlen(e->prefix));
		e->sign = 0;
		i = i + ft_strlen(e->prefix);
	}
	ft_memset(e->result + i, '0', e->precision);
}
*/
/*
static void	fill_data(t_spec *e)
{
	int		i;

	if (e->flags.left)
	{
		i = 0;
		//if (e->value.d < 0 && !e->sign)
		//	i = i + ft_strlen(e->prefix);
		if (e->precision > 0 && e->precision > e->dsize)
			i = i + e->precision - e->dsize;
	}
	else
	{
		i = e->size - e->dsize;
		if (e->sign)
			i = i - ft_strlen(e->prefix);
	}
	if (e->sign)
	{
		ft_memcpy(e->result + i, e->prefix, ft_strlen(e->prefix));
		e->sign = 0;
		i = i + ft_strlen(e->prefix);
	}
	ft_memcpy(e->result + i, e->itoa, e->dsize);
}
*/
int			get_x_result(t_spec *e)
{
	e->itoa = ft_itoa_x(e->value.x);
	e->prefix = ft_strdup("0x");
	e->sign = e->flags.hash;
	e->size = get_size(e);
	//printf("hash: %d\n", e->flags.hash);
	e->dsize = ft_strlen(e->itoa);
	if (e->value.x == 0 && e->precision == 0)
		e->dsize = 0;
	e->result = malloc(sizeof(*e->result) * e->size);
	if (!e->result)
		return (-1);
	fill_width2(e);
	fill_precision2(e);
	fill_data2(e);
	return (e->size);
}
