.global _start
.section .text

_start:
        mov r7, #0x04 //write() syscall
        mov r0, #1 //STDOUT fd
        ldr r1, =message //addr of string
        mov r2, #13 //len of string
        swi 0

        mov r7, #0x01 //exit() syscall
        swi 0

.section .data
        message: .ascii "Hello, World\n"
