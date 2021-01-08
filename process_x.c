
#include "libftprintf.h"

static int	get_size(t_spec *e)
{
	int		size;

	size = ft_strlen(e->itoa);
	size = !e->precision && !e->value.x ? 0 : size;
	//size = e->precision == 0 && e->value.x == 0 ? 0 : size;
	//if (e->precision == 0 && e->value.d == 0)
	//	size =  0;
	size = e->precision > size ? e->precision : size;
	//size = e->flags.hash ? size + ft_strlen(e->prefix) : size;
	if (e->flags.hash)
		size = size + ft_strlen(e->prefix);
	size = e->width > size ? e->width : size;
	return (size);
}

int			process_x(t_spec *e)
{
	e->prefix = ft_strdup("0x");
	e->itoa = ft_itoa_x(e->value.x);
	if (!e->itoa)
		return (-1);
	e->sign = e->flags.hash;
	e->size = get_size(e);
	e->dsize = ft_strlen(e->itoa);
	//e->dsize = e->precision == 0 && e->value.x == 0 ? 0 : e->dsize;
	e->dsize = !e->precision && !e->value.x ? 0 : e->dsize;
	//e->dsize = !(e->precision || e->value.x) ? 0 : e->dsize;
	//if (e->value.x == 0 && e->precision == 0)
	//	e->dsize = 0;
	e->result = malloc(sizeof(*e->result) * e->size);
	if (!e->result)
		return (-1);
	fill_width2(e);
	fill_precision2(e);
	fill_data2(e);
	return (e->size);
}
