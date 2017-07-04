// date:17.4.10
// author: linyang <942510346@qq.com>


#include "string.h"

#define MAX_SUPER_BLOCK 8
#define NULL 			(void *)0


struct super_block *fs_type[MAX_SUPER_BLOCK];

int register_file_system(struct super_block *type, unsigned int id)
{
	if(fs_type[id] == NULL) {
		fs_type[id] = type;
		return 0;
	}

	return -1;
}

void unregister_file_system(struct super_block *type, unsigned int id)
{
	fs_type[id] = NULL;
}
