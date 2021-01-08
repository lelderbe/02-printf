
#include "libftprintf.h"

static int	get_size(t_spec *e)
{
	int		size;

	size = e->width ? e->width : 1;
	return (size);
}

int			process_c(t_spec *e)
{
	e->itoa = ft_strdup(" ");
	*e->itoa = e->value.c;
	e->dsize = 1;
	e->precision = -1;
	e->size = get_size(e);
	e->result = malloc(sizeof(*e->result) * e->size);
	if (!e->result)
		return (-1);
	fill_width2(e);
	fill_precision2(e);
	fill_data2(e);
	return (e->size);
}
