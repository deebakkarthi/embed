.global _start

.section .text

_start:
	mov r0, #15
	mov r1, #45
	add r0, r0, r1
	sub r1, r0, r1
	sub r0, r0, r1
	b _exit

_exit:
	mov r0, #0
	mov r7, #0x01
	swi 0

.section data
