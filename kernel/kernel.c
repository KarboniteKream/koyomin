#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/multiboot.h>
#include <kernel/pic.h>
#include <kernel/tty.h>

void kernel_early(void)
{
	pic_init();
	tty_init();
}

void kernel_main(multiboot_info_t *mbt)
{
	printf("\nMemory Map -----\n");

	if((mbt->flags & 0x1) == 1)
		printf("lower=%dKB, upper=%dKB\n", mbt->mem_lower, mbt->mem_upper);

	if((mbt->flags & 0x5) == 0x5)
	{
		printf("mmap_addr=0x%X, mmap_length=0x%X\n", mbt->mmap_addr, mbt->mmap_length);
		multiboot_memory_map_t *mmap = (multiboot_memory_map_t *)mbt->mmap_addr;

		while((uintptr_t)mmap < mbt->mmap_addr + mbt->mmap_length)
		{
			printf("size=0x%X, base_addr=0x%X%X, length=0x%X%X, type=%X\n", mmap->size, mmap->base_addr_high, mmap->base_addr_low, mmap->length_high, mmap->length_low, mmap->type);
			mmap = (multiboot_memory_map_t *)((uintptr_t)mmap + mmap->size + sizeof(mmap->size));
		}
	}

	printf("\n");

	printf("koyomin v0.0.1\n$ ");
}
