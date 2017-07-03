// date:17.4.10
// author: linyang <942510346@qq.com>


#include "fs.h"
#include "storage.h"
#include "string.h"

#define NULL (void *)0

#define be32_to_le32(x) \
	((unsigned int)( \
		(((unsigned int)(x) & (unsigned int)0x000000ffUL) << 24) | \
		(((unsigned int)(x) & (unsigned int)0x0000ff00UL) <<  8) | \
		(((unsigned int)(x) & (unsigned int)0x00ff0000UL) >>  8) | \
		(((unsigned int)(x) & (unsigned int)0xff000000UL) >> 24) ))

struct romfs_super_block {
	unsigned int word0;
	unsigned int word1;
	unsigned int size;
	unsigned int checksum;
	char name[0];
};

struct romfs_inode {
	unsigned int next;
	unsigned int spec;
	unsigned int size;
	unsigned int checksum;
	char name[0];
};

struct super_block romfs_super_block;

#define ROMFS_MAX_FILE_NAME	(128)
#define ROMFS_NAME_ALIGN_SIZE	(16)
#define ROMFS_SUPER_UP_MARGIN	(16)
#define ROMFS_NAME_MASK	(~(ROMFS_NAME_ALIGN_SIZE-1))
#define ROMFS_NEXT_MASK 0xfffffff0

#define romfs_get_first_file_header(p)	((((strlen(((struct romfs_inode *)(p))->name)+ROMFS_NAME_ALIGN_SIZE+ROMFS_SUPER_UP_MARGIN))&ROMFS_NAME_MASK)<<24)
#define romfs_get_file_data_offset(p,num)	(((((num)+ROMFS_NAME_ALIGN_SIZE)&ROMFS_NAME_MASK)+ROMFS_SUPER_UP_MARGIN+(p)))



static char *bmap(char *tmp,char *dir){
	unsigned int n;
	char *p=strchr(dir,'/');
	if(!p){
		strcpy(tmp,dir);
		return NULL;
	}
	n=p-dir;
	n=(n>ROMFS_MAX_FILE_NAME)?ROMFS_MAX_FILE_NAME:n;
	strncpy(tmp,dir,n);
	return p+1;
}

static char *get_the_file_name(char *p,char *name){
	char *tmp=p;
	int index;
	for(index=0;*tmp;tmp++){
		if(*tmp=='/'){
			index=0;
			continue;
		}else{
			name[index]=*tmp;
			index++;
		}
	}
	name[index]='\0';
	return name;
}

struct inode *simple_romfs_namei(struct super_block *block,char *dir){
	struct inode *inode;
	struct romfs_inode *p;
	unsigned int tmp,next,num;
	char name[ROMFS_MAX_FILE_NAME],fname[ROMFS_MAX_FILE_NAME];
	unsigned int max_p_size=(ROMFS_MAX_FILE_NAME+sizeof(struct romfs_inode));
	max_p_size=max_p_size>(block->device->sector_size)?max_p_size:(block->device->sector_size);
	get_the_file_name(dir,fname);
	if((p=(struct romfs_inode *)kmalloc(max_p_size,0))==NULL){
		goto ERR_OUT_NULL;
	}
	dir=bmap(name,dir);
	if(block->device->dout(block->device,p,0,block->device->sector_size))
		goto ERR_OUT_KMALLOC;
	next=romfs_get_first_file_header(p);

	while(1){
		tmp=(be32_to_le32(next))&ROMFS_NEXT_MASK;
		if(tmp>=block->device->storage_size)
			goto ERR_OUT_KMALLOC;
		if(tmp!=0){
			if(block->device->dout(block->device,p,tmp,block->device->sector_size)){
				goto ERR_OUT_KMALLOC;
			}
			if(!strcmp(p->name,name)){
				if(!strcmp(name,fname)){
					goto FOUND;
				}else{
					dir=bmap(name,dir);
					next=p->spec;	
					if(dir==NULL){
						goto FOUNDDIR;
					}
				}
			}else{
				next=p->next;	
			}
		}else{
			goto ERR_OUT_KMALLOC;
		}
	}

FOUNDDIR:
	while(1){
		tmp=(be32_to_le32(next))&ROMFS_NEXT_MASK;

		if(tmp!=0){
			if(block->device->dout(block->device,p,tmp,block->device->sector_size)){
				goto ERR_OUT_KMALLOC;
			}

			if(!strcmp(p->name,name)){
				goto FOUND;
			}else{
				next=p->next;
			}
		}else{
			goto ERR_OUT_KMALLOC;
		}
	}

FOUND:
	if((inode = (struct inode *)kmalloc(sizeof(struct inode), 0))==NULL){
		goto ERR_OUT_KMALLOC;
	}
	num=strlen(p->name);				
	if((inode->name=(char *)kmalloc(num,0))==NULL){
		goto ERR_OUT_KMEM_CACHE_ALLOC;
	}
	strcpy(inode->name,p->name);	
	inode->dsize=be32_to_le32(p->size);
	inode->daddr=tmp;			
	inode->super=&romfs_super_block;
	kfree(p);		
	return inode;

ERR_OUT_KMEM_CACHE_ALLOC:
	kfree(inode);
ERR_OUT_KMALLOC:
	kfree(p);
ERR_OUT_NULL:
	return NULL;
}


unsigned int romfs_get_daddr(struct inode *node){
	int name_size=strlen(node->name);
	return romfs_get_file_data_offset(node->daddr,name_size);
}

struct super_block romfs_super_block={
	.namei=simple_romfs_namei,
	.get_daddr=romfs_get_daddr,
	.name="romfs",
};


int romfs_init(void){
	int ret;
	ret=register_file_system(&romfs_super_block,ROMFS);
	romfs_super_block.device=storage[RAMDISK];
	return ret;
}
