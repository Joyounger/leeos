// date:17.4.10
// author: linyang <942510346@qq.com>


#define __NR_SYSCALL_BASE	0x0

#define __NR_test						(__NR_SYSCALL_BASE+ 0)
#define __NR_SYS_CALL					(__NR_SYSCALL_BASE+1)


typedef int (*syscall_fn)(int num,int *args);


#define SYSCALL(num,pnum,parray,ret)	do{							\
							asm volatile(							\
								"stmfd r13!,{%3}\n"\
								"stmfd r13!,{%2}\n"\
								"sub r13,r13,#4\n"\
								"swi %1\n"							\
								"ldmfd r13!,{%0}\n"\
								"add r13,r13,#8\n"\
								:"=r"(ret)							\
								:"i"(num),"r"(pnum),"r"(parray)		\
								:"r2","r3"\
								);									\
							}while(0)

