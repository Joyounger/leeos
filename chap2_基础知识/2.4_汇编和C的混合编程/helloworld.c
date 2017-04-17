
int helloworld(unsigned int *addr, const char *p)
{
	while(*p) {
		*addr = *p++;
	};

	return 0;
}


/*
kolya@asus ~/src/leeos/chap2_基础知识/2.4_汇编和C的混合编程 $ ../../skyeye_1.2.6rc1_linux/skyeye

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
2.4_helloworld
*/