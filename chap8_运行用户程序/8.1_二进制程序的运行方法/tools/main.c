// date:17.4.10
// author: linyang <942510346@qq.com>


int main()
{
	const char *p = "8.1_this is a test application\n";
	while(*p) {
		*(volatile unsigned int *)0xd0000020 = *p++;
	};
}
