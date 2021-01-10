/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 12:10:33 by lelderbe          #+#    #+#             */
/*   Updated: 2021/01/10 13:19:17 by lelderbe         ###   ########.fr       */
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
		size++;
	size = e->width > size ? e->width : size;
	return (size);
}

static char	*get_itoa(t_spec *e)
{
	if (e->length == 'h')
		return (ft_itoa_mod(e->value.h));
	if (e->length == 'H')
		return (ft_itoa_mod(e->value.hh));
	if (e->length == 'l')
		return (ft_itoa_mod(e->value.l));
	if (e->length == 'L')
		return (ft_itoa_mod(e->value.ll));
	return (ft_itoa_mod(e->value.d));
}

int			process_d(t_spec *e)
{
	if (!(e->itoa = get_itoa(e)))
		return (-1);
	e->dsize = ft_strlen(e->itoa);
	e->dsize = e->precision == 0 && e->value.value == 0 ? 0 : e->dsize;
	e->prefix = ft_strdup("+");
	e->flags.hash = 0;
	e->flags.zero = e->precision >= 0 ? 0 : e->flags.zero;
	if (e->flags.space)
		*e->prefix = ' ';
	if (e->value.ll < 0)
	{
		*e->prefix = '-';
		e->flags.plus = 1;
		e->flags.space = 0;
	}
	e->sign = e->flags.plus || e->flags.space;
	e->size = get_size(e);
	if (!(e->result = malloc(sizeof(*e->result) * e->size)))
		return (-1);
	fill_width(e);
	fill_precision(e);
	fill_data(e);
	return (e->size);
}
