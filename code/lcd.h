#ifndef _LCD_H_
#define _LCD_H_

#include <sys/mman.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <linux/input.h>

static int fd;
static int fd_touch;
static unsigned char *pmap;

void open_ts(void);
void close_ts(void);
int get(int *x1, int *y1, int *push);

void init_bru(void);
void close_bru(void);
void show_bmp(char *bmp_patpname,int x_offset,int y_offset);

#endif