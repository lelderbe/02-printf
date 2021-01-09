/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_o.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 10:29:06 by lelderbe          #+#    #+#             */
/*   Updated: 2021/01/09 12:46:20 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	get_size(t_spec *e)
{
	int		size;

	size = ft_strlen(e->itoa);
	size = e->precision == 0 && e->value.o == 0 ? 0 : size;
	size = e->precision > size ? e->precision : size;
	if (e->sign)
		size = size + ft_strlen(e->prefix);
	size = e->width > size ? e->width : size;
	return (size);
}

int			process_o(t_spec *e)
{
	if (!(e->itoa = ft_itoa_u(e->value.o, 8)))
		return (-1);
	e->dsize = ft_strlen(e->itoa);
	e->dsize = e->precision == 0 && e->value.o == 0 ? 0 : e->dsize;
	e->prefix = ft_strdup("0");
	e->flags.plus = 0;
	e->flags.space = 0;
	if (e->flags.hash && !e->flags.zero)
	{
		if (e->precision < 0)
			e->precision = e->value.o ? e->dsize + 1 : e->precision;
		else
			e->precision = e->precision <= e->dsize ?
									e->dsize + 1 : e->precision;
	}
	e->flags.hash = 0;
	e->flags.zero = e->precision >= 0 ? 0 : e->flags.zero;
	e->sign = e->flags.hash || e->flags.plus || e->flags.space;
	e->size = get_size(e);
	if (!(e->result = malloc(sizeof(*e->result) * e->size)))
		return (-1);
	fill_width2(e);
	fill_precision2(e);
	fill_data2(e);
	return (e->size);
}
