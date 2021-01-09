/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 12:10:33 by lelderbe          #+#    #+#             */
/*   Updated: 2021/01/09 12:10:52 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	get_size(t_spec *e)
{
	int		size;

	size = ft_strlen(e->itoa);
	size = e->precision == 0 && e->value.d == 0 ? 0 : size;
	size = e->precision > size ? e->precision : size;
	if (e->sign)
		size++;
	size = e->width > size ? e->width : size;
	return (size);
}

int			process_d(t_spec *e)
{
	e->prefix = ft_strdup("+");
	e->itoa = ft_itoa_mod(e->value.d);
	if (!e->itoa)
		return (-1);
	//if (e->flags.space)
	//	e->flags.space = !e->flags.left;
	//e->flags.space = e->flags.space ? !e->flags.left : e->flags.space;
	e->flags.hash = 0;
	e->sign = e->flags.sign || e->flags.space;
	if (e->precision >= 0)
		e->flags.zero = 0;
	if (e->flags.space)
	{
		*e->prefix = ' ';
		e->flags.sign = 1;
	}
	if (e->value.d < 0)
	{
		e->flags.sign = 1;
		e->flags.space = 0;
		*e->prefix = '-';
		e->sign = 1;
	}
	e->size = get_size(e);
	e->dsize = ft_strlen(e->itoa);
	e->dsize = e->precision == 0 && e->value.d == 0 ? 0 : e->dsize;
	e->result = malloc(sizeof(*e->result) * e->size);
	if (!e->result)
		return (-1);
	fill_width2(e);
	fill_precision2(e);
	fill_data2(e);
	return (e->size);
}
