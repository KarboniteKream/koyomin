#ifndef _KERNEL_PIC_H
#define _KERNEL_PIC_H

#include <stdint.h>

void pic_init();
void pic_master_eoi();
void pic_slave_eoi();
uint16_t pic_read_irr();
uint16_t pic_read_isr();

#endif
