/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_s.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 15:46:13 by lelderbe          #+#    #+#             */
/*   Updated: 2020/12/29 15:58:10 by lelderbe         ###   ########.fr       */
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

char	*get_s_result(t_spec *spec)
{
	char	*result;
	int		size;
	int		i;

	size = ft_strlen(spec->value.s);
	size = spec->precision >= 0 && size > spec->precision ? spec->precision : size;
	size = spec->width && spec->width > size ? spec->width : size;
	result = malloc(sizeof(*result) * (size + 1));
	if (!result)
		return (0);
	fill_width(result, size, spec);
	fill_precision(result, size, spec);
	if (spec->flags.left)
		i = 0;
	else
		i = (size < (int) ft_strlen(spec->value.s)) ?  0 : size - ft_strlen(spec->value.s);
	while (*spec->value.s && i < size)
	{
		result[i] = *spec->value.s;
		i++;
		(spec->value.s)++;
	}
	result[size] = '\0';
	return (result);
}
