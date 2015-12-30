#ifndef _KERNEL_IOPORT_H
#define _KERNEL_IOPORT_H

#include <stdint.h>

static inline uint8_t inportb(uint16_t port)
{
	uint8_t value;
	asm volatile("inb %1, %0" : "=a" (value) : "dN" (port));
	return value;
}

static inline void outportb(uint16_t port, uint8_t value)
{
	asm volatile("outb %0, %1" : : "a" (value), "dN" (port));
}

#endif
