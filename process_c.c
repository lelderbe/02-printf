/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 14:13:04 by lelderbe          #+#    #+#             */
/*   Updated: 2021/01/04 16:07:05 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	get_size(t_spec *e)
{
	int		size;

	(void)e;
	size = e->width ? e->width : 1;
	return (size);
}

static void	fill_width(t_spec *e)
{
	if (e->flags.zero)
	{
		ft_memset(e->result, '0', e->size);
		if (e->sign)
		{
			ft_memcpy(e->result, e->prefix, ft_strlen(e->prefix));
			e->sign = 0;
		}
	}
	else
		ft_memset(e->result, ' ', e->size);
}

static void	fill_precision(t_spec *e)
{
	(void)e;
}

static void	fill_data(t_spec *e)
{
	int		pos;

	if (e->flags.left)
		pos = 0;
	else
		pos = e->size - 1;
	e->result[pos] = e->value.c;
}

int			get_c_result(t_spec *e)
{
	e->size = get_size(e);
	e->dsize = 1;
	e->result = malloc(sizeof(*e->result) * e->size);
	if (!e->result)
		return (-1);
	fill_width(e);
	fill_precision(e);
	fill_data(e);
	return (e->size);
}

