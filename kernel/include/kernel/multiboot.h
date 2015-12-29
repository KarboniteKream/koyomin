#define MULTIBOOT_HEADER_MAGIC 0x1BADB002
#define MULTIBOOT_BOOTLOADER_MAGIC 0x2BADB002

// The Multiboot header.
typedef struct multiboot_header
{
	uint32_t magic;
	uint32_t flags;
	uint32_t checksum;
	uint32_t header_addr;
	uint32_t load_addr;
	uint32_t load_end_addr;
	uint32_t bss_end_addr;
	uint32_t entry_addr;
} multiboot_header_t;

// The symbol table for a.out.
typedef struct aout_symbol_table
{
	uint32_t tabsize;
	uint32_t strsize;
	uint32_t addr;
	uint32_t reserved;
} aout_symbol_table_t;

// The section header table for ELF.
typedef struct elf_section_header_table
{
	uint32_t num;
	uint32_t size;
	uint32_t addr;
	uint32_t shndx;
} elf_section_header_table_t;

// The Multiboot information.
typedef struct multiboot_info
{
	uint32_t flags;
	uint32_t mem_lower;
	uint32_t mem_upper;
	uint32_t boot_device;
	uint32_t cmdline;
	uint32_t mods_count;
	uint32_t mods_addr;
	union
	{
		aout_symbol_table_t aout_sym;
		elf_section_header_table_t elf_sec;
	} u;
	uint32_t mmap_length;
	uint32_t mmap_addr;
} multiboot_info_t;

// The memory map.
typedef struct multiboot_memory_map
{
	uint32_t size;
	uint32_t base_addr_low;
	uint32_t base_addr_high;
	uint32_t length_low;
	uint32_t length_high;
	uint32_t type;
} multiboot_memory_map_t;
