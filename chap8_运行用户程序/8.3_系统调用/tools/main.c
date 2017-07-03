// date:17.4.10
// author: linyang <942510346@qq.com>

#include "../syscall.h"

int main()
{
	const char *p = "8.3_this is a test application\n";
	while(*p) {
		*(volatile unsigned int *)0xd0000020 = *p++;
	};
	
	int test_array[2],ret;
	test_array[0]=0xf0;
	test_array[1]=0x0f;


	SYSCALL(__NR_test,2,test_array,ret);
}
