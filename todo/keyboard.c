#include <stdint.h>
#include <stdio.h>

#include <kernel/pic.h>
#include <kernel/portio.h>
#include <kernel/tty.h>

struct interrupt_context
{
	uint32_t gs;
	uint32_t fs;
	uint32_t ds;
	uint32_t es;
	uint32_t int_no;
	uint32_t err_code;
	uint32_t cs;
	uint32_t eflags;
	uint32_t esp;
	uint32_t ss;
};

char scancodes[] =
{
	'?', // escape
	'1',
	'2',
	'3',
	'4',
	'5',
	'6',
	'7',
	'8',
	'9',
	'0',
	'-',
	'=',
	'?', // backspace
	'?', // tab
	'q',
	'w',
	'e',
	'r',
	't',
	'y',
	'u',
	'i',
	'o',
	'p',
	'[',
	']',
	'\n',
	'?', // lctrl
	'a',
	's',
	'd',
	'f',
	'g',
	'h',
	'j',
	'k',
	'l',
	';',
	'\'',
	'?', // backtick
	'?', // lshift
	'\\',
	'z',
	'x',
	'c',
	'v',
	'b',
	'n',
	'm',
	',',
	'.',
	'/',
	'?', // rshift,
	'*', // keypad
	'?', // lalt
	' '
};

char getchar(uint8_t scancode)
{
	return scancodes[scancode - 1];
}

void isr_handler(struct interrupt_context* int_ctx)
{
	printf("ISR%d\n", int_ctx->int_no);
}

void irq_handler(struct interrupt_context* int_ctx)
{
	uint8_t irq = int_ctx->int_no - 32;

	// Spurious IRQs (7 and 15).
	if(irq == 7 && !(pic_read_isr() & (1 << 7)))
		return;
	if(irq == 15 && !(pic_read_isr() & (1 << 15)))
	{
		pic_master_eoi();
		return;
	}

	if(irq == 1)
	{
		uint8_t c = inportb(0x60);
		if(c < 0x3A)
			putchar(getchar(c));
	}

	if(irq > 7)
		pic_slave_eoi();
	pic_master_eoi();
}

void interrupt_handler(struct interrupt_context* int_ctx)
{
	if(int_ctx->int_no < 32)
		isr_handler(int_ctx);
	else if(32 <= int_ctx->int_no && int_ctx->int_no < 32 + 16)
		irq_handler(int_ctx);
}
