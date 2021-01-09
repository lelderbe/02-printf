/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_o.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 10:29:06 by lelderbe          #+#    #+#             */
/*   Updated: 2021/01/09 11:28:23 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	get_size(t_spec *e)
{
	int		size;

	size = ft_strlen(e->itoa);
	size = e->precision == 0 && e->value.o == 0 ? 0 : size;
	size = e->precision > size ? e->precision : size;
	if (e->flags.hash)
		size = size + ft_strlen(e->prefix);
	size = e->width > size ? e->width : size;
	return (size);
}

int			process_o(t_spec *e)
{
	e->prefix = ft_strdup("0");
	e->itoa = ft_itoa_u(e->value.o, 8);
	if (!e->itoa)
		return (-1);
	e->flags.sign = 0;
	e->flags.space = 0;
	e->size = get_size(e);
	e->dsize = ft_strlen(e->itoa);
	e->dsize = e->precision == 0 && e->value.x == 0 ? 0 : e->dsize;
	if (e->flags.hash)
		e->flags.hash = e->precision > e->dsize ? 0 : 1;
	e->sign = e->flags.hash;
	e->result = malloc(sizeof(*e->result) * e->size);
	if (!e->result)
		return (-1);
	fill_width2(e);
	fill_precision2(e);
	fill_data2(e);
	return (e->size);
}
