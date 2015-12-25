#include <stdio.h>

#ifdef __is_kernel
#include <kernel/tty.h>
#endif

int putchar(int ch)
{
#ifdef __is_kernel
	char c = (char)ch;
	tty_write(&c, sizeof(c));
#else
	// TODO: Implement a write system call.
#endif
	return ch;
}
