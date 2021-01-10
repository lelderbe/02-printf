/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_n.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/09 12:11:02 by lelderbe          #+#    #+#             */
/*   Updated: 2021/01/10 13:22:49 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

int			process_n(t_spec *e)
{
	if (e->length == 'h')
		*e->value.hn = e->written;
	else if (e->length == 'H')
		*e->value.hhn = e->written;
	else if (e->length == 'l')
		*e->value.ln = e->written;
	else if (e->length == 'L')
		*e->value.lln = e->written;
	else
		*e->value.n = e->written;
	return (0);
}
