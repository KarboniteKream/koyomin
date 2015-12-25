#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/tty.h>

void kernel_early(void)
{
	tty_init();
}

void kernel_main(void)
{
	printf("koyomin v0.0.1\n$ ");
}
