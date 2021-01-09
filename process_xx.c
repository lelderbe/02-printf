/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_xx.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 15:53:14 by lelderbe          #+#    #+#             */
/*   Updated: 2021/01/09 13:01:10 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	str_toupper(t_spec *e)
{
	int	i;

	i = 0;
	while (i < e->size)
	{
		e->result[i] = ft_toupper(e->result[i]);
		i++;
	}
}

int			process_xx(t_spec *e)
{
	if (process_x(e) == -1)
		return (-1);
	str_toupper(e);
	return (e->size);
}
