/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_d.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lelderbe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 13:02:18 by lelderbe          #+#    #+#             */
/*   Updated: 2021/01/04 13:59:58 by lelderbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

static int	get_size(t_spec *e)
{
	int		size;
	//char	*itoa;

	//itoa = ft_itoa(e->value.d);
	size = ft_strlen(e->itoa);
	if (e->precision == 0 && e->value.d == 0)
		size =  0;
	size = e->precision > size ? e->precision : size;
	//if (e->precision > 0 && e->value.d < 0)
	//	size
	size = e->width > size ? e->width : size;
	//free(itoa);
	return (size);
}

static void	fill_width(char *result, int size, t_spec *e)
{
	ft_memset(result, ' ', size);
	if (e->flags.zero && e->precision < 0)
		ft_memset(result, '0', size);
}

static void	fill_precision(char *result, int size, t_spec *e)
{
	if (e->precision < 0)
		return ;

	if (e->value.d < 0)
	{
		//result[0] = '-';
		//if (e->flags.left)
		//	result[0] = '-';
		//else
		//	ft_memset(result + (size - e->precision), '-', 1);

		result++;
	}
	
	if (e->flags.left)
		ft_memset(result, '0', e->precision);
	else
		ft_memset(result + (size - e->precision), '0', e->precision);
}

static void	fill_data(char *result, int size, t_spec *e)
{
	//int		pos;
	int		i;
	//int		max;
	//char	*itoa;
	char	*ptr;

	//itoa = ft_itoa(e->value.d);
	ptr = e->itoa;

	i = size - ft_strlen(ptr);

	if (e->precision >= 0)
	{
		if (e->flags.left)
		{
			//if (*ptr == '-')
			i = 0;
			//if (e->precision > 0 && e->precision > (int)ft_strlen(ptr))
			if (e->precision > (int)ft_strlen(ptr))
			{
				i = e->precision - ft_strlen(ptr);
			}
		}

	}
	else
	{
		if (e->flags.left)
		{
			i = 0;
		}
		if (*ptr == '-' && e->flags.zero)
		{
			result[0] = '-';
			ptr++;
			i++;
			//i = size - ft_strlen(ptr);
		}
	}

	/*
	if (e->flags.left)
	{
		i = 0;
		if (*ptr == '-')
		{
			result[0] = '-';
			i = size - ft_strlen(ptr) + 1;
			ptr++;
			if (e->precision >= 0)
				i = size - e->precision + (e->precision - ft_strlen(ptr)) + 1;
		}
	}
	*/
	while (*ptr)
	{
		if (e->precision == 0 && e->value.d == 0)
			break ;
		result[i] = *ptr;
		i++;
		ptr++;
	}
	//free(ptr);
}

/*
static void	fill_data2(char *result, int size, t_spec *e)
{
	// - or not
	if (e->value.d < 0 && e->flags.zero && e->precision < 0)
		ft_putchar_fd('-', 1);

}
*/

char	*get_d_result(t_spec *e)
{
	char	*result;
	int		size;

	e->itoa = ft_itoa(e->value.d);
	size = get_size(e);
	//printf("size: %d\n", size);
	result = malloc(sizeof(*result) * (size + 1));
	if (!result)
		return (0);
	fill_width(result, size, e);
	fill_precision(result, size, e);
	fill_data(result, size, e);
	result[size] = '\0';
	free(e->itoa);
	e->itoa = 0;
	return (result);
}
