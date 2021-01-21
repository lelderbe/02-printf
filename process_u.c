/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_u.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 10:31:34 by lelderbe          #+#    #+#             */
/*   Updated: 2021/01/21 11:12:55 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	get_size(t_spec *e)
{
	int		size;

	size = ft_strlen(e->itoa);
	size = e->precision == 0 && e->value.value == 0 ? 0 : size;
	size = e->precision > size ? e->precision : size;
	size = e->width > size ? e->width : size;
	return (size);
}

static char	*get_itoa(t_spec *e)
{
	if (e->length == 'h')
		return (ft_itoa_u_base(e->value.hu, 10));
	if (e->length == 'H')
		return (ft_itoa_u_base(e->value.hhu, 10));
	if (e->length == 'l')
		return (ft_itoa_u_base(e->value.lu, 10));
	if (e->length == 'L')
		return (ft_itoa_u_base(e->value.llu, 10));
	return (ft_itoa_u_base(e->value.u, 10));
}

int			process_u(t_spec *e)
{
	if (!(e->itoa = get_itoa(e)))
		return (0);
	e->dsize = ft_strlen(e->itoa);
	e->dsize = e->precision == 0 && e->value.value == 0 ? 0 : e->dsize;
	e->flags.plus = 0;
	e->flags.space = 0;
	e->flags.hash = 0;
	e->flags.zero = e->precision >= 0 ? 0 : e->flags.zero;
	e->sign = 0;
	e->size = get_size(e);
	if (!(e->result = malloc(sizeof(*e->result) * e->size)))
		return (0);
	fill_width(e);
	fill_precision(e);
	fill_data(e);
	return (1);
}
