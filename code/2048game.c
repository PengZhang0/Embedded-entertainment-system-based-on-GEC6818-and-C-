#include "2048game.h"

extern int x;
extern int y;
extern int key;
void initGame(int data[NR][NR])
{
    int x1, y1;

	show_bmp("./2048/background.bmp", 0, 0);//背景板
    for (y1 = 0; y1 < NR; y1++)
    {
        for (x1 = 0; x1 < NR; x1++)
		{
		    data[y1][x1] = 0;		 // 所有数据清零
		}
    }

    /* 游戏上随机产生两个数 */
    srand(time(NULL));           // 设置随机数种子
    getRand(data);
    getRand(data);
}

/*
 * 函数名：showGame
 * 功能：显示游戏界面
 * 参数：需要显示的游戏数据
 * 返回值：无
*/
void showGame(int data[NR][NR])
{
    int x1, y1;

	/* 打印所有数据 */
    for (y1 = 0; y1 < NR; y1++)
    {
        for (x1 = 0; x1 < NR; x1++)
		{
	    	if (data[y1][x1] == 0)
	    	{
	        	show_bmp("./2048/item.bmp", 90*x1 + 240,90*y1 + 80);
	    	}
	    	else
	    	{
				switch (data[y1][x1])	// 根据不同数字打印不同颜色
				{
				case 2   : show_bmp("./2048/color_x80_2.bmp",    90*x1 + 240,90*y1 + 80); break;
				case 4   : show_bmp("./2048/color_x80_4.bmp",    90*x1 + 240,90*y1 + 80); break;
				case 8   : show_bmp("./2048/color_x80_8.bmp",    90*x1 + 240,90*y1 + 80); break;
				case 16  : show_bmp("./2048/color_x80_16.bmp",   90*x1 + 240,90*y1 + 80); break;
				case 32  : show_bmp("./2048/color_x80_32.bmp",   90*x1 + 240,90*y1 + 80); break;
				case 64  : show_bmp("./2048/color_x80_64.bmp",   90*x1 + 240,90*y1 + 80); break;
				case 128 : show_bmp("./2048/color_x80_128.bmp",  90*x1 + 240,90*y1 + 80); break;
				case 256 : show_bmp("./2048/color_x80_256.bmp",  90*x1 + 240,90*y1 + 80); break;
				case 512 : show_bmp("./2048/color_x80_512.bmp",  90*x1 + 240,90*y1 + 80); break;
				case 1024: show_bmp("./2048/color_x80_1024.bmp", 90*x1 + 240,90*y1 + 80); break;
				case 2048: show_bmp("./2048/color_x80_2048.bmp", 90*x1 + 240,90*y1 + 80); break;
				}
	    	}
		}
    }
}

void moveUp(int data[NR][NR])
{
    int x1, y1;
    int idx;
    int isChange = 0;	// 可移动标记位

    /* 先累加 */
    for (x1 = 0; x1 <= NR-1; x1++)
    {
        for (y1 = 0; y1 < NR-1; y1++)
		{
		    if (data[y1][x1] == 0)
		    {
		        continue;
		    }
		    /* 查找是否可加，能加则加 */
		    for (idx = y1+1; idx <= NR-1; idx++)
		    {
		        if (data[idx][x1] == 0)
				{
				    continue;
				}
				else if (data[idx][x1] != data[y1][x1])
				{
				    break;
				}
				else
				{
				    data[y1][x1]  += data[idx][x1];
				    data[idx][x1] = 0;
				    isChange = 1;
				    break;
				}
		    }
		}
    }

    /* 累加完后移动 */
    for (x1 = 0; x1 <= NR-1; x1++)
    {
        for (y1 = 1; y1 <= NR-1; y1++)
		{
		    if (data[y1][x1] == 0)
		    {
		        continue;
		    }

		    /* 寻找移动点 */
    	    idx = y1-1;
		    while (data[idx][x1] == 0 && idx >= 0)
		    {
		        idx--;
		    }

    	    if (data[idx+1][x1] == 0)
		    {
		        data[idx+1][x1] = data[y1][x1];
		        data[y1][x1] = 0;
		        isChange = 1;
		    }
		}
    }

	/* 成功移动之后需要随即产生一个数 */
    if (isChange == 1)
    {
        getRand(data);
    }
}


void moveDown(int data[NR][NR])
{
    int x1, y1;
    int idx;
    int isChange = 0;   // 可移动标记位

    /* 先累加 */
    for (x1 = 0; x1 <= NR-1; x1++)
    {
        for (y1 = NR-1; y1 >= 1; y1--)
    	{
    	    if (data[y1][x1] == 0)
    	    {
    	        continue;
    	    }
    	    /* 查找是否可加，能加则加 */
    	    for (idx = y1-1; idx >= 0; idx--)
    	    {
    	        if (data[idx][x1] == 0)
        		{
        		    continue;
        		}
        		else if (data[idx][x1] != data[y1][x1])
        		{
        		    break;
        		}
        		else
        		{
        		    data[y1][x1]  += data[idx][x1];
        		    data[idx][x1] = 0;
        		    isChange = 1;
        		    break;
        		}
    	    }
    	}
    }
    /* 累加完后移动 */
    for (x1 = 0; x1 <= NR-1; x1++)
    {
        for (y1 = NR-2; y1 >= 0; y1--)
    	{
    	    if (data[y1][x1] == 0)
    	    {
    	        continue;
    	    }
    	    /* 寻找移动点 */
    	    idx = y1+1;
    	    while (data[idx][x1] == 0 && idx <= NR-1)
    	    {
    	        idx++;
    	    }

    	    if (data[idx-1][x1] == 0)
    	    {
        		data[idx-1][x1] = data[y1][x1];
        		data[y1][x1] = 0;
        		isChange = 1;
    	    }
    	}
    }

    /* 成功移动之后需要随即产生一个数 */
    if (isChange == 1)
    {
        getRand(data);
    }
}

/*
 * 函数名：moveRight
 * 功能：把游戏数据右移
 * 参数：需要右移的游戏数据
 * 返回值：无
*/
void moveRight(int data[NR][NR])
{
    int x1, y1;
    int idx;
    int isChange = 0;   // 可移动标记位

    /* 先累加 */
    for (y1 = 0; y1 < NR; y1++)
    {
        for (x1 = NR-1; x1 >= 0; x1--)
    	{
    	    if (data[y1][x1] == 0)
    	    {
    	        continue;
    	    }
    	    /* 查找是否可加，能加则加 */
    	    for (idx = x1-1; idx >= 0; idx--)
    	    {
    	        if (data[y1][idx] == 0)
        		{
        		    continue;
        		}
        		else if (data[y1][idx] != data[y1][x1])
        		{
        		    break;
        		}
        		else
        		{
        		    data[y1][x1]  += data[y1][x1];
        		    data[y1][idx] = 0;
        		    isChange = 1;
        		    break;
        		}
    	    }
    	}
    }
    /* 累加完后移动 */
    for (y1 = 0; y1 < NR; y1++)
    {
        for (x1 = NR-2; x1 >= 0; x1--)
    	{
    	    if (data[y1][x1] == 0)
    	    {
    	        continue;
    	    }
    	    /* 寻找移动点 */
    	    idx = x1+1;
    	    while (data[y1][idx] == 0 && idx <= NR-1)
    	    {
    	        idx++;
    	    }

      	    if (data[y1][idx-1] == 0)
    	    {
    	        data[y1][idx-1] = data[y1][x1];
    	        data[y1][x1] = 0;
    	        isChange = 1;
    	    }
    	}
    }

    /* 成功移动之后需要随即产生一个数 */
    if (isChange == 1)
    {
        getRand(data);
    }
}

/*
 * 函数名：moveLeft
 * 功能：把游戏数据左移
 * 参数：需要左移的游戏数据
 * 返回值：无
*/
void moveLeft(int data[NR][NR])
{
    int x1, y1;
    int idx;
    int isChange = 0;   // 可移动标记位

    /* 先累加 */
    for (y1 = 0; y1 <= NR-1; y1++)
    {
        for (x1 = 0; x1 < NR-1; x1++)
    	{
    	    if (data[y1][x1] == 0)
    	    {
    	        continue;
    	    }
    	    /* 查看是否可加，能加则加 */
    	    for (idx = x1+1; idx <= NR-1; idx++)
    	    {
    	        if (data[y1][idx] == 0)
        		{
        		    continue;
        		}
        		else if (data[y1][idx] != data[y1][x1])
        		{
        		    break;
        		}
        		else
        		{
        		    data[y1][x1]  += data[y1][idx];
        		    data[y1][idx] = 0;
        		    isChange = 1;
        		    break;
        		}
    	    }
    	}
    }
    /* 累加完后移动 */
    for (y1 = 0; y1 <= NR-1; y1++)
    {
        for (x1 = 1; x1 <= NR-1; x1++)
    	{
    	    if (data[y1][x1] == 0)
    	    {
    	        continue;
    	    }
    	    /* 寻找移动点 */
    	    idx = x1-1;
    	    while (data[y1][idx] == 0 && idx >= 0)
    	    {
    	        idx--;
    	    }

    	    if (data[y1][idx+1] == 0)
    	    {
    	        data[y1][idx+1] = data[y1][x1];
    	        data[y1][x1] = 0;
    	        isChange = 1;
    	    }
    	}
    }

    /* 成功移动之后需要随即产生一个数 */
    if (isChange == 1)
    {
        getRand(data);
    }
}
/*
 * 函数名：checkGameOver
 * 功能：检查游戏是否结束
 * 参数：需要检查的游戏数据
 * 返回值：游戏结束返回1，没有结束返回0
*/
int checkGameOver(int data[NR][NR])
{
    int x1, y1;

    /* 判断有无空位0 */
    for (y1 = 0; y1 < NR; y1++)
    {
        for (x1 = 0; x1 < NR; x1++)
    	{
    	    if (data[y1][x1] == 0)
    	    {
    	        return 0;
    	    }
    	}
    }
    /* 判断各行是否可加 */
    for (y1 = 0; y1 < NR; y1++)
    {
        for (x1 = 0; x1 < NR-1; x1++)
    	{
    	    if (data[y1][x1] == data[y1][x1+1])
    	    {
    	        return 0;
    	    }
    	}
    }
    /* 判断各列是否可加 */
    for (x1 = 0; x1 < NR; x1++)
    {
        for (y1 = 0; y1 < NR-1; y1++)
    	{
    	    if (data[y1][x1] == data[y1+1][x1])
    	    {
    	       return 0;
    	    }
    	}
    }
    /* 游戏结束 */
    return 1;
}


/*
 * 函数名：getRand
 * 功能：在游戏数据中产生一个随机数，2的概率为80%，4的概率为20%
 * 参数：需要产生随机数的游戏数据
 * 返回值：无
*/
void getRand(int data[NR][NR])
{
    int x1, y1;
    int idx;  /* 随机种子索引 */

    /* 全局查找是否有空位产生随机数 */
    while (1)
    {
        /* 随即定位 */
        x1 = rand() % NR;
        y1 = rand() % NR;

        /* 定位的位置有数了 */
        if (data[y1][x1] != 0)
    	    continue;

        /* 空白位置产生数 */
        idx = rand() % 10;
    	data[y1][x1] = 2;

        return;
    }
}

/*
 * 函数名：maxScore
 * 功能：获取游戏最高分
 * 参数：需要获取最高分的游戏数据
 * 返回值：返回游戏数据中的最大值
*/
int maxScore(int data[NR][NR])
{
    int x1, y1;
    int maxValue = 0;

    for (y1 = 0; y1 < NR; y1++)
    {
        for (x1 = 0; x1 < NR; x1++)
    	{
    	    if (maxValue < data[y1][x1])
    	    {
    	        maxValue = data[y1][x1];
    	    }
    	}
    }

    return maxValue;
}


void game_2048()
{
	int gameData[NR][NR];	// 游戏数据
    int isGameOver = 0;		// 游戏结束标志位
    //int key;				// 用户的按键输入
	

    /* 初始化游戏 */
again:    initGame(gameData);
	showGame(gameData);

    /* 进入游戏 */
	while(1)
	{
		//key = get();//屏幕手势输入
		switch (key)
		{
		    case 1 : moveUp(gameData);    break;
		    case 2 : moveDown(gameData);  break;
    	    case 3 : moveLeft(gameData);  break;
		    case 4 : moveRight(gameData); break;
		    case 0: continue;
		}
		showGame(gameData);

		isGameOver = checkGameOver(gameData);
		if (isGameOver)
		{
			show_bmp("./2048/gameover.bmp",0, 0);
			sleep(2);
			goto again;
		}
		if(x>700 && y<55)	return;
    }
}