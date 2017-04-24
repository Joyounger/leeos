// date:17.4.10
// author: linyang <942510346@qq.com>


#define INT_BASE	(0xca000000)
#define INTMSK		(INT_BASE+0x8)
#define INTOFFSET	(INT_BASE+0x14)
#define INTPND		(INT_BASE+0x10)
#define SRCPND		(INT_BASE+0x0)

void enable_irq(void)
{
	asm volatile (
		"mrs r4,cpsr\n\t"
		"bic r4,r4,#0x80\n\t"
		"msr cpsr,r4\n\t"
		:::"r4"
	);
}

void umask_int(unsigned int offset)
{
	*(volatile unsigned int *)INTMSK &= ~(1<<offset);
}

void common_irq_handler(void)
{
	unsigned int tmp = (1<<(*(volatile unsigned int *)INTOFFSET));
	printk("%d\t",*(volatile unsigned int *)INTOFFSET);
	*(volatile unsigned int *)SRCPND |= tmp;
	*(volatile unsigned int *)INTPND |= tmp;
	printk("5.2_timer interrupt occured\n");
}
