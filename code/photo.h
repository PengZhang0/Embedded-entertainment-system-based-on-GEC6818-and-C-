#ifndef _PHOTO_H_
#define _PHOTO_H_

#include "lcd.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <string.h>
#include <sys/mman.h>	
#include <linux/input.h>

int get_photo_file(void);
void act(void);
void photo(void);

#endif