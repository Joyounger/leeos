CC=arm-none-eabi-gcc
LD=arm-none-eabi-ld
OBJCOPY=arm-none-eabi-objcopy

CFLAGS= -O2 -g
ASFLAGS= -O2 -g
LDFLAGS=-Tleeos.lds -Ttext 30000000

OBJS=start.o helloworld.o

.c.o:
	$(CC) $(CFLAGS) -c $<
.s.o:
	$(CC) $(ASFLAGS) -c $<

leeos.elf:$(OBJS)
	$(CC) -static -nostartfiles -nostdlib $(LDFLAGS) $? -o $@ -lgcc
	$(OBJCOPY) -O binary $@ leeos.bin

clean:
	rm *.o leeos.elf leeos.bin -f
