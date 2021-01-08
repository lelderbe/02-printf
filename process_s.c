
#include "libftprintf.h"

static int	get_size(t_spec *e)
{
	int		size;

	size = ft_strlen(e->itoa);
	//size = e->precision > size ? e->precision : size;
	size = e->precision >= 0 && e->precision < size ? e->precision : size;
	size = e->width > size ? e->width : size;
	return (size);
}

int			process_s(t_spec *e)
{
	if (!e->value.s)
		e->itoa = ft_strdup(S_NULL_TEXT);
	else
		e->itoa = ft_strdup(e->value.s);
	if (!e->itoa)
		return (-1);
	//e->flags.sign = 0;
	//e->flags.hash = 0;
	//e->flags.space = 0;
	e->sign = 0;
	e->size = get_size(e);
	e->dsize = ft_strlen(e->itoa);
	e->dsize = e->precision >= 0 && e->precision < e->dsize ? e->precision : e->dsize;
	//if (e->precision >= 0 && e->precision < e->dsize)
	//	e->dsize = e->precision;
	e->precision = e->precision > e->dsize ? e->dsize : e->precision;
	//if (e->precision > e->dsize)
	//	e->precision = e->dsize;
	e->result = malloc(sizeof(*e->result) * e->size);
	if (!e->result)
		return (-1);
	fill_width2(e);
	fill_precision2(e);
	fill_data2(e);
	return (e->size);
}
