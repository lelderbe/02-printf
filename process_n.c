
#include "libftprintf.h"

int			process_n(t_spec *e)
{
	*e->value.n = e->written;
	return (0);
}
