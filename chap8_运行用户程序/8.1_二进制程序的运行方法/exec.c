// date:17.4.10
// author: linyang <942510346@qq.com>


int exec(unsigned int start)
{
	asm volatile(
		"mov pc,r0\n\t"
	);

	return 0;
}
