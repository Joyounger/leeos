# leeos
一步步写嵌入式操作系统 linux平台实现代码


step 0
准备开发环境
1 安装交叉编译工具
sudo apt-get install gcc-arm-none-eabi
sudo apt-get install gcc-arm-linux-gnueabihf
sudo apt-get install g++-arm-linux-gnueabihf

2 手边编译skyeye
用apt命令安装的skyeye模拟器版本（1.2.5）有bug,需要手动编译更高版本的skyeye



下载并解压skyeye 1.2.6_rc1的代码，
 ~/Downloads/skyeye-1.2.6_rc1
根据执行skyeye-1.2.6_rc1/INSTALL的说明
1 执行 ./configure
2 执行 make 后
编译错误1：
In file included from /usr/include/fcntl.h:289:0,
                 from nandflash/nandflash_smallblock.c:19:
In function ‘open’,
    inlined from ‘nandflash_sb_setup’ at nandflash/nandflash_smallblock.c:519:24:
/usr/include/x86_64-linux-gnu/bits/fcntl2.h:50:4: error: call to ‘__open_missing_mode’ declared with attribute error: open with O_CREAT or O_TMPFILE in second argument needs 3 arguments
    __open_missing_mode ();

解决方法：
修改skyeye-1.2.6_rc1/device/nandflash/nandflash_smallblock.c 519行
if ((nf->fdump= open(dev->dump, FILE_FLAG)) < 0) 改为：
if ((nf->fdump= open(dev->dump, FILE_FLAG, 0777)) < 0)


编译错误2：
gcc  -g -O2   -o skyeye skyeye.o ./utils/libutils.a ./arch/arm/libarm.a ./device/libdev.a ./arch/mips/libmips.a ./arch/ppc/libppc.a ./arch/bfin/libbfin.a ./arch/mips/libmips.a ./arch/coldfire/libcoldfire.a -lc ./utils/libutils.a  -lbfd -lm -lc 
./arch/mips/libmips.a(decoder.o)：在函数‘decode’中：
/home/kolya/Downloads/skyeye-1.2.6_rc1/arch/mips/common/decoder.c:1079：对‘sign_extend_UInt32’未定义的引用
/home/kolya/Downloads/skyeye-1.2.6_rc1/arch/mips/common/decoder.c:1105：对‘sign_extend_UInt32’未定义的引用
/home/kolya/Downloads/skyeye-1.2.6_rc1/arch/mips/common/decoder.c:1049：对‘sign_extend_UInt32’未定义的引用
/home/kolya/Downloads/skyeye-1.2.6_rc1/arch/mips/common/decoder.c:1027：对‘sign_extend_UInt32’未定义的引用
/home/kolya/Downloads/skyeye-1.2.6_rc1/arch/mips/common/decoder.c:1013：对‘sign_extend_UInt32’未定义的引用
./arch/mips/libmips.a(decoder.o):/home/kolya/Downloads/skyeye-1.2.6_rc1/arch/mips/common/decoder.c:1001: 跟着更多未定义的参考到 sign_extend_UInt32
./arch/mips/libmips.a(decoder.o)：在函数‘decode’中：
/home/kolya/Downloads/skyeye-1.2.6_rc1/arch/mips/common/decoder.c:240：对‘divide_UInt32’未定义的引用
/home/kolya/Downloads/skyeye-1.2.6_rc1/arch/mips/common/decoder.c:231：对‘divide_Int32’未定义的引用
collect2: error: ld returned 1 exit status
Makefile:305: recipe for target 'skyeye' failed
make[2]: *** [skyeye] Error 1
make[2]: Leaving directory '/home/kolya/Downloads/skyeye-1.2.6_rc1'
Makefile:351: recipe for target 'all-recursive' failed
make[1]: *** [all-recursive] Error 1
make[1]: Leaving directory '/home/kolya/Downloads/skyeye-1.2.6_rc1'
Makefile:227: recipe for target 'all' failed
解决方法：
修改skyeye-1.2.6_rc1/arch/mips/common/decoder.c文件：
添加函数
UInt32 sign_extend_UInt32(UInt32 x, int s)
{
	return x + s;
}

skyeye-1.2.6_rc1/arch/mips/common/decoder.c:231行 注释掉divide_Int32(x, y);
skyeye-1.2.6_rc1/arch/mips/common/decoder.c:240行 注释掉divide_UInt32(x, y);

之后重新make即可编译出skyeye