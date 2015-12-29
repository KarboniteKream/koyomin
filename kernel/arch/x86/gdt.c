#include <stdint.h>

#define GRAN_4KIB_BLOCKS (1 << 7)
#define GRAN_32_BIT_MODE (1 << 6)
#define GRAN_64_BIT_MODE (1 << 5)

#define GDT_ENTRY(base, limit, access, granularity) \
{ \
	(limit) & 0xFFFF, \
	(base) >> 0 & 0xFFFF, \
	(base) >> 16 & 0xFF, \
	(access) & 0xFF, \
	((limit) >> 16 & 0x0F) | ((granularity) & 0xF0), \
	(base) >> 24 & 0xFF \
}

struct gdt_entry
{
	uint16_t limit;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t granularity;
	uint8_t base_high;
};

struct gdt_entry gdt[] =
{
	// Null Segment.
	GDT_ENTRY(0, 0, 0, 0),

	// Kernel Code Segment.
	GDT_ENTRY(0, 0xFFFFFFFF, 0x9A, GRAN_32_BIT_MODE | GRAN_4KIB_BLOCKS),

	// Kernel Data Segment.
	GDT_ENTRY(0, 0xFFFFFFFF, 0x92, GRAN_32_BIT_MODE | GRAN_4KIB_BLOCKS),

	// User Code Segment.
	GDT_ENTRY(0, 0xFFFFFFFF, 0xFA, GRAN_32_BIT_MODE | GRAN_4KIB_BLOCKS),

	// User Data Segment.
	GDT_ENTRY(0, 0xFFFFFFFF, 0xF2, GRAN_32_BIT_MODE | GRAN_4KIB_BLOCKS),
};

uint16_t gdt_size = sizeof(gdt) - 1;
