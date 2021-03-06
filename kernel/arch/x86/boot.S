# Declare constants used for creating a multiboot header.
.set ALIGN, 1 << 0 # align loaded modules on page boundaries
.set MEMINFO, 1 << 1 # provide memory map
.set FLAGS, ALIGN | MEMINFO
.set MAGIC, 0x1BADB002
.set CHECKSUM, -(MAGIC + FLAGS)

# Declare a header as in the Multiboot Standard.
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Reserve a stack for the initial thread.
.section .bootstrap_stack, "aw", @nobits
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

# The kernel entry point.
.section .text
.global _start
.type _start, @function
_start:
	# Note that the processor is not fully initialized yet and stuff
	# such as floating point instructions are not available yet.
	movl $stack_top, %esp

	# Push memory map on stack.
	push %ebx

	# Disable interrupts.
	cli

	# Load the Global Descriptor Table.
	push %ax
	subl $6, %esp
	movw gdt_size, %ax
	movw %ax, 0(%esp)
	movl $gdt, %eax
	movl %eax, 2(%esp)
	lgdt 0(%esp)
	addl $6, %esp

	# Reload data segment registers.
	movw $0x10, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs
	movw %ax, %ss
	ljmp $0x08, $_reload
_reload:
	pop %ax

	# Initialize the core kernel before running the global constructors.
	call kernel_early

	# Enable interrupts.
	sti

	# Call the global constructors.
	call _init

	# Transfer control to the main kernel.
	call kernel_main

	# Hang if kernel_main unexpectedly returns.
	cli
.Lhang:
	hlt
	jmp .Lhang

# Set the size of the _start symbol to the current location '.' minus its start.
# This is useful when debugging or when you implement call tracing.
.size _start, . - _start
