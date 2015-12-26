.section .text

.global _start
_start:
	call _init
	call main
	call _fini
