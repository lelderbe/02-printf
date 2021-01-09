
#include "libftprintf.h"

void	debug_print_e(t_spec *e)
{
	(void)e;
#ifdef DEBUG
	printf(" ----- elem: ------\n");
	printf("%30s %d\n", "flags.left: ", e->flags.left);
	printf("%30s %d\n", "flags.zero: ", e->flags.zero);
	printf("%30s %d\n", "flags.plus: ", e->flags.plus);
	printf("%30s %d\n", "flags.space: ", e->flags.space);
	printf("%30s %d\n", "flags.hash: ", e->flags.hash);
	printf("%30s\n", "-------------------------------------------");
	printf("%30s %ld\n", "int width: ", e->width);
	printf("%30s %d\n", "int precision: ", e->precision);
	printf("%30s %c\n", "char length: ", e->length);
	printf("%30s %c\n", "char type: ", e->type);
	printf("%30s %lu\n", "size_t value.value: ", e->value.value);
	printf("%30s %p\n", "void *value.p: ", e->value.p);
	printf("%30s %p\n", "char *value.s: ", e->value.s);
	printf("%30s %u\n", "unsigned value.u: ", e->value.u);
	printf("%30s %u\n", "unsigned value.x: ", e->value.x);
	printf("%30s %d\n", "unsigned char value.c: ", e->value.c);
	printf("%30s %d\n", "int value.d: ", e->value.d);
	printf("%30s %d\n", "int value.i: ", e->value.i);
	printf("%30s\n", "-------------------------------------------");
	printf("%30s %s\n", "const char *ptr: ", e->ptr);
	printf("%30s %p\n", "va_list *ap: ", e->ap);
	printf("%30s %s\n", "char *result: ", e->result);
	printf("%30s %d\n", "int size: ", e->size);
	printf("%30s %s\n", "char *prefix: ", e->prefix);
	printf("%30s %s\n", "char *itoa: ", e->itoa);
	printf("%30s %d\n", "int dsize: ", e->dsize);
	printf("%30s %d\n", "int sign: ", e->sign);
	printf("%30s %d\n", "int written: ", e->written);
	printf("%30s\n", "-------------------------------------------");
#endif
}
