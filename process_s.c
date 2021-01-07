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
	//size = e->precision > size ? e->precision : size;
	size = e->precision >= 0 && e->precision < size ? e->precision : size;
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
	(void)e;
	
	int		i;

	if (e->precision < 0 || e->precision <= e->dsize)
		return ;
	i = 0;
	if (!e->flags.left)
	{
		i = e->size - e->precision;// - e->sign;
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
		//if (e->precision > 0 && e->precision > e->dsize)
		//	i = i + e->precision - e->dsize;
	}
	else
	{
		i = e->size - e->dsize;// - e->sign;
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
int			get_s_result(t_spec *e)
{
	if (!e->value.s)
		e->itoa = ft_strdup(S_NULL_TEXT);
	else
		e->itoa = e->value.s;
	e->size = get_size(e);
	e->sign = 0;
	//e->prefix = ft_strdup("");
	e->dsize = ft_strlen(e->itoa);
	if (e->precision >= 0 && e->precision < e->dsize)
		e->dsize = e->precision;
	if (e->precision > e->dsize)
		e->precision = e->dsize;
	e->result = malloc(sizeof(*e->result) * e->size);
	if (!e->result)
		return (0);
	fill_width2(e);
	fill_precision2(e);
	fill_data2(e);
	return (e->size);
}
