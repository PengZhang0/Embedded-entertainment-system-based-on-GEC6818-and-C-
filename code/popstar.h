#ifndef _POP_H_
#define _POP_H_

#include<stdio.h>
#include<unistd.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>

#include"lcd.h"
	
int cal_score(int t);
int cal_target_score(int l);
int cal_bonous(int t);
int check_one(int (*p)[11],int i,int j);
int check_all(int (*p)[11]);
int init();
int show(int (*map)[11]);
int clean(int (*p)[11],int i,int j ,int real);
int down(int (*p)[11]);
int left(int (*p)[11]);
int play_game(int(*p)[11],int i,int j);
void pop(void);

#endif