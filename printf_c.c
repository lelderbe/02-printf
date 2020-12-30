/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_c.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 14:13:04 by lelderbe          #+#    #+#             */
/*   Updated: 2020/12/30 15:19:15 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static void	fill_width(char *result, int size, t_spec *e)
{
	ft_memset(result, ' ', size);
	if (e->flags.zero && e->precision < 0)
		ft_memset(result, '0', size);
}

static void	fill_precision(char *result, int size, t_spec *e)
{
	(void)result;
	(void)size;
	(void)e;
}

static void	fill_data(char *result, int size, t_spec *e)
{
	int		pos;

	if (e->flags.left)
		pos = 0;
	else
		pos = size - 1;
	result[pos] = e->value.c;
}

static int	get_size(t_spec *e)
{
	int		size;

	(void)e;
	size = e->width ? e->width : 1;
	return (size);
}

char		*get_c_result(t_spec *e)
{
	char	*result;
	size_t	size;

	size = get_size(e);
	result = malloc(sizeof(*result) * (size + 1));
	if (!result)
		return (0);
	fill_width(result, size, e);
	fill_precision(result, size, e);
	fill_data(result, size, e);
	result[size] = '\0';
	return (result);
}
