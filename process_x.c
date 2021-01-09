/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 11:14:09 by lelderbe          #+#    #+#             */
/*   Updated: 2021/01/09 11:15:08 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	get_size(t_spec *e)
{
	int		size;

	size = ft_strlen(e->itoa);
	size = e->precision == 0 && e->value.x == 0 ? 0 : size;
	size = e->precision > size ? e->precision : size;
	if (e->flags.hash)
		size = size + ft_strlen(e->prefix);
	size = e->width > size ? e->width : size;
	return (size);
}

int			process_x(t_spec *e)
{
	e->prefix = ft_strdup("0x");
	e->itoa = ft_itoa_u(e->value.x, 16);
	if (!e->itoa)
		return (-1);
	if (e->flags.hash && e->value.x == 0)
		e->flags.hash = 0;
	e->sign = e->flags.hash;
	e->size = get_size(e);
	e->dsize = ft_strlen(e->itoa);
	e->dsize = e->precision == 0 && e->value.x == 0 ? 0 : e->dsize;
	e->result = malloc(sizeof(*e->result) * e->size);
	if (!e->result)
		return (-1);
	fill_width2(e);
	fill_precision2(e);
	fill_data2(e);
	return (e->size);
}
