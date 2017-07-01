# date:17.4.10
# author: linyang <942510346@qq.com>


.equ DISABLE_IRQ,0x80
.equ DISABLE_FIQ,0x40
.equ SYS_MOD,0x1f
.equ IRQ_MOD,0x12
.equ FIQ_MOD,0x11
.equ SVC_MOD,0x13
.equ ABT_MOD,0x17
.equ UND_MOD,0x1b
.equ MOD_MASK,0x1f


.macro CHANGE_TO_SVC
        msr     cpsr_c,#(DISABLE_FIQ|DISABLE_IRQ|SVC_MOD)
.endm

.macro CHANGE_TO_IRQ
        msr     cpsr_c,#(DISABLE_FIQ|DISABLE_IRQ|IRQ_MOD)
.endm


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
	str r14,[r13,#-0x4]
	mrs r14,spsr
	str r14,[r13,#-0x8]
	str r0,[r13,#-0xc]
	mov r0,r13
	CHANGE_TO_SVC
	str r14,[r13,#-0x8]!
	ldr r14,[r0,#-0x4]
	str r14,[r13,#-0x4]
	ldr r14,[r0,#-0x8]
	ldr r0,[r0,#-0xc]
	stmdb r13!,{r0-r3,r14}
	bl common_irq_handler
	ldmia r13!,{r0-r3,r14}
	msr spsr,r14
	ldmfd r13!,{r14,pc}^
__vector_fiq:
	nop
