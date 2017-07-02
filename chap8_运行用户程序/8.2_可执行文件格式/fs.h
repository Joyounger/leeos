// date:17.4.10
// author: linyang <942510346@qq.com>


#include "storage.h"

#define MAX_SUPER_BLOCK	(8)

#define ROMFS	0

struct super_block;


struct inode {
	char *name;
	unsigned int flags;
	size_t dsize;				//file data size
	unsigned int daddr;			//real data bias inside the block device
	struct super_block *super;
	
};

struct super_block {
	struct inode *(*namei)(struct super_block *super,char *p);
	unsigned int (*get_daddr)(struct inode *);
	
	struct storage_device *device;
	char *name;
};

extern struct super_block *fs_type[];
