/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 14:13:04 by lelderbe          #+#    #+#             */
/*   Updated: 2020/12/29 15:36:57 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	fill_width(char *result, int size, t_spec *spec)
{
	ft_memset(result, ' ', size);
	if (spec->flags.zero && spec->precision < 0)
		ft_memset(result, '0', size);
}

static void	fill_precision(char *result, int size, t_spec *spec)
{
	(void)result;
	(void)size;
	(void)spec;
}

char	*get_c_result(t_spec *spec)
{
	char	*result;
	size_t	size;
	int		i;

	size = spec->width ? spec->width : 1;
	result = malloc(sizeof(*result) * (size + 1));
	if (!result)
		return (0);
	fill_width(result, size, spec);
	fill_precision(result, size, spec);
	if (spec->flags.left)
		i = 0;
	else
		i = size - 1;
	result[i] = spec->value.c;
	result[size] = '\0';
	return (result);
}
