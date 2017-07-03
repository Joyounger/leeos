// date:17.4.10
// author: linyang <942510346@qq.com>


#ifndef __ELF_H__
#define __ELF_H__

typedef unsigned int elf32_addr;
typedef unsigned int elf32_word;
typedef signed int elf32_sword;
typedef unsigned short elf32_half;
typedef unsigned int elf32_off;

struct elf32_ehdr{
	unsigned char e_ident[16];     		/* 魔数和相关信息 */
	elf32_half	e_type;                 /* 目标文件类型 */
	elf32_half	e_machine;              /* 硬件体系 */
	elf32_word	e_version;              /* 目标文件版本 */
	elf32_addr	e_entry;                /* 程序进入点 */
	elf32_off	e_phoff;                /* 程序头部偏移量 */
	elf32_off	e_shoff;                /* 节头部偏移量 */
	elf32_word	e_flags;                /* 处理器特定标志 */
	elf32_half	e_ehsize;               /* elf头部长度 */
	elf32_half	e_phentsize;            /* 程序头部中一个条目的长度 */
	elf32_half	e_phnum;                /* 程序头部条目个数  */
	elf32_half	e_shentsize;            /* 节头部中一个条目的长度 */
	elf32_half	e_shnum;                /* 节头部条目个数 */
	elf32_half	e_shstrndx;             /* 节头部字符表索引 */
};
struct elf32_phdr{
	elf32_word	p_type;					/* 段类型 */
	elf32_off	p_offset;     	 		/* 段位置相对于文件开始处的偏移量 */
	elf32_addr	p_vaddr;   				/* 段在内存中的地址 */
	elf32_addr	p_paddr;   				/* 段的物理地址 */
	elf32_word	p_filesz;				/* 段在文件中的长度 */
	elf32_word	p_memsz;				/* 段在内存中的长度 */
	elf32_word	p_flags;				/* 段的标记 */
	elf32_word	p_align;				/* 段在内存中对齐标记 */
};

/*definition of elf class*/
#define ELFCLASSNONE	0
#define ELFCLASS32		1
#define ELFCLASS64		2
#define CHECK_ELF_CLASS(p)				((p)->e_ident[4])
#define CHECK_ELF_CLASS_ELFCLASS32(p)	(CHECK_ELF_CLASS(p)==ELFCLASS32)

/*definition of elf data*/
#define ELFDATANONE		0
#define ELFDATA2LSB		1
#define ELFDATA2MSB		2
#define CHECK_ELF_DATA(p)				((p)->e_ident[5])
#define CHECK_ELF_DATA_LSB(p)	(CHECK_ELF_DATA(p)==ELFDATA2LSB)

/*elf type*/
#define ET_NONE			0
#define ET_REL			1
#define ET_EXEC			2
#define ET_DYN			3
#define ET_CORE			4
#define ET_LOPROC		0xff00
#define ET_HIPROC		0xffff
#define CHECK_ELF_TYPE(p)			((p)->e_type)
#define CHECK_ELF_TYPE_EXEC(p)		(CHECK_ELF_TYPE(p)==ET_EXEC)

/*elf machine*/
#define EM_NONE			0
#define EM_M32			1
#define EM_SPARC		2
#define EM_386			3
#define EM_68k			4
#define EM_88k			5
#define EM_860			7
#define EM_MIPS			8
#define EM_ARM			40
#define CHECK_ELF_MACHINE(p)		((p)->e_machine)
#define CHECK_ELF_MACHINE_ARM(p)	(CHECK_ELF_MACHINE(p)==EM_ARM)

/*elf version*/
#define EV_NONE			0
#define EV_CURRENT		1
#define CHECK_ELF_VERSION(p)			((p)->e_ident[6])
#define CHECK_ELF_VERSION_CURRENT(p)	(CHECK_ELF_VERSION(p)==EV_CURRENT)

#define ELF_FILE_CHECK(hdr)	((((hdr)->e_ident[0])==0x7f)&&\
								(((hdr)->e_ident[1])=='E')&&\
								(((hdr)->e_ident[2])=='L')&&\
								(((hdr)->e_ident[3])=='F'))


#define PT_NULL 				0
#define PT_LOAD 				1
#define PT_DYNAMIC 				2
#define PT_INTERP 				3
#define PT_NOTE 				4
#define PT_SHLIB 				5
#define PT_PHDR 				6
#define PT_LOPROC				0x70000000
#define PT_HIPROC				0x7fffffff
#define CHECK_PT_TYPE(p)		((p)->p_type)
#define CHECK_PT_TYPE_LOAD(p)	(CHECK_PT_TYPE(p)==PT_LOAD)
#endif
