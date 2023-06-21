/**
 *������������������������������+ +
 *�������������������ߩ��������ߩ� + +
 *��������������������������������
 *�������������������������������� ++ + + +
 *������������ ������������������ ��+
 *�������������������������������� +
 *�����������������������ߡ�������
 *�������������������������������� + +
 *��������������������������������
 *����������������������������
 *���������������������������� + + + +
 *������������������������������������Code is far away from bug with the animal protecting
 *���������������������������� + �����������ޱ���,������bug
 *����������������������������
 *��������������������������������+
 *���������������������� �������������� + +
 *�������������������� ���������������ǩ�
 *�������������������� ������������������
 *�����������������������������ש����� + + + +
 *�����������������������ϩϡ����ϩ�
 *�����������������������ߩ������ߩ�+ + + +
 */
#include "headfile.h"
#include "myheadfile.h"
#pragma section all "cpu0_dsram"
//���������#pragma section all restore���֮���ȫ�ֱ���������CPU0��RAM��

//���̵��뵽���֮��Ӧ��ѡ�й���Ȼ����refreshˢ��һ��֮���ٱ���
//����Ĭ������Ϊ�ر��Ż��������Լ��һ�����ѡ��properties->C/C++ Build->Setting
//Ȼ�����Ҳ�Ĵ������ҵ�C/C++ Compiler->Optimization->Optimization level�������Ż��ȼ�
//һ��Ĭ���½����Ĺ��̶���Ĭ�Ͽ�2���Ż�����˴��Ҳ��������Ϊ2���Ż�

//����TCϵ��Ĭ���ǲ�֧���ж�Ƕ�׵ģ�ϣ��֧���ж�Ƕ����Ҫ���ж���ʹ��enableInterrupts();�������ж�Ƕ��
//�򵥵�˵ʵ���Ͻ����жϺ�TCϵ�е�Ӳ���Զ�������disableInterrupts();���ܾ���Ӧ�κε��жϣ������Ҫ�����Լ��ֶ�����enableInterrupts();�������жϵ���Ӧ��

IFX_ALIGN(4) volatile uint8 mt9v03x_image_otsu_show[MT9V03X_H][MT9V03X_W];//������ʾ��ֵ�����ͼ��buff
IFX_ALIGN(4) volatile uint8 mt9v03x_image_otsu_show_xunji[MT9V03X_H][MT9V03X_W];//������ʾ��ֵ�����ͼ��buff
IFX_ALIGN(4) volatile uint8 mt9v03x_image_ZW_Tool[ZW_ImgSize_H][ZW_ImgSize_W];//����ͼ��buff

int core0_main(void)
{
    char buf_str[32];
    //debug 11.9-11.12
	get_clk();//��ȡʱ��Ƶ��  ��ر���
	//�û��ڴ˴����ø��ֳ�ʼ��������
	// ��ʼ��LED
    gpio_init(P20_8, GPO, 0, PUSHPULL);
    gpio_init(P20_9, GPO, 0, PUSHPULL);
    // ������
    gpio_init(P11_6, GPO, 1, PUSHPULL);
    //���뿪��
    gpio_init(P11_9, GPI, 1, NO_PULL);
    gpio_init(P11_10, GPI, 1, NO_PULL);
    gpio_init(P11_11, GPI, 1, NO_PULL);
    gpio_init(P11_12, GPI, 1, NO_PULL);
    // ��ʼ���������
    gtm_pwm_init(ATOM0_CH1_P21_3, 20000, 0); //0-10000
    gtm_pwm_init(ATOM0_CH3_P21_5, 20000, 0);
    gpio_init(L_DIR, GPO, 1, PUSHPULL);
    gpio_init(R_DIR, GPO, 0, PUSHPULL);
    gtm_pwm_init(ATOM1_CH2_P10_2, 100000, 5000);
    // ��ʼ��������
    gpt12_init(GPT12_T2, GPT12_T2INB_P33_7, GPT12_T2EUDB_P33_6);//r
    gpt12_init(GPT12_T4, GPT12_T4INA_P02_8, GPT12_T4EUDA_P00_9);//l
    WS2812_Init();// ��ʼ��WS2812�ƴ�
    ADC_Init();// ADC
    ips200_init(); //LCD
    mt9v03x_init(); //�����

    //mt9v03x_init(); //�����
    // ��ʱ���жϳ�ʼ��
    simiic_init();
    pit_interrupt_ms(CCU6_0, PIT_CH0, 10);
    pit_interrupt_ms(CCU6_0, PIT_CH1, 2000);
    pit_interrupt_ms(CCU6_1, PIT_CH1, 100);
    pit_interrupt_ms(CCU6_1, PIT_CH0, 10);
    // ����
    uart_init(DEBUG_UART, 115200, DEBUG_UART_TX_PIN, DEBUG_UART_RX_PIN);
    // PID������ʼ��
    PID_Init();
    // ������GPIO
    gpio_init(P11_2, GPO, 0, PUSHPULL);
    //���IIC��ʼ��
    //mpu6050_init();
    //�ȴ����к��ĳ�ʼ�����
	IfxCpu_emitEvent(&g_cpuSyncEvent);
	IfxCpu_waitEvent(&g_cpuSyncEvent, 0xFFFF);
	enableInterrupts();

	while (TRUE)
	{
	   uint16 i = 0,j=0;
	   send_init();
	   sprintf(buf_str, "A13:%.1f", Get_A13);
       ips200_showstr(188, 0, buf_str);
       sprintf(buf_str, "A16:%.1f", Get_A16);
       ips200_showstr(188, 1, buf_str);
       sprintf(buf_str, "stop:%d", car_stop);
       ips200_showstr(188, 2, buf_str);
       sprintf(buf_str, "Cap:%.1f", V_Cap);
       ips200_showstr(188, 3, buf_str);
       sprintf(buf_str, "Mid:%4.1f", Filtre_Mid);
       ips200_showstr(188, 4, buf_str);
       sprintf(buf_str, "ChargeNum:%d", Charge_Num);
       ips200_showstr(188, 5, buf_str);
       sprintf(buf_str, "ZebraNum:%d", Zebra_Crossing_Num);
       ips200_showstr(188, 6, buf_str);
       sprintf(buf_str, "ThreeNum:%d", Flag_Branch_road_CiShu);
       ips200_showstr(188, 7, buf_str);
       sprintf(buf_str, "ChargeState:%c", charging_state);
       ips200_showstr(188, 8, buf_str);
       sprintf(buf_str, "Use_Time:%.2f", use_time/1000.0);
       ips200_showstr(188, 9, buf_str);
       sprintf(buf_str, "Speed:%.1f", running_speed);
       ips200_showstr(188, 10, buf_str);
       sprintf(buf_str, "Speed:%d", Temp_xianshi);
       ips200_showstr(188, 11, buf_str);

       ips200_displayimage032_zoom1(mt9v03x_image_otsu_show_xunji[0], MT9V03X_W, MT9V03X_H, 0, 0, 2 * MT9V03X_W, 2 * MT9V03X_H);
       ips200_displayimage032_zoom1(mt9v03x_image_otsu_show[0], MT9V03X_W, MT9V03X_H, 0, 120, 2 * MT9V03X_W, 2 * MT9V03X_H);

        systick_delay_ms(STM0, 10);
	}
}

#pragma section all restore

