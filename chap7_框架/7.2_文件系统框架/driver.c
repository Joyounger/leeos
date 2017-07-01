/*
driver.c:
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

#include "storage.h"

struct storage_device *storage[MAX_STORAGE_DEVICE];

int register_storage_device(struct storage_device *sd,unsigned int num){
	if(num>MAX_STORAGE_DEVICE)
		return -1;

	if(storage[num]){
		return -1;
	}else{
		storage[num]=sd;
	}
	return 0;
};
