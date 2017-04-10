// date:17.4.9
// author: linyang <942510346@qq.com>
// helloworld.c



#define UFCON0	((volatile unsigned int *)(0x50000020))

void helloworld(void){
	
	const char *p="2.2_helloworld\n";
	while(*p){
		*UFCON0=*p++;
	};
	while(1); 
}


/*
kolya@asus ~/src/leeos/chap2_基础知识 $ /home/kolya/Downloads/skyeye-1.2.6_rc1/skyeye

**************************** WARNING **********************************
If you want to run ELF image, you should use -e option to indicate
your elf-format image filename. Or you only want to run binary image,
you need to set the filename of the image and its entry in skyeye.conf.
***********************************************************************

Your elf file is little endian.
arch: arm
cpu info: armv4, arm920t, 41009200, ff00fff0, 2 
mach info: name s3c2410x, mach_init addr 0x425800
uart_mod:0, desc_in:, desc_out:, converter:
SKYEYE: use arm920t mmu ops
Loaded RAM   ./helloworld.bin
2.2_helloworld
*/
