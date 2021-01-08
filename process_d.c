
#include "libftprintf.h"

static int	get_size(t_spec *e)
{
	int		size;

	size = ft_strlen(e->itoa);
	if (e->precision == 0 && e->value.d == 0)
		size = 0;
	size = e->precision > size ? e->precision : size;
	if (e->sign)
		size++;
	//if (e->value.d < 0)
	//	size++;
	size = e->width > size ? e->width : size;
	return (size);
}

int			process_d(t_spec *e)
{
	e->prefix = ft_strdup("+");
	e->itoa = ft_itoa_mod(e->value.d);
	if (!e->itoa)
		return (-1);
	e->sign = e->flags.sign || e->flags.space;
	if (e->flags.space)
	{
		*e->prefix = ' ';
		e->flags.sign = 1;
	}
	if (e->value.d < 0)
	{
		e->flags.sign = 1;
		e->flags.space = 0;
		*e->prefix = '-';
		e->sign = 1;
	}
	e->size = get_size(e);
	e->dsize = ft_strlen(e->itoa);
	e->dsize = !e->precision && !e->value.d ? 0 : e->dsize;
	//if (e->value.d == 0 && e->precision == 0)
	//	e->dsize = 0;
	e->result = malloc(sizeof(*e->result) * e->size);
	if (!e->result)
		return (-1);
	fill_width2(e);
	fill_precision2(e);
	fill_data2(e);
	return (e->size);
}
