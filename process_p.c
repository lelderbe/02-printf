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

	size = ft_strlen(e->itoa) + ft_strlen(e->prefix);
	size = e->precision > size ? e->precision : size;
	size = e->width > size ? e->width : size;
	return (size);
}

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

static void	fill_precision(t_spec *e)
{
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
		//e->result[i] = e->prefix[0];
		e->sign = 0;
		i = i + ft_strlen(e->prefix);
	}
	ft_memset(e->result + i, '0', e->precision);
}

static void	fill_data(t_spec *e)
{
	int		i;

	if (e->flags.left)
	{
		i = 0;
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

int			get_p_result(t_spec *e)
{
	if (!e->value.p)
	{
		e->itoa = ft_strdup(P_NULL_TEXT);
		e->prefix = ft_strdup("");
		e->sign = 0;
		e->flags.zero = 0;
		e->precision = -1;
	}
	else
	{
		e->itoa = ft_itoa_x(e->value.padding);
		e->prefix = ft_strdup("0x");
		e->sign = 1;
	}
	e->size = get_size(e);
	e->dsize = ft_strlen(e->itoa);
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
