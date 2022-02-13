#include "lcd.h"

static int fd;
static int fd_touch;
static unsigned char *pmap;

typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
#pragma pack(1)
typedef struct {			//bmp图片文件头信息封装 
	// 位图文件头 
	u8  bit_file_type[2];	//位图文件类型:'BM'->0x4d42 
	u32 file_size;	  		//整个文件大小 
	u16 reserved1;	  		//保留 
	u16 reserved2;	  		//保留 
	u32 offset;		  		//文件头到位图数据之间的偏移量 

	// 位图信息头 
	u32 head_size;			//位图信息头长度 
	u32 width;		  		//位图宽度 
	u32 height;		  		//位图高度 
	u16 bit_planes;	  		//位图位面数 
	u16 bits_per_pixel; 	//每个像素的位数 
	u32 compression;		//压缩说明 
	u32 image_size;			//位图数据大小 
	u32 h_res;				//水平分辨率 
	u32 v_res;				//垂直分辨率 
	u32 color_palette;		//位图使用的颜色索引数 
	u32 vip_color;			//重要的颜色索引数目 
}bmp_head;
#pragma pack()

void init_bru(void)
{
	fd = open ("/dev/fb0", O_RDWR);
	if(fd == -1){
		perror("open error!");
		return;
	}

	pmap = mmap(NULL, 800*480*4, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(pmap == MAP_FAILED){
		perror("map error!");
		close(fd);
		return;
	}
}

void close_bru(void)
{
	munmap(pmap,800*480*4);
	close(fd);
}

void show_bmp(char *bmp_patpname,int x_offset,int y_offset)
{
	int bmp_fd = open(bmp_patpname, O_RDONLY);
	if(bmp_fd == -1)
	{
		perror("打开bmp图片失败");
		return ;
	}

	//读取图片头部信息
	bmp_head myhead;
	read(bmp_fd, &myhead, sizeof(bmp_head));

	//如果每一行字节数能被4整除，n为0，否则是多出来的字节数
	int n = ((myhead.width*3)%4==0) ? 0 : 4 -(myhead.width*3)%4;	

	//申请并清空缓冲区
	char tmp_buf[(myhead.width*3+n)*myhead.height];
	bzero(tmp_buf,sizeof(tmp_buf));
	
	//读取图片数据
	read(bmp_fd, tmp_buf, sizeof(tmp_buf));
	close(bmp_fd);
	
	//将数据存入映射内存
	int i,j;
	for(i=0; i<myhead.height; i++)
		for(j=0; j<myhead.width; j++)
		{
			*(pmap+((i+y_offset)*800+j+x_offset)*4) = tmp_buf[((myhead.height-1-i)*myhead.width+j)*3-i*n];
			*(pmap+((i+y_offset)*800+j+x_offset)*4+1) = tmp_buf[((myhead.height-1-i)*myhead.width+j)*3+1-i*n];
			*(pmap+((i+y_offset)*800+j+x_offset)*4+2) = tmp_buf[((myhead.height-1-i)*myhead.width+j)*3+2-i*n];
			*(pmap+((i+y_offset)*800+j+x_offset)*4+3) = 0x00;
		}
	
}


void show_bmp_center(char *bmp_patpname)
{
	int x_offset,y_offset;
	/*向lcd文件中写入像素点数据*/
	//打开bmp图片
	int  bmp_fd = open(bmp_patpname, O_RDONLY);//完整路径 /mnt/hgfs/shear/day004/1.bmp
	if(bmp_fd == -1)
	{
		perror("打开bmp图片失败");
		return ;
	}
	
	//读取图片头部信息
	bmp_head myhead;
	read(bmp_fd, &myhead, sizeof(bmp_head));
	
	//申请缓冲区
	char tmp_buf[myhead.width*myhead.height*3];
	//清空缓冲区
	bzero(tmp_buf,sizeof(tmp_buf));
	
	//读取图片数据
	read(bmp_fd, tmp_buf, sizeof(tmp_buf));
	//关闭图片文件
	close(bmp_fd);
	//将数据存入映射内存
	//将数据存入映射内存
	int i,j;

	x_offset=400-myhead.width/2;
	y_offset=240-myhead.height/2;
	for(i=0; i<myhead.height; i++)
		for(j=0; j<myhead.width; j++)
		{
			*(pmap+((i+y_offset)*800+j+x_offset)*4) = tmp_buf[((myhead.height-1-i)*myhead.width+j)*3];
			*(pmap+((i+y_offset)*800+j+x_offset)*4+1) = tmp_buf[((myhead.height-1-i)*myhead.width+j)*3+1];
			*(pmap+((i+y_offset)*800+j+x_offset)*4+2) = tmp_buf[((myhead.height-1-i)*myhead.width+j)*3+2];
			*(pmap+((i+y_offset)*800+j+x_offset)*4+3) = 0x00<<24;
		}
	
}

void open_ts(void)
{
	fd_touch = open("/dev/input/event0", O_RDONLY);
	if(fd_touch == -1)
	{
		perror("open ts failed");
		return ;
	}
}

void close_ts(void)
{
	close(fd_touch);
}

int get(int *x1, int *y1, int *push)
{
	struct input_event ts_buf;
	char x_flag=0,y_flag=0;
	int fx, fy;
	int lx, ly;
	int x_now, y_now;
	int press;
	
	read(fd_touch, &ts_buf, sizeof(ts_buf));
	//判断事件类型
	if(ts_buf.type == EV_ABS)
	{
		//判断事件代号
		if(ts_buf.code == ABS_X)
		{
			x_now = ts_buf.value;
			*x1 = x_now;
		}
		if(ts_buf.code == ABS_Y)
		{
			y_now = ts_buf.value;
			*y1 = y_now;
		}
	}
	else if(ts_buf.type==EV_KEY && ts_buf.code==BTN_TOUCH)
	{
		press = ts_buf.value;
		*push = press;
		if(ts_buf.value == 1)	fx = x_now, fy = y_now;
		else{
			lx = x_now, ly = y_now;
			if(ly - fy < -80)	return 1;		//up
			else if(ly - fy > 80)	return 2;	//down
			else if(lx - fx < -80)	return 3;	//left
			else if(lx - fx > 80)	return 4;	//right
			else	return 0;					//no action
		}
	}
}
