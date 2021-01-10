/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 12:10:13 by lelderbe          #+#    #+#             */
/*   Updated: 2021/01/10 12:50:34 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	get_size(t_spec *e)
{
	int		size;

	size = e->width ? e->width : 1;
	return (size);
}

int			process_c(t_spec *e)
{
	e->itoa = ft_strdup(" ");
	*e->itoa = e->value.c;
	e->dsize = 1;
	e->precision = -1;
	e->flags.plus = 0;
	e->flags.space = 0;
	e->flags.hash = 0;
	e->size = get_size(e);
	e->result = malloc(sizeof(*e->result) * e->size);
	if (!e->result)
		return (-1);
	fill_width(e);
	fill_precision(e);
	fill_data(e);
	return (e->size);
}
