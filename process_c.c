
#include "libftprintf.h"

static int	get_size(t_spec *e)
{
	int		size;

	(void)e;
	size = e->width ? e->width : 1;
	return (size);
}
/*
static void	fill_width(t_spec *e)
{
	if (e->flags.zero)
	{
		ft_memset(e->result, '0', e->size);
		if (e->sign)
		{
			ft_memcpy(e->result, e->prefix, ft_strlen(e->prefix));
			e->sign = 0;
		}
	}
	else
		ft_memset(e->result, ' ', e->size);
}
*/
/*
static void	fill_precision(t_spec *e)
{
	(void)e;
}
*/
/*
static void	fill_data(t_spec *e)
{
	int		i;

	if (e->flags.left)
		i = 0;
	else
		i = e->size - e->dsize;
	e->result[i] = e->value.c;
}
*/
int			get_c_result(t_spec *e)
{
	e->size = get_size(e);
	e->dsize = 1;
	e->itoa = ft_strdup(" ");
	*e->itoa = e->value.c;
	e->precision = -1;
	e->result = malloc(sizeof(*e->result) * e->size);
	if (!e->result)
		return (-1);
	fill_width2(e);
	fill_precision2(e);
	fill_data2(e);
	return (e->size);
}

