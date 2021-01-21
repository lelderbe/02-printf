/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 11:14:09 by lelderbe          #+#    #+#             */
/*   Updated: 2021/01/21 11:13:13 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	get_size(t_spec *e)
{
	int		size;

	size = ft_strlen(e->itoa);
	size = e->precision == 0 && e->value.value == 0 ? 0 : size;
	size = e->precision > size ? e->precision : size;
	if (e->sign)
		size = size + ft_strlen(e->prefix);
	size = e->width > size ? e->width : size;
	return (size);
}

static char	*get_itoa(t_spec *e)
{
	if (e->length == 'h')
		return (ft_itoa_u_base(e->value.hu, 16));
	if (e->length == 'H')
		return (ft_itoa_u_base(e->value.hhu, 16));
	if (e->length == 'l')
		return (ft_itoa_u_base(e->value.lu, 16));
	if (e->length == 'L')
		return (ft_itoa_u_base(e->value.llu, 16));
	return (ft_itoa_u_base(e->value.x, 16));
}

int			process_x(t_spec *e)
{
	if (!(e->itoa = get_itoa(e)))
		return (0);
	e->dsize = ft_strlen(e->itoa);
	e->dsize = e->precision == 0 && e->value.value == 0 ? 0 : e->dsize;
	if (!(e->prefix = ft_strdup("0x")))
		return (0);
	e->flags.plus = 0;
	e->flags.space = 0;
	if (e->flags.hash && e->value.value == 0)
		e->flags.hash = 0;
	e->flags.zero = e->precision >= 0 ? 0 : e->flags.zero;
	e->sign = e->flags.hash;
	e->size = get_size(e);
	if (!(e->result = malloc(sizeof(*e->result) * e->size)))
		return (0);
	fill_width(e);
	fill_precision(e);
	fill_data(e);
	return (1);
}
