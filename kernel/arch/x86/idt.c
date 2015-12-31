#include <kernel/idt.h>

#include <stdint.h>
#include <string.h>

#define IDT_FLAG_PRESENT (1 << 7)
#define IDT_TYPE_INTERRUPT 0xE

struct idt_entry
{
	uint16_t handler_low;
	uint16_t selector;
	uint8_t zero;
	uint8_t flags;
	uint16_t handler_high;
};

struct idt_entry idt[256];

void lidt(size_t size, uintptr_t addr)
{
	asm volatile("subl $6, %%esp\n\t"
				 "movw %w0, 0(%%esp)\n\t"
				 "movl %1, 2(%%esp)\n\t"
				 "lidt (%%esp)\n\t"
				 "addl $6, %%esp" : : "rN" (size), "r" (addr));
}

void idt_create_entry(struct idt_entry *entry, void (*handler)(void))
{
	entry->handler_low = (uintptr_t)handler & 0xFFFF;
	entry->selector = 0x08; // Kernel Code Segment.
	entry->zero = 0;
	entry->flags = IDT_FLAG_PRESENT | IDT_TYPE_INTERRUPT;
	entry->handler_high = (uintptr_t)handler >> 16 & 0xFFFF;
}

void idt_init()
{
	memset(idt, 0, sizeof(idt));
	idt_create_entry(&idt[33], irq1);
	lidt(sizeof(idt) - 1, (uintptr_t)idt);
}
