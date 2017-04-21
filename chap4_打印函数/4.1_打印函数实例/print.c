// date:17.4.10
// author: linyang <942510346@qq.com>


typedef char * va_list;
#define _INTSIZEOF(n)	((sizeof(n)+sizeof(int)-1)&~(sizeof(int) - 1) )
#define va_start(ap,v) 	( ap = (va_list)&v + _INTSIZEOF(v) )
#define va_arg(ap,t) 	( *(t *)((ap += _INTSIZEOF(t)) - _INTSIZEOF(t)) )
#define va_end(ap)    	( ap = (va_list)0 )

void test_num(int num)
{
	*(char *)0xd0000020 = num  + '0';
}

void test_vparameter(int i,...)
{
	int mm;
	va_list argv;
	va_start(argv,i);
	while(i--) {
		mm = va_arg(argv,int);
		test_num(mm);
	}
	va_end(argv);
}
