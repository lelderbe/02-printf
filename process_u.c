/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 10:31:34 by lelderbe          #+#    #+#             */
/*   Updated: 2021/01/09 11:50:20 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	get_size(t_spec *e)
{
	int		size;

	size = ft_strlen(e->itoa);
	if (e->precision == 0 && e->value.u == 0)
		size = 0;
	size = e->precision > size ? e->precision : size;
	size = e->width > size ? e->width : size;
	return (size);
}

int			process_u(t_spec *e)
{
	e->itoa = ft_itoa_u(e->value.u, 10);
	if (!e->itoa)
		return (-1);
	e->flags.hash = 0;
	e->flags.space = 0;
	e->size = get_size(e);
	e->dsize = ft_strlen(e->itoa);
	e->dsize = e->precision == 0 && e->value.u == 0 ? 0 : e->dsize;
	//if (e->value.u == 0 && e->precision == 0)
	//	e->dsize = 0;
	e->result = malloc(sizeof(*e->result) * e->size);
	if (!e->result)
		return (0);
	fill_width2(e);
	fill_precision2(e);
	fill_data2(e);
	return (e->size);
}
