.arch armv4
.global _start

.equ REG_FIFO, 0x50000020

.text
.align 2

_start:
	ldr r0,=REG_FIFO
	adr r1,.L0
	bl helloworld
.L1:
	b .L1

.align 2
.L0:
	.ascii "2.5_helloworld\n\0"
