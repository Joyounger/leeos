// date:17.4.10
// author: linyang <942510346@qq.com>

#include "storage.h"
#include "fs.h"
#include "elf.h"

typedef void (*init_func)(void);

#define UFCON0	((volatile unsigned int *)(0x50000020))

void helloworld(void)
{
	const char *p = "8.2_helloworld\n";
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
	const char *p = "8.2_test_mmu\n";
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

void *kmalloc(unsigned int size);

void plat_boot(void)
{
	int i;
	for(i = 0; init[i]; i++) {
		init[i]();
	}
	init_sys_mmu();
	start_mmu();
	// test_mmu();
	// test_printk();
	// timer_init();
	init_page_map();
	kmalloc_init();
	ramdisk_driver_init();
	romfs_init();


	struct inode *node;
	struct elf32_phdr *phdr;
	struct elf32_ehdr *ehdr;
	int pos,dpos;
	char *buf;
	if((buf = kmalloc(1024)) == (void *)0) {
		printk("8.2_get free pages error\n");
		goto HALT;
	}
	if((node = fs_type[ROMFS]->namei(fs_type[ROMFS],"main.elf")) == (void *)0) {
		printk("8.2_inode read eror\n");
		goto HALT;
	}
	if(fs_type[ROMFS]->device->dout(fs_type[ROMFS]->device,buf,fs_type[ROMFS]->get_daddr(node),1024)) {
		printk("8.2_dout error\n");
		goto HALT;
	}
	ehdr = (struct elf32_ehdr *)buf;
	phdr = (struct elf32_phdr *)((char *)buf+ehdr->e_phoff);
	for(i = 0; i < ehdr->e_phnum; i++) {
		if(CHECK_PT_TYPE_LOAD(phdr)) {
			if(fs_type[ROMFS]->device->dout(fs_type[ROMFS]->device,(char *)phdr->p_vaddr,fs_type[ROMFS]->get_daddr(node)+phdr->p_offset,phdr->p_filesz)<0) {
				printk("8.2_dout error\n");
				goto HALT;
			}
			phdr++;
		}
	}
	exec(ehdr->e_entry);

	// 8.1 section
	/*struct inode *node;
	char *buf = (char *)0x30100000;
	if((node = fs_type[ROMFS]->namei(fs_type[ROMFS],"main.bin")) == (void *)0) {
		printk("8.1_inode read eror\n");
		goto HALT;
	}
	if(fs_type[ROMFS]->device->dout(fs_type[ROMFS]->device,buf,fs_type[ROMFS]->get_daddr(node),node->dsize)) {
		printk("8.1_dout error\n");
		goto HALT;
	}
	exec(buf);*/

	// 7.2 section
	/*struct inode *node;
	char buf[128];
	node = fs_type[ROMFS]->namei(fs_type[ROMFS], "number.txt");
	fs_type[ROMFS]->device->dout(fs_type[ROMFS]->device, buf, fs_type[ROMFS]->get_daddr(node), node->dsize);
	printk("7.2_the content of file number.txt in ram.img is\n");
	for(i = 0; i < sizeof(buf); i++) {
		printk("%c ",buf[i]);
	}
	printk("\n");*/

HALT:
	while(1);
}


