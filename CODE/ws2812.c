#include "ws2812.h"
#include "stdint.h"
#include "math.h"

uint8_t LED_Buff[17][3]={{10,10,10},{10,10,10},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},
                        {0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
//-------------------------------------------------------------------------------
//�ӳ�������:IO_Init(void)
//���ܣ��˿ڳ�ʼ��
//-------------------------------------------------------------------------------
void WS2812_Init(void)
{
    gpio_init(WS2812_DIN, GPO, 0, PUSHPULL);
    RGB_Data_Init();
    ResetDataFlow();
}

//-------------------------------------------------------------------------------
//�ӳ�������:ResetDateFlow(void)
//���ܣ���λ��Ϊ��һ�η�����׼����
//˵������DI��λΪ0����ʱԼ65us
//-------------------------------------------------------------------------------
void ResetDataFlow(void)
{
	unsigned char i,j;
	DI0;					//DI��Ϊ0����ʱ50us���ϣ�ʵ��֡��λ
	IfxStm_waitTicks(&MODULE_STM0, 1);//200ns
}
//-------------------------------------------------------------------------------
//�ӳ�������:SendOnePix(unsigned char *ptr)
//���ܣ�����һ�����ص��24bit����
//���������յĲ�����һ��ָ�룬�˺����Ὣ��ָ��ָ��ĵ�ַ������������Byte�����ݷ���
//˵��������������ֱ�ӵ��ô˺���ʱ��������֡���Ϳ�ʼǰ��Ҫ��ִ�� ResetDataFlow()
//		�����ǰ�������ķ�ʽ���ͣ�����Ϊ800KBPS
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
			if(temp&0x80)		 //�Ӹ�λ��ʼ����
			{
				DI1;			 //���͡�1����
//				systick_delay_ns(STM0, 700);
				IfxStm_waitTicks(&MODULE_STM0, 1);//700ns
                IfxStm_waitTicks(&MODULE_STM0, 1);
                IfxStm_waitTicks(&MODULE_STM0, 1);
                IfxStm_waitTicks(&MODULE_STM0, 1);
				DI0;
//				systick_delay_ns(STM0, 600);
				IfxStm_waitTicks(&MODULE_STM0, 30);//600ns
			}
			else				//���͡�0����
			{
				DI1;
//				systick_delay_ns(STM0, 350);
				IfxStm_waitTicks(&MODULE_STM0, 10);//300ns

				DI0;
//				systick_delay_ns(STM0, 800);
				IfxStm_waitTicks(&MODULE_STM0, 50);//800ns
			}
			temp=(temp<<1);		 //����λ
		}
	}
}
//-------------------------------------------------------------------------------
//�ӳ�������:SendOneFrame(unsigned char *ptr)
//���ܣ�����һ֡���ݣ�������������������ݣ�
//���������յĲ�����һ��ָ�룬�˺����Ὣ��ָ��ָ��ĵ�ַ��������������ݷ���
//-------------------------------------------------------------------------------
void SendOneFrame(uint8_t *ptr)
{
	unsigned char k;

	ResetDataFlow();				 //����֡��λ�ź�

	for(k=0;k<SNUM;k++)				 //����һ֡���ݣ�SNUM�ǰ���LED�ĸ���
	{
		SendOnePix(&ptr[(3*k)]);
	}

	ResetDataFlow();				 //����֡��λ�ź�
}

//-------------------------------------------------------------------------------
//�ӳ�������:SendSameColor(unsigned char *ptr,unsigned char cnt)
//���ܣ���ͬ��ɫ�ĵ㷢��cnt��
//���������յĲ�����һ��ָ�룬ָ�����ص���ɫ���飬cnt���ݷ��͸���
//-------------------------------------------------------------------------------
void SendSameColor(uint8_t *ptr,unsigned char cnt)
{
	unsigned char k;

	ResetDataFlow();				 //����֡��λ�ź�

	for(k=0;k<cnt;k++)				 //����һ֡���ݣ�SNUM�ǰ���LED�ĸ���
	{
		SendOnePix(&ptr[0]);
	}

	ResetDataFlow();				 //����֡��λ�ź�
}
//-------------------------------------------------------------------------------
//�ӳ�������:SendOneFrameFrom(unsigned char i,unsigned char *ptr)
//���ܣ���ָ�������ص㿪ʼ����һ֡���ݣ�������������������ݣ�
//���������յĲ�����һ��ָ�룬�˺����Ὣ��ָ��ָ��ĵ�ַ����֡���ݷ���
//		i:������ĵ�0���������ݷ��͵���i�����ص㣨��0�������ǰ��ϱ��Ϊ01�����أ�
//˵������ԭ����Ӧ��һ�����ص����ݻᷢ�͵���i�����ص㣨LED����
//-------------------------------------------------------------------------------
void SendOneFrameFrom(unsigned char i,uint8_t *ptr)
{
	unsigned char k;

	ResetDataFlow();				 //����֡��λ�ź�

   	for(k=(SNUM-i);k<SNUM;k++)		 //����һ֡����
	{
		SendOnePix(&ptr[(3*k)]);
	}
	for(k=0;k<(SNUM-i);k++)
	{
		SendOnePix(&ptr[(3*k)]);
	}

	ResetDataFlow();				 //����֡��λ�ź�
}

void SendOneFrameFrom_1(unsigned char i,uint8_t *ptr, uint8_t num) // ��num���� ������ʾ����
{
    unsigned char k;
    uint8_t show_times = 0, zero[3];

    for(k=0;k<3;k++)    zero[k] = 0; // ��������

    ResetDataFlow();                 // ����֡��λ�ź�

    for(k=(SNUM-i);k<SNUM;k++)       // ����һ֡����
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

    ResetDataFlow();                 // ����֡��λ�ź�
}

//-------------------------------------------------------------------------------
//�ӳ�������:SendOneFrameSince(unsigned char i,unsigned char *ptr)
//���ܣ��ӵ�i�����ص�����ݿ�ʼ����һ֡���ݣ�������������������ݣ�
//���������յĲ�����һ��ָ�룬�˺����Ὣ��ָ��ָ��ĵ�ַ����֡���ݷ���
//		i:������ĵ�i���������ݷ��͵���1�����ص�
//˵������ԭ����Ӧ��i���ص����ݻᷢ�͵���1�����ص㣨LED���ϣ���i+1�����ص������
//		���͵���2��������
//-------------------------------------------------------------------------------
void SendOneFrameSince(unsigned char i,uint8_t *ptr)
{
	unsigned char k;

	ResetDataFlow();				 //����֡��λ�ź�

	for(k=i;k<SNUM;k++)				 //����һ֡����
	{
		SendOnePix(&ptr[(3*k)]);
	}
	for(k=0;k<i;k++)
	{
		SendOnePix(&ptr[(3*k)]);
	}
	ResetDataFlow();				 //����֡��λ�ź�
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

// RGBѭ����ʾ num������
void RGB_Show(uint8_t num)
{
    static uint16_t state = 0;
    SendOneFrameFrom_1(state++, LED_Buff, num);
    if(state >= SNUM) state = 0;
}
/**********************************THE END**********************************/ 

 

