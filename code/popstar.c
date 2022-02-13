#include "popstar.h"

extern int x;
extern int y;
extern int push;

int map[11][11];
int count_now;//本次消灭个数
int total_score;//当前总分
int last_have;//最后剩余未消个数
int target_score;//本关目标分数
int level;//等级

int cal_score(int t)//根据消除的个数决定分数
{
	return t*(t*5);
}

int cal_target_score(int l)
{
	if(l<=5)
		target_score+=2000;
	else if(l<=10)
		target_score+=3000;
	else if(l<=15)
		target_score+=3500;
	else 
		target_score+=4000;
	return 0;
}

int cal_bonous(int t)
{
	if(t>=10)
		return 0;
	else
		return 2000-t*t*20;
}

int check_one(int (*p)[11],int i,int j)//检查单个点是否符合消除的条件
{
	int flag=0;
	if(i<0||i>=10||j<0||j>=10||map[i][j]==-1)
		return 0;
	if(i-1>=0&&map[i-1][j]==map[i][j])
		flag=1;
	if(flag||(j+1<10&&map[i][j+1]==map[i][j]))
		flag=1;
	if(flag||(i+1<10&&map[i+1][j]==map[i][j]))
		flag=1;
	if(flag||(j-1>=0&&map[i][j-1]==map[i][j]))
		flag=1;
	return flag;
}

int check_all(int (*p)[11])
{
	int i,j;
	for(i=9;i>=0;i--)
		for(j=0;j<10;j++)
			if(check_one(p,i,j))
				return 1;
		return 0;
}

int init()///init
{
	int i,j;
	srand(time(NULL)); 
	for(i=0;i<10;i++)
		for(j=0;j<10;j++)
			map[i][j]=rand()%5;
	return 0;
}

int show(int (*map)[11])
{
	int i,j;
	for(i=0;i<10;i++)
	{
	for(j=0;j<10;j++)
		switch(map[i][j])
		{
			case -1:show_bmp("./popstar/blank.bmp",40*j+200,40*i+40);break;
			case 0:show_bmp("./popstar/redstar.bmp",40*j+200,40*i+40);break;
			case 1:show_bmp("./popstar/bluestar.bmp",40*j+200,40*i+40);break;
			case 2:show_bmp("./popstar/greenstar.bmp",40*j+200,40*i+40);break;
			case 3:show_bmp("./popstar/yellowstar.bmp",40*j+200,40*i+40);break;
			case 4:show_bmp("./popstar/pinkstar.bmp",40*j+200,40*i+40);break;
		}
	}
	return 0;
}

int clean(int (*p)[11],int i,int j ,int real)
{
	if(i<0||i>=10||j<0||j>=10)//其实没必要，但是效率要高一些
	return 0;
	if(i-1>=0&&map[i-1][j]==real)
	{  count_now++;map[i-1][j]=-1; clean(p,i-1,j,real); }
	if((j+1<10&&map[i][j+1]==real))
	{count_now++; map[i][j+1]=-1; clean(p,i,j+1,real); }
	if((i+1<10&&map[i+1][j]==real))
	{count_now++; map[i+1][j]=-1; clean(p,i+1,j,real); }
	if((j-1>=0&&map[i][j-1]==real))
	{ count_now++; map[i][j-1]=-1; clean(p,i,j-1,real); }
	return 0;
}

int down(int (*p)[11])//上面的下来
{
	int i,j,c;
	for(j=0;j<10;j++)
	{
		c=0;
		for(i=9;i>=0;i--)
		{
			if(p[i][j]==-1)
			c++;
			else
			p[i+c][j]=p[i][j];
		}
			for(i=0;i<c;i++)
			p[i][j]=-1;
		}
	return 0;
}

int left(int (*p)[11])//向左看齐
//在向下对齐之后向右就简单了
{
	int i=9,j=0,c=0;
	int x1;
	for(j=0;j<10;j++)
	{
		if(p[i][j]==-1)
		c++;
		else
		for(x1=0;x1<10;x1++)
			p[x1][j-c]=p[x1][j];
	}
	for(j=0;j<c;j++)
		for(i=0;i<10;i++)
			p[i][10-j-1]=-1;
	return 0;
}

int play_game(int(*p)[11],int i,int j)//play
{
	show(p);
	printf("i:%d,j:%d\n",i,j);
        i = 9-i;
	if(check_one(p,i,j))
	{  printf("输入OK\n"); clean(p,i,j,p[i][j]);down(p); left(p); } 
	else 
		printf("输入不合法，不符合条件\n");
	return 0;
}


void pop(void)
{
	int flag_go_on=1;//判断是否继续
	target_score=1000;
	level=1;

again:	show_bmp("./popstar/popstart.bmp",0,0);
	while(flag_go_on){
		printf("begin new !\n\n\n\n");
		init();
		last_have=100;
		while(1)
		{
			if(x>700 && y<55)	//退出
			{
				return;
			}
				count_now=0;
				if(push == 1){
				play_game(map,11-(y/40),(x/40)-5); 
				printf("clean star num:%d ,add:%d ,total:%d\n,level:%d ,target score:%d\n",count_now,cal_score(count_now),total_score,level,target_score);
				}
				total_score+=cal_score(count_now);
				last_have-=count_now;
				if(!check_all(map))
				{
				total_score+=cal_bonous(last_have);
					if(total_score>=target_score)
					{
						flag_go_on=1;
						level++;
						cal_target_score(level);
					}
					else
					{ 
						flag_go_on=0;
						show_bmp("./2048/gameover.bmp",0, 0);
						sleep(2);
						goto again;
					}
					printf("last_have:%d ,bonus:%d,total:%d\n",last_have,cal_bonous(last_have),total_score);
					break;
				}		
		}
		show(map);
		sleep(10);
		}
	return ;
}