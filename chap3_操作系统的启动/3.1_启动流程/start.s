# date:17.4.10
# author: linyang <942510346@qq.com>

.section .startup
.code 32
.align 0

.global _start
.extern __vector_reset
.extern __vector_undefined
.extern __vector_swi
.extern __vector_prefetch_abort
.extern __vector_data_abort
.extern __vector_reserved
.extern __vector_irq
.extern __vector_fiq

_start:
	ldr pc,_vector_reset
	ldr pc,_vector_undefined
	ldr pc,_vector_swi
	ldr pc,_vector_prefetch_abort
	ldr pc,_vector_data_abort
	ldr pc,_vector_reserved
	ldr pc,_vector_irq
	ldr pc,_vector_fiq

	.align 4

_vector_reset:			.word  __vector_reset
_vector_undefined:		.word  __vector_undefined
_vector_swi:			.word  __vector_swi
_vector_prefetch_abort:	.word  __vector_prefetch_abort
_vector_data_abort:		.word  __vector_data_abort
_vector_reserved:		.word  __vector_reserved
_vector_irq:			.word  __vector_irq
_vector_fiq:			.word  __vector_fiq
