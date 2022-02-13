#ifndef _2048GAME_H_
#define _2048GAME_H_
#define   NR    4   // 游戏的维数

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lcd.h"

void initGame(int data[NR][NR]);
void showGame(int data[NR][NR]);
void moveUp(int data[NR][NR]);
void moveDown(int data[NR][NR]);
void moveLeft(int data[NR][NR]);
void moveRight(int data[NR][NR]);
int checkGameOver(int data[NR][NR]);
int getInput(void);
void getRand(int data[NR][NR]);

int maxScore(int data[NR][NR]);
#endif


