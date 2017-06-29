# date:17.4.10
# author: linyang <942510346@qq.com>

CC=arm-none-eabi-gcc
LD=arm-none-eabi-ld
OBJCOPY=arm-none-eabi-objcopy

CFLAGS= -O2 -g
ASFLAGS= -O2 -g
LDFLAGS=-Tleeos.lds -Ttext 30000000 

OBJS=init.o start.o boot.o abnormal.o mmu.o print.o interrupt.o mem.o driver.o ramdisk.o

.c.o:
	$(CC) $(CFLAGS) -c $<
.s.o:
	$(CC) $(ASFLAGS) -c $<

leeos.elf:$(OBJS)
	$(CC) -static -nostartfiles -nostdlib $(LDFLAGS) $? -o $@ -lgcc
	$(OBJCOPY) -O binary $@ leeos.bin

clean:
	rm *.o leeos.elf leeos.bin -f
