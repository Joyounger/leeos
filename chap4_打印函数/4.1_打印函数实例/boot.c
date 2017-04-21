// date:17.4.10
// author: linyang <942510346@qq.com>

typedef void (*init_func)(void);

#define UFCON0	((volatile unsigned int *)(0x50000020))

void helloworld(void)
{
	const char *p = "4.1_helloworld\n";
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
	const char *p = "4.1_test_mmu\n";
	while (*p) {
		*(volatile unsigned int *)0xd0000020 = *p++;
	};
}

void plat_boot(void)
{
	extern void test_vparameter(int,...);
	int i;
	for(i = 0; init[i]; i++) {
		init[i]();
	}
	init_sys_mmu();
	start_mmu();
	test_mmu();
	test_vparameter(3, 9, 8, 7);
	test_vparameter(2, 6, 5);

	while(1);
}


