/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 12:11:35 by lelderbe          #+#    #+#             */
/*   Updated: 2021/01/10 17:44:56 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	get_size(t_spec *e)
{
	int		size;

	size = ft_strlen(e->itoa);
	size = e->precision >= 0 && e->precision < size ? e->precision : size;
	size = e->width > size ? e->width : size;
	return (size);
}

static char	*get_itoa(t_spec *e)
{
	char	*result;

	if (!e->value.s)
		return (ft_strdup(S_NULL_TEXT));
	if (e->precision >= 0)
	{
		if (!(result = malloc(sizeof(*result) * (e->precision + 1))))
			return (0);
		result[e->precision] = '\0';
		ft_memccpy(result, e->value.s, '\0', e->precision);
		return (result);
	}
	else
		return (ft_strdup(e->value.s));
}

int			process_s(t_spec *e)
{
	if (!(e->itoa = get_itoa(e)))
		return (-1);
	e->flags.plus = 0;
	e->flags.hash = 0;
	e->flags.space = 0;
	e->sign = 0;
	e->size = get_size(e);
	e->dsize = ft_strlen(e->itoa);
	e->dsize = e->precision >= 0 && e->precision < e->dsize ?
			e->precision : e->dsize;
	e->precision = e->precision > e->dsize ? e->dsize : e->precision;
	if (!(e->result = malloc(sizeof(*e->result) * e->size)))
		return (-1);
	fill_width(e);
	fill_precision(e);
	fill_data(e);
	return (e->size);
}
