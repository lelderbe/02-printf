
#include "libftprintf.h"

static int	get_size(t_spec *e)
{
	int		size;

	size = ft_strlen(e->itoa);
	if (e->precision == 0 && e->value.u == 0)
		size = 0;
	size = e->precision > size ? e->precision : size;
	size = e->width > size ? e->width : size;
	return (size);
}

int			process_u(t_spec *e)
{
	e->itoa = ft_itoa_u(e->value.u);
	if (!e->itoa)
		return (-1);
	e->size = get_size(e);
	e->dsize = ft_strlen(e->itoa);
	if (e->value.u == 0 && e->precision == 0)
		e->dsize = 0;
	e->result = malloc(sizeof(*e->result) * e->size);
	if (!e->result)
		return (0);
	fill_width2(e);
	fill_precision2(e);
	fill_data2(e);
	return (e->size);
}
