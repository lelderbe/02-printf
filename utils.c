/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 15:24:54 by lelderbe          #+#    #+#             */
/*   Updated: 2021/01/10 12:55:05 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static size_t	get_length_int(long long int n)
{
	size_t	result;

	result = 1;
	while ((n = n / 10))
		result++;
	return (result);
}

static size_t	get_length_u_base(size_t n, int base)
{
	size_t	result;

	result = 1;
	while ((n = n / base))
		result++;
	return (result);
}

char			*ft_itoa_mod(long long int n)
{
	char	*result;
	size_t	length;
	int		i;
	int		j;

	length = get_length_int(n);
	result = malloc(sizeof(*result) * (length + 1));
	if (!result)
		return (0);
	j = 0;
	i = length - 1;
	while (i >= j)
	{
		result[i] = n < 0 ? '0' - (n % 10) : '0' + (n % 10);
		n = n / 10;
		i--;
	}
	result[length] = 0;
	return (result);
}

char			*ft_itoa_u_base(size_t n, int base)
{
	char		*result;
	size_t		length;
	int			i;
	int			j;
	const char	*hex = "0123456789abcdef";

	length = get_length_u_base(n, base);
	result = malloc(sizeof(*result) * (length + 1));
	if (!result)
		return (0);
	j = 0;
	i = length - 1;
	while (i >= j)
	{
		result[i] = hex[(n % base)];
		n = n / base;
		i--;
	}
	result[length] = 0;
	return (result);
}
