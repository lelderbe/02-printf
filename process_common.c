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
/*
static int	get_size(t_spec *e)
{
	int		size;

	size = ft_strlen(e->itoa);
	if (e->precision == 0 && e->value.d == 0)
		size =  0;
	size = e->precision > size ? e->precision : size;
	if (e->value.d < 0)
		size++;
	size = e->width > size ? e->width : size;
	return (size);
}
*/

void	fill_width2(t_spec *e)
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

void	fill_precision2(t_spec *e)
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

void	fill_data2(t_spec *e)
{
	int		i;

	if (e->flags.left)
	{
		i = 0;
		if ((e->flags.sign || e->flags.space || e->flags.hash) && !e->sign)
			i = i + ft_strlen(e->prefix);
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
/*
int			get_d_result(t_spec *e)
{
	e->itoa = ft_itoa_mod(e->value.d);
	e->size = get_size(e);
	if (e->value.d < 0)
	{
		e->prefix = ft_strdup("-");
		e->sign = 1;
	}
	else
		e->prefix = ft_strdup("");
	e->dsize = ft_strlen(e->itoa);
	if (e->value.d == 0 && e->precision == 0)
		e->dsize = 0;
	e->result = malloc(sizeof(*e->result) * e->size);
	if (!e->result)
		return (0);
	fill_width(e);
	fill_precision(e);
	fill_data(e);
	free(e->itoa);
	e->itoa = 0;
	free(e->prefix);
	e->prefix = 0;
	return (e->size);
}
*/
