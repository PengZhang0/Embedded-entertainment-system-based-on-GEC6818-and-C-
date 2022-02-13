#include "2048game.h"
#include "photo.h"
#include "popstar.h"
#include "piano.h"

int x, y, push, key;
char file[20][100];
int file_num[3];

extern int map[11][11];
extern int count_now;//本次消灭个数
extern int total_score;//当前总分
extern int last_have;//最后剩余未消个数
extern int target_score;//本关目标分数
extern int level;//等级

void *pthread_get_ts(void * arg)
{
    while(1)
        key = get(&x,&y, &push);
}

int main(int argc, const char  *argv[])
{
	//初始化
	open_ts();
	init_bru();
	pthread_t thr;
    pthread_create(&thr,NULL,pthread_get_ts,NULL);
	
	show_bmp("./home.bmp",0,0);
	while(1){
		if(x > 415 && x < 535 && y > 95 && y < 225){
			act();
			game_2048();
			show_bmp("./home.bmp",0,0);
		}
		else if(x > 255 && x < 385 && y > 95 && y < 225){
			act();
			piano();
			show_bmp("./home.bmp",0,0);
		}
		else if(x > 415 && x < 535 && y > 230 && y < 390){
			act();
			photo();
			show_bmp("./home.bmp",0,0);
		}
		else if(x > 255 && x < 385 && y > 265 && y < 385){
			act();
			pop();
			show_bmp("./home.bmp",0,0);
		}
		else{ continue; }
	}
	close_ts();
	close_bru();
}

