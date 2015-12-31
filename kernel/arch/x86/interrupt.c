#include <stdint.h>

#include <kernel/pic.h>

struct interrupt_context
{
	uint32_t ebp;
	uint32_t edi;
	uint32_t esi;
	uint32_t edx;
	uint32_t ecx;
	uint32_t ebx;
	uint32_t eax;
	uint32_t int_no;
	uint32_t err_code;
	// TODO: Check if eip is really on stack.
	// uint32_t eip;
	uint32_t cs;
	uint32_t eflags;
	// If (cs & 0x03) != 0.
	uint32_t esp;
	uint32_t ss;
};

void isr_handler(struct interrupt_context *int_ctx)
{
	(void)int_ctx;
}

void irq_handler(struct interrupt_context *int_ctx)
{
	uint8_t irq = int_ctx->int_no - 32;

	// Handle spurious IRQs.
	if(irq == 7 && (pic_read_isr() & (1 << 7)) == 0)
		return;
	if(irq == 15 && (pic_read_isr() & (1 << 15)) == 0)
	{
		pic_master_eoi();
		return;
	}

	(void)int_ctx;

	if(irq > 7)
		pic_slave_eoi();
	pic_master_eoi();
}

void interrupt_handler(struct interrupt_context *int_ctx)
{
	if(int_ctx->int_no < 32)
		isr_handler(int_ctx);
	else if(32 <= int_ctx->int_no && int_ctx->int_no < 32 + 16)
		irq_handler(int_ctx);
}
