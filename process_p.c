
#include "libftprintf.h"

static int	get_size(t_spec *e)
{
	int		size;

	size = ft_strlen(e->itoa);
	size = e->precision == 0 && e->value.p == 0 ? 0 : size;
	//if (e->precision == 0 && e->value.p == 0)
	//	size = 0;
	size = e->precision > size ? e->precision : size;
	size = size + ft_strlen(e->prefix);
	size = e->width > size ? e->width : size;
	return (size);
}

int			process_p(t_spec *e)
{
	#if defined(__linux__)
	if (!e->value.p)
	{
		e->prefix = ft_strdup("");
		e->itoa = ft_strdup(P_NULL_TEXT);
		e->sign = 0;
		e->flags.zero = 0;
		e->precision = -1;
	}
	else
	#endif
	#if defined(__linux) || defined(__APPLE__)
	{
		e->prefix = ft_strdup("0x");
		e->itoa = ft_itoa_x(e->value.value);
		if (!e->itoa)
			return (-1);
		e->sign = 1;
	}
	#endif
	e->size = get_size(e);
	e->dsize = ft_strlen(e->itoa);
	e->dsize = e->precision == 0 && e->value.p == 0 ? 0 : e->dsize;
	//if (e->value.p == 0 && e->precision == 0)
	//	e->dsize = 0;
	e->result = malloc(sizeof(*e->result) * e->size);
	if (!e->result)
		return (-1);
	fill_width2(e);
	fill_precision2(e);
	fill_data2(e);
	return (e->size);
}
