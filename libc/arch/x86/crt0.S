.section .text

.global _start
.type _start, @function
_start:
	call _init
	call main
	call exit
.size _start, . - _start
