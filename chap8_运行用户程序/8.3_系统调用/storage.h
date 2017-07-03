/*
storage.h:
Copyright (C) 2009  david leels <davidontech@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see http://www.gnu.org/licenses/.
*/

#ifndef __STORAGE_H__
#define __STORAGE_H__

#define MAX_STORAGE_DEVICE (2)
#define RAMDISK	0

typedef unsigned int size_t;
struct storage_device{
	unsigned int start_pos;
	size_t sector_size;
	size_t storage_size;
	int (*dout)(struct storage_device *sd,void *dest,unsigned int bias,size_t size);
	int (*din)(struct storage_device *sd,void *dest,unsigned int  bias,size_t size);
};

extern struct storage_device *storage[MAX_STORAGE_DEVICE];
extern int register_storage_device(struct storage_device *sd,unsigned int num);

#endif
