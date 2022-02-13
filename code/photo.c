#include "photo.h"

extern int x;
extern int y;
extern int push;
extern int key;

char file[20][100];
int file_num[3];

int get_photo_file(void)
{
	DIR* dir;
	struct dirent* ptr;
	int i=0,j=0;
	dir=opendir("./photo");
	while((ptr=readdir(dir))!=NULL)
	{
		if(NULL!=strstr(ptr->d_name,".bmp"))
		{
			//拼接字符串
			sprintf(file[i],"./photo/%s",ptr->d_name);
			i++;
		}
	}
	closedir(dir);
	return i;
}

void act(void)
{
	show_bmp("./act/wait1.bmp",0,0);
	usleep(40000);
	show_bmp("./act/wait2.bmp",0,0);
	usleep(40000);
	show_bmp("./act/wait3.bmp",0,0);
	usleep(40000);
	show_bmp("./act/wait4.bmp",0,0);
	usleep(40000);
	show_bmp("./act/wait5.bmp",0,0);
	usleep(60000);
}


void photo(void)
{
	int photo_count_now;//记录当前图片
	int times;
	photo_count_now=10;//记录当前图片
	file_num[0]=get_photo_file();
	
	show_bmp("./photo.bmp",0,0);
	while(1){
		if(key == 3 && push == 0){
			photo_count_now--;
			if(photo_count_now<0)
				photo_count_now=file_num[0]-1;
			printf("当前序号 : %d \n",photo_count_now);
			printf("图片文件 : %s \n",file[photo_count_now]);
			show_bmp(file[photo_count_now], 100, 63);
		}
		else if(key == 4 && push == 0){
			photo_count_now++;
			if(photo_count_now>file_num[0]-1)
				photo_count_now=0;
			printf("当前序号 : %d \n",photo_count_now);
			printf("图片文件 : %s \n",file[photo_count_now]);
			show_bmp(file[photo_count_now], 100, 63);
		}
		else if(x>700 && y<55)	//退出
        {
            return;
        }
	}
}