#include "ws2812.h"
#include "stdint.h"
#include "math.h"

uint8_t LED_Buff[17][3]={{10,10,10},{10,10,10},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
                        {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
//-------------------------------------------------------------------------------
//子程序名称:IO_Init(void)
//功能：端口初始化
//-------------------------------------------------------------------------------
void WS2812_Init(void)
{
    gpio_init(WS2812_DIN, GPO, 0, PUSHPULL);
    RGB_Data_Init();
    ResetDataFlow();
}

//-------------------------------------------------------------------------------
//子程序名称:ResetDateFlow(void)
//功能：复位，为下一次发送做准备，
//说明：将DI置位为0后，延时约65us
//-------------------------------------------------------------------------------
void ResetDataFlow(void)
{
	unsigned char i,j;
	DI0;					//DI置为0后，延时50us以上，实现帧复位
	IfxStm_waitTicks(&MODULE_STM0, 1);//200ns
}
//-------------------------------------------------------------------------------
//子程序名称:SendOnePix(unsigned char *ptr)
//功能：发送一个像素点的24bit数据
//参数：接收的参数是一个指针，此函数会将此指针指向的地址的连续的三个Byte的数据发送
//说明：在主函数中直接调用此函数时，在整个帧发送开始前需要先执行 ResetDataFlow()
//		数据是按归零码的方式发送，速率为800KBPS
//-------------------------------------------------------------------------------
void SendOnePix(uint8_t *ptr)
{
	unsigned char i,j;
	uint8_t temp;

	for(j=0;j<3;j++)
	{
		temp=ptr[j];
		for(i=0;i<8;i++)
		{
			if(temp&0x80)		 //从高位开始发送
			{
				DI1;			 //发送“1”码
//				systick_delay_ns(STM0, 700);
				IfxStm_waitTicks(&MODULE_STM0, 1);//700ns
                IfxStm_waitTicks(&MODULE_STM0, 1);
                IfxStm_waitTicks(&MODULE_STM0, 1);
                IfxStm_waitTicks(&MODULE_STM0, 1);
				DI0;
//				systick_delay_ns(STM0, 600);
				IfxStm_waitTicks(&MODULE_STM0, 30);//600ns
			}
			else				//发送“0”码
			{
				DI1;
//				systick_delay_ns(STM0, 350);
				IfxStm_waitTicks(&MODULE_STM0, 10);//300ns

				DI0;
//				systick_delay_ns(STM0, 800);
				IfxStm_waitTicks(&MODULE_STM0, 50);//800ns
			}
			temp=(temp<<1);		 //左移位
		}
	}
}
//-------------------------------------------------------------------------------
//子程序名称:SendOneFrame(unsigned char *ptr)
//功能：发送一帧数据（即发送整个数组的数据）
//参数：接收的参数是一个指针，此函数会将此指针指向的地址的整个数组的数据发送
//-------------------------------------------------------------------------------
void SendOneFrame(uint8_t *ptr)
{
	unsigned char k;

	ResetDataFlow();				 //发送帧复位信号

	for(k=0;k<SNUM;k++)				 //发送一帧数据，SNUM是板子LED的个数
	{
		SendOnePix(&ptr[(3*k)]);
	}

	ResetDataFlow();				 //发送帧复位信号
}

//-------------------------------------------------------------------------------
//子程序名称:SendSameColor(unsigned char *ptr,unsigned char cnt)
//功能：相同颜色的点发送cnt次
//参数：接收的参数是一个指针，指向像素点颜色数组，cnt传递发送个数
//-------------------------------------------------------------------------------
void SendSameColor(uint8_t *ptr,unsigned char cnt)
{
	unsigned char k;

	ResetDataFlow();				 //发送帧复位信号

	for(k=0;k<cnt;k++)				 //发送一帧数据，SNUM是板子LED的个数
	{
		SendOnePix(&ptr[0]);
	}

	ResetDataFlow();				 //发送帧复位信号
}
//-------------------------------------------------------------------------------
//子程序名称:SendOneFrameFrom(unsigned char i,unsigned char *ptr)
//功能：从指定的像素点开始发送一帧数据（即发送整个数组的数据）
//参数：接收的参数是一个指针，此函数会将此指针指向的地址的整帧数据发送
//		i:把数组的第0个像素数据发送到第i个像素点（第0个像素是板上标号为01的像素）
//说明：即原本对应第一个像素的数据会发送到第i个像素点（LED）上
//-------------------------------------------------------------------------------
void SendOneFrameFrom(unsigned char i,uint8_t *ptr)
{
	unsigned char k;

	ResetDataFlow();				 //发送帧复位信号

   	for(k=(SNUM-i);k<SNUM;k++)		 //发送一帧数据
	{
		SendOnePix(&ptr[(3*k)]);
	}
	for(k=0;k<(SNUM-i);k++)
	{
		SendOnePix(&ptr[(3*k)]);
	}

	ResetDataFlow();				 //发送帧复位信号
}

void SendOneFrameFrom_1(unsigned char i,uint8_t *ptr, uint8_t num) // 亮num个灯 用来显示电量
{
    unsigned char k;
    uint8_t show_times = 0, zero[3];

    for(k=0;k<3;k++)    zero[k] = 0; // 数组清零

    ResetDataFlow();                 // 发送帧复位信号

    for(k=(SNUM-i);k<SNUM;k++)       // 发送一帧数据
    {
        show_times++;
        if(show_times > num)    SendOnePix(zero);
        else                    SendOnePix(&ptr[(3*k)]);
    }
    for(k=0;k<(SNUM-i);k++)
    {
        show_times++;
        if(show_times > num)    SendOnePix(zero);
        else                    SendOnePix(&ptr[(3*k)]);
    }

    ResetDataFlow();                 // 发送帧复位信号
}

//-------------------------------------------------------------------------------
//子程序名称:SendOneFrameSince(unsigned char i,unsigned char *ptr)
//功能：从第i个像素点的数据开始发送一帧数据（即发送整个数组的数据）
//参数：接收的参数是一个指针，此函数会将此指针指向的地址的整帧数据发送
//		i:把数组的第i个像素数据发送到第1个像素点
//说明：即原本对应第i像素的数据会发送到第1个像素点（LED）上，第i+1个像素点的数据
//		发送到第2个像素上
//-------------------------------------------------------------------------------
void SendOneFrameSince(unsigned char i,uint8_t *ptr)
{
	unsigned char k;

	ResetDataFlow();				 //发送帧复位信号

	for(k=i;k<SNUM;k++)				 //发送一帧数据
	{
		SendOnePix(&ptr[(3*k)]);
	}
	for(k=0;k<i;k++)
	{
		SendOnePix(&ptr[(3*k)]);
	}
	ResetDataFlow();				 //发送帧复位信号
}

void RGB_Data_Init(void)
{
    uint16_t i, j;
    float sin_data;
    for(i = 0; i < SNUM; i++)
    {
        sin_data = sin(2 * 3.14 * i / SNUM);
        LED_Buff[i][0] = 20 * (sin_data > 0 ? sin_data : 0);
        sin_data = sin(2 * 3.14 * i / SNUM + 3.14 * 2 / 3);
        LED_Buff[i][1] = 16 * (sin_data > 0 ? sin_data : 0);
        sin_data = sin(2 * 3.14 * i / SNUM - 3.14 * 2 / 3);
        LED_Buff[i][2] = 20 * (sin_data > 0 ? sin_data : 0);
    }
}

// RGB循环显示 num个灯亮
void RGB_Show(uint8_t num)
{
    static uint16_t state = 0;
    SendOneFrameFrom_1(state++, LED_Buff, num);
    if(state >= SNUM) state = 0;
}
/**********************************THE END**********************************/ 

 

