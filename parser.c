#include "libftprintf.h"

t_spec	*parse(const char **s, va_list *ap)
{
	t_spec	*result;

	result = ft_calloc(1, sizeof(*result));
	if (!result)
		return (0);

	printf("flags.sign: %u\n", result->flags.sign);
	printf("flags.zero: %u\n", result->flags.zero);
	printf("width: %lu\n", result->width);
	printf("precision: %lu\n", result->precision);
	printf("type: %d\n", result->type);
	printf("buf: %p\n", result->buf);
	printf("value.d: %ld\n", result->value.d);
	printf("value.i: %ld\n", result->value.i);
	//printf("sizeof spec: %ld\n", sizeof(result));
	//printf("sizeof spec: %ld\n", sizeof(*result));

	if (**s == 'd')
	{
		result->type = 'd';
		result->value.d = va_arg(*ap, int);
	}
	(*s)++;

	printf("value.d: %ld\n", result->value.d);
	printf("value.i: %ld\n", result->value.i);
	return (result);
}
