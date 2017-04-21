// date:17.4.10
// author: linyang <942510346@qq.com>


/*mask for page table base addr*/
#define PAGE_TABLE_L1_BASE_ADDR_MASK	(0xffffc000)

#define VIRT_TO_PTE_L1_INDEX(addr)		(((addr)&0xfff00000)>>18)

#define PTE_L1_SECTION_NO_CACHE_AND_WB	(0x0<<2)
#define PTE_L1_SECTION_DOMAIN_DEFAULT	(0x0<<5)
#define PTE_ALL_AP_L1_SECTION_DEFAULT	(0x1<<10)

#define PTE_L1_SECTION_PADDR_BASE_MASK	(0xfff00000)
#define PTE_BITS_L1_SECTION				(0x2)

#define L1_PTR_BASE_ADDR				0x30700000
#define PHYSICAL_MEM_ADDR				0x30000000
#define VIRTUAL_MEM_ADDR				0x30000000
#define MEM_MAP_SIZE					0x800000
#define PHYSICAL_IO_ADDR				0x48000000
#define VIRTUAL_IO_ADDR					0xc8000000
#define IO_MAP_SIZE						0x18000000

void start_mmu(void)
{
	unsigned int ttb = L1_PTR_BASE_ADDR;

	asm (
		"mcr p15,0,%0,c2,c0,0\n"    /* set base address of page table*/
		"mvn r0,#0\n"                  
		"mcr p15,0,r0,c3,c0,0\n"    /* enable all region access*/

		"mov r0,#0x1\n"
		"mcr p15,0,r0,c1,c0,0\n"    /* set back to control register */
		"mov r0,r0\n"
		"mov r0,r0\n"
		"mov r0,r0\n"
		:
		: "r" (ttb)
		:"r0"
	);
}

unsigned int gen_l1_pte(unsigned int paddr)
{
	return (paddr & PTE_L1_SECTION_PADDR_BASE_MASK) | PTE_BITS_L1_SECTION;
}

unsigned int gen_l1_pte_addr(unsigned int baddr, unsigned int vaddr)
{
	return (baddr & PAGE_TABLE_L1_BASE_ADDR_MASK) | VIRT_TO_PTE_L1_INDEX(vaddr);
}

void init_sys_mmu(void)
{
	unsigned int pte;
	unsigned int pte_addr;
	int j;

	for(j = 0; j < MEM_MAP_SIZE>>20; j++) {
		pte = gen_l1_pte(PHYSICAL_MEM_ADDR + (j<<20));
		pte |= PTE_ALL_AP_L1_SECTION_DEFAULT;
		pte |= PTE_L1_SECTION_NO_CACHE_AND_WB;
		pte |= PTE_L1_SECTION_DOMAIN_DEFAULT;
		pte_addr = gen_l1_pte_addr(L1_PTR_BASE_ADDR, VIRTUAL_MEM_ADDR + (j<<20));
		*(volatile unsigned int *)pte_addr = pte;
	}

	for(j = 0; j< IO_MAP_SIZE>>20; j++) {
		pte = gen_l1_pte(PHYSICAL_IO_ADDR+(j<<20));
		pte |= PTE_ALL_AP_L1_SECTION_DEFAULT;
		pte |= PTE_L1_SECTION_NO_CACHE_AND_WB;
		pte |= PTE_L1_SECTION_DOMAIN_DEFAULT;
		pte_addr = gen_l1_pte_addr(L1_PTR_BASE_ADDR, VIRTUAL_IO_ADDR + (j<<20));
		*(volatile unsigned int *)pte_addr = pte;
	}
}

