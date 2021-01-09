/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 10:31:34 by lelderbe          #+#    #+#             */
/*   Updated: 2021/01/09 12:58:21 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	get_size(t_spec *e)
{
	int		size;

	size = ft_strlen(e->itoa);
	size = e->precision == 0 && e->value.u == 0 ? 0 : size;
	size = e->precision > size ? e->precision : size;
	size = e->width > size ? e->width : size;
	return (size);
}

int			process_u(t_spec *e)
{
	if (!(e->itoa = ft_itoa_u(e->value.value, 10)))
		return (-1);
	e->dsize = ft_strlen(e->itoa);
	e->dsize = e->precision == 0 && e->value.u == 0 ? 0 : e->dsize;
	e->flags.plus = 0;
	e->flags.space = 0;
	e->flags.hash = 0;
	e->flags.zero = e->precision >= 0 ? 0 : e->flags.zero;
	e->sign = 0;
	e->size = get_size(e);
	if (!(e->result = malloc(sizeof(*e->result) * e->size)))
		return (-1);
	fill_width2(e);
	fill_precision2(e);
	fill_data2(e);
	return (e->size);
}
