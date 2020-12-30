/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/30 15:24:54 by lelderbe          #+#    #+#             */
/*   Updated: 2020/12/30 15:42:10 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static size_t	get_length(size_t n)
{
	size_t	result;

	result = 1;
	while ((n = n / 10))
		result++;
	return (result);
}

static size_t	get_length_x(size_t n)
{
	size_t	result;

	result = 1;
	while ((n = n / 16))
		result++;
	return (result);
}

char		*ft_itoa_u(size_t n)
{
	char	*result;
	size_t	length;
	int		i;
	int		j;

	length = get_length(n);
	result = (char *)malloc(sizeof(*result) * (length + 1));
	if (!result)
		return (0);
	j = 0;
	i = length - 1;
	while (i >= j)
	{
		result[i] = '0' + (n % 10);
		n = n / 10;
		i--;
	}
	result[length] = 0;
	return (result);
}

char		*ft_itoa_x(size_t n)
{
	char	*result;
	size_t	length;
	int		i;
	int		j;
	char	hex[] = "0123456789abcdef";

	length = get_length_x(n);
	result = (char *)malloc(sizeof(*result) * (length + 1));
	if (!result)
		return (0);
	j = 0;
	i = length - 1;
	while (i >= j)
	{
		result[i] = hex[(n % 16)];
		n = n / 16;
		i--;
	}
	result[length] = 0;
	return (result);
}
