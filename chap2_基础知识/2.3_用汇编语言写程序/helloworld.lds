ENTRY(helloworld)
SECTIONS
{
	. = 0x00000000;
	.text :{
	   *(.text)
	}
	. = ALIGN(32);
	.data :{
	   *(.data)
	}
	. = ALIGN(32);
	.bss :{
	   *(.bss)
	}
}