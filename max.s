.global _start
.section .text


_start:
	ldr r0, =nums
	ldm r0, {r1-r3}
	cmp r1, r2
	movge r4, r1 //r4 is the curr_max
	movle r4, r2
	cmp r4, r3
	movle r4, r3
	b _exit

_exit:
	mov r0, #0 //return 0
        mov r7, #0x01 //exit() syscall
        svc 0x0

.section .data
        nums: .word 4, 5, 6
