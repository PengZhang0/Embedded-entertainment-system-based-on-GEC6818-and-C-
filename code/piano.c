#include "piano.h"

extern int x;
extern int y;
extern int push;

void piano(void)
{
    int n,last_n;//键值、上次的键值，也就是按下的哪个按键
    char buf[64];//拼接用
    int vol=0;//音量
    int mot=1; //模式，主题
    //显示界面
	
    show_bmp("./piano/bmp1/background.bmp",0,0);
    while(1)
    {
        if(push == 1 && y>55 && y<320)//如果触摸屏按下
        {
            for(n=0; n<12; n++){//看一下是按下的哪个按键
                if(x>n*66 && x<(n+1)*66 && last_n!=n){
                sprintf(buf,"madplay -A %d ./piano/mp3%d/d%d.mp3 &",vol,mot,n+1);
                system("killall -9 madplay");
                system(buf);//播放相应音频
                sprintf(buf,"./piano/bmp%d/key_on.bmp",mot);
                show_bmp(buf,n*66,48);//显示按键按下图片
                
                if(last_n != -1){
                    sprintf(buf,"./piano/bmp%d/key_off.bmp",mot);
                    show_bmp(buf,last_n*66,48);//显示松开图片
                }
                last_n = n;
                break;
                }
            }
        }
        else if(push == 0)//如果触摸屏松开
        {
            last_n = -1;
            for(n=0; n<12; n++){//把按键都复原
            sprintf(buf,"./piano/bmp%d/key_off.bmp",mot);
            show_bmp(buf,n*66,48);
            }
        }
        else if(x>635 && x<690 && y>375 && y<435)//音量按键减小
        {
            if(vol>-100)vol--;usleep(50000);printf("%d--\n",vol);
        }
        else if(x>691 && x<750 && y>375 && y<435)//增大
        {
			if(vol<18)vol++;usleep(50000);printf("%d++\n",vol);
        }
        else if(x>55 && x<115 && y>375 && y<435)
        {
            sleep(1);
            mot++;if(mot==3)mot=1;//主题
        }
        else if(x>700 && y<55)
        {
            return;
        }
    }
}
