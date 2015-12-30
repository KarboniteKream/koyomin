#include <kernel/pic.h>
#include <kernel/portio.h>

#define PIC_MASTER_CMD 0x20
#define PIC_MASTER_DATA 0x21
#define PIC_SLAVE_CMD 0xA0
#define PIC_SLAVE_DATA 0xA1

#define PIC_CMD_INIT 0x10
#define PIC_CMD_EOI 0x20

#define PIC_ICW1_ICW4 0x01
#define PIC_MODE_8086 0x01

#define PIC_READ_IRR 0x0A
#define PIC_READ_ISR 0x0B

void pic_init()
{
	outportb(PIC_MASTER_CMD, PIC_CMD_INIT + PIC_ICW1_ICW4);
	outportb(PIC_SLAVE_CMD, PIC_CMD_INIT + PIC_ICW1_ICW4);
	outportb(PIC_MASTER_DATA, 0x20);
	outportb(PIC_SLAVE_DATA, 0x20 + 8);
	outportb(PIC_MASTER_DATA, 0x04);
	outportb(PIC_SLAVE_DATA, 0x02);
	outportb(PIC_MASTER_DATA, PIC_MODE_8086);
	outportb(PIC_SLAVE_DATA, PIC_MODE_8086);
	outportb(PIC_MASTER_DATA, 0xFD);
	outportb(PIC_SLAVE_DATA, 0xFF);
}

void pic_master_eoi()
{
	outportb(PIC_MASTER_CMD, PIC_CMD_EOI);
}

void pic_slave_eoi()
{
	outportb(PIC_SLAVE_CMD, PIC_CMD_EOI);
}

uint16_t pic_read_irr()
{
	outportb(PIC_MASTER_CMD, PIC_READ_IRR);
	outportb(PIC_SLAVE_CMD, PIC_READ_IRR);
	return inportb(PIC_SLAVE_CMD) << 8 | inportb(PIC_MASTER_CMD);
}

uint16_t pic_read_isr()
{
	outportb(PIC_MASTER_CMD, PIC_READ_ISR);
	outportb(PIC_SLAVE_CMD, PIC_READ_ISR);
	return inportb(PIC_SLAVE_CMD) << 8 | inportb(PIC_MASTER_CMD);
}
