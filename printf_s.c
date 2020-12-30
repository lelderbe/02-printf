/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_s.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 15:46:13 by lelderbe          #+#    #+#             */
/*   Updated: 2020/12/30 15:13:35 by lelderbe         ###   ########.fr       */
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

static int	get_size(t_spec *e)
{
	int		size;

	size = ft_strlen(e->value.s);
	size = e->precision >= 0 && size > e->precision ? e->precision : size;
	size = e->width && e->width > size ? e->width : size;
	return (size);
}

static void	fill_data(char *result, int size, t_spec *e)
{
	int		pos;
	int		i;
	int		max;

	if (e->precision >= 0)
	{
		max = e->precision > (int)ft_strlen(e->value.s) ?
			ft_strlen(e->value.s) : e->precision;
		i = 0;
		pos = e->flags.left ? 0 : size - max;
	}
	else
	{
		max = size;
		i = 0;
		pos = e->flags.left ? 0 : size - ft_strlen(e->value.s);
	}
	while (e->value.s[i] && i < max)
	{
		result[pos + i] = e->value.s[i];
		i++;
	}
}

char		*get_s_result(t_spec *e)
{
	char	*result;
	int		size;
	char	*np;

	np = 0;
	if (!e->value.s)
	{
		np = ft_strdup("(null)");
		e->value.s = np;
	}
	size = get_size(e);
	result = malloc(sizeof(*result) * (size + 1));
	if (!result)
		return (0);
	fill_width(result, size, e);
	fill_precision(result, size, e);
	fill_data(result, size, e);
	if (np)
	{
		free(np);
		e->value.s = 0;
	}
	result[size] = '\0';
	return (result);
}
