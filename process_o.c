/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_o.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 10:29:06 by lelderbe          #+#    #+#             */
/*   Updated: 2021/01/10 17:53:35 by lelderbe         ###   ########.fr       */
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
		return (ft_itoa_u_base(e->value.hu, 8));
	if (e->length == 'H')
		return (ft_itoa_u_base(e->value.hhu, 8));
	if (e->length == 'l')
		return (ft_itoa_u_base(e->value.lu, 8));
	if (e->length == 'L')
		return (ft_itoa_u_base(e->value.llu, 8));
	return (ft_itoa_u_base(e->value.o, 8));
}

int			process_o(t_spec *e)
{
	if (!(e->itoa = get_itoa(e)))
		return (-1);
	e->dsize = ft_strlen(e->itoa);
	e->dsize = e->precision == 0 && e->value.value == 0 ? 0 : e->dsize;
	if (!(e->prefix = ft_strdup("0")))
		return (-1);
	e->flags.plus = 0;
	e->flags.space = 0;
	if (e->flags.hash && !e->flags.zero)
	{
		if (e->precision < 0)
			e->precision = e->value.value ? e->dsize + 1 : e->precision;
		else
			e->precision = e->precision <= e->dsize ? e->dsize + 1 : e->precision;
	}
	e->flags.hash = 0;
	e->flags.zero = e->precision >= 0 ? 0 : e->flags.zero;
	e->sign = 0;
	e->size = get_size(e);
	if (!(e->result = malloc(sizeof(*e->result) * e->size)))
		return (-1);
	fill_width(e);
	fill_precision(e);
	fill_data(e);
	return (e->size);
}
