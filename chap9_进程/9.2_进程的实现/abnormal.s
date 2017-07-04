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

.macro CHANGE_TO_SYS
        msr     cpsr_c,#(DISABLE_FIQ|DISABLE_IRQ|SYS_MOD)
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
	str	r14,[r13,#-0xc]
	mrs	r14,spsr
	str	r14,[r13,#-0x8]
	str r0,[r13,#-0x4]
	mov	r0,r13
	CHANGE_TO_SYS
	str	r14,[r13,#-8]!
	ldr	r14,[r0,#-0xc]
	str	r14,[r13,#4]
	ldr r14,[r0,#-0x8]
	ldr r0,[r0,#-0x4]
	stmfd r13!,{r0-r3,r14}
	ldr r3,[r13,#24]
	ldr r0,[r3,#-4]
	bic r0,r0,#0xff000000
	ldr r1,[r13,#32]
	ldr r2,[r13,#36]
	bl	sys_call_schedule
	str r0,[r13,#28]
	ldmfd r13!,{r0-r3}
	ldmfd r13!,{r14}
	msr cpsr,r14
	ldmfd r13!,{r14,pc}
__vector_prefetch_abort:	
	nop
__vector_data_abort:
	nop
__vector_reserved:
	nop
__vector_irq:
	sub r14,r14,#4
	stmfd r13!,{r0}
	stmfd r13!,{r1-r3}

	mov r2,#0xca000000
	add r1,r2,#0x10
	ldr r0,[r1]
	ldr r3,[r2]
	orr r3,r3,r1
	str r3,[r2]
	str r0,[r1]

	ldmfd r13!,{r1-r3}
	mov r0,r14
	CHANGE_TO_SYS
	stmfd r13!,{r0}
	stmfd r13!,{r14}
	CHANGE_TO_IRQ
	ldmfd r13!,{r0}
	ldr r14,=__asm_schedule
	stmfd r13!,{r14}
	ldmfd r13!,{pc}^

__asm_schedule:
	stmfd r13!,{r0-r12}
	mrs	r1, cpsr
	stmfd r13!,{r1}

	mov	r1,sp
	bic	r1,#0xff0
	bic r1,#0xf
	mov r0,sp
	str r0,[r1]

	bl __common_schedule
	ldr sp,[r0]
	ldmfd r13!,{r1}
	msr cpsr_cxsf,r1
	ldmfd r13!,{r0-r12,r14,pc}

__vector_fiq:
	nop
