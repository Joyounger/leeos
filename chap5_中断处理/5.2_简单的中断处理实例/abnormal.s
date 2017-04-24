# date:17.4.10
# author: linyang <942510346@qq.com>

.global __vector_undefined
.global __vector_swi
.global __vector_prefetch_abort
.global __vector_data_abort
.global __vector_reserved
.global __vector_irq
.global __vector_fiq

.text
.code 32

__vector_undefined:
	nop
__vector_swi:
	nop
__vector_prefetch_abort:	
	nop
__vector_data_abort:
	nop
__vector_reserved:
	nop
__vector_irq:
	sub r14,r14,#4
	stmfd r13!,{r0-r3,r14}
	bl common_irq_handler
	ldmfd r13!,{r0-r3,pc}^
__vector_fiq:
	nop
