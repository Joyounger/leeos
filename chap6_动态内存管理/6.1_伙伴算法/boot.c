// date:17.4.10
// author: linyang <942510346@qq.com>

typedef void (*init_func)(void);

#define UFCON0	((volatile unsigned int *)(0x50000020))

void helloworld(void)
{
	const char *p = "6.1_helloworld\n";
	while(*p) {
		*UFCON0 = *p++;
	};
}

static init_func init[] = {
	helloworld,
	0,
};

void test_mmu(void)
{
	const char *p = "6.1_test_mmu\n";
	while (*p) {
		*(volatile unsigned int *)0xd0000020 = *p++;
	};
}

extern void test_printk(void);

#define TIMER_BASE  (0xd1000000)
#define TCFG0   	((volatile unsigned int *)(TIMER_BASE+0x0))
#define TCFG1   	((volatile unsigned int *)(TIMER_BASE+0x4))
#define TCON    	((volatile unsigned int *)(TIMER_BASE+0x8))
#define TCONB4  	((volatile unsigned int *)(TIMER_BASE+0x3c))
void timer_init(void)
{
	*TCFG0|=0x800;
	*TCON&=(~(7<<20));
	*TCON|=(1<<22);
	*TCON|=(1<<21);

	*TCONB4=10000;

	*TCON|=(1<<20);
	*TCON&=~(1<<21);

	umask_int(14);
	enable_irq();
}

void plat_boot(void)
{
	int i;
	for(i = 0; init[i]; i++) {
		init[i]();
	}
	init_sys_mmu();
	start_mmu();
	test_mmu();
	test_printk();
	// timer_init();

	init_page_map();
	char *p1, *p2, *p3, *p4;
	p1 = (char *)get_free_pages(0,6);
	printk("6.1_the return address of get_free_pages %x\n",p1);
	p2 = (char *)get_free_pages(0,6);
	printk("6.1_the return address of get_free_pages %x\n",p2);
	put_free_pages(p2,6);
	put_free_pages(p1,6);
	p3 = (char *)get_free_pages(0,7);
	printk("6.1_the return address of get_free_pages %x\n",p3);
	p4 = (char *)get_free_pages(0,7);
	printk("6.1_the return address of get_free_pages %x\n",p4);

	while(1);
}


