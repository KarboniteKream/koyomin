.global irq1
.type irq1, @function
irq1:
	pushl $0 # Error code.
	pushl $(1 + 32)
	jmp interrupt_handler_prepare
.size irq1, . - irq1

.type interrupt_handler_prepare, @function
interrupt_handler_prepare:
	pushl %eax
	pushl %ebx
	pushl %ecx
	pushl %edx
	pushl %esi
	pushl %edi
	# esp
	pushl %ebp

	movl %esp, %ebx
	subl $4, %esp
	andl $0xFFFFFFF0, %esp # 16-byte align stack.
	movl %ebx, (%esp)
	call interrupt_handler
	movl %ebx, %esp

	popl %ebp
	popl %edi
	popl %esi
	popl %edx
	popl %ecx
	popl %ebx
	popl %eax

	addl $8, %esp
	iret
.size interrupt_handler_prepare, . - interrupt_handler_prepare
