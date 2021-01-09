/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_n.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 12:11:02 by lelderbe          #+#    #+#             */
/*   Updated: 2021/01/09 12:11:06 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			process_n(t_spec *e)
{
	if (e->length == 'h')
		*e->value.nh = e->written;
	if (e->length == 'H')
		*e->value.nhh = e->written;
	if (e->length == 'l')
		*e->value.nl = e->written;
	if (e->length == 'L')
		*e->value.nll = e->written;
	*e->value.n = e->written;
	return (0);
}
