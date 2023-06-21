
 
/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		isr
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		ADS v1.2.2
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 ********************************************************************************************************************/


#include "isr_config.h"
#include "isr.h"
#include "myheadfile.h"

//PIT中断函数  示例
IFX_INTERRUPT(cc60_pit_ch0_isr, 0, CCU6_0_CH0_ISR_PRIORITY)//10ms
{
    static int16 Last_Charger_Sensor_Close;
    static int16 Charge_Delay = 0;
    static int16 Charge_Delay_B = 0;
    static int16 tms_Charge = 0;
    static int16 Charge_stop_num = 0;

	enableInterrupts();//开启中断嵌套
	PIT_CLEAR_FLAG(CCU6_0, PIT_CH0);
	gpio_toggle(P20_8);

	//****************充电相关*******************//
	V_Bat = Get_Bat_V();//adc检测
	V_Cap = Get_Cap_V();
	I_Charge = Get_Charge_I();
	// 充电PID
        Charge_PID.input = 12.8;
        Charge_PID.feedback = V_Cap;
	//Charge_PID.feedback = V_Cap;
	//Charge_PID.feedback = V_Cap * I_Charge;
	if(Charge_PID.feedback > 10) {L_Motor_PID.err_x = 0; R_Motor_PID.err_x = 0;}
	PID_Cal(&Charge_PID);
	pwm_duty(ATOM1_CH2_P10_2, Charge_PID.output);
	//pwm_duty(ATOM1_CH2_P10_2, 7500);

//	// 获取充电线圈位置
     Get_A16 = Get_Jiance_A16();
     Get_A13 = Get_Jiance_A13();
//    n->c->s->n
    // 高放大倍率传感器检测到数值大于2000保持300ms，减速等待充电
     if(Get_A13 > 300 && charging_state == 'n' && Charge_Delay_B == 0 && No_Charge_Flag == 0 )
     {
         tms_Charge++;
         if(tms_Charge > 5)
          {
              charging_state = 'b';
              tms_Charge = 0;
          }
     }

     if((Get_A16 > 2200 && charging_state == 'b' && Charge_Delay == 0 && No_Charge_Flag == 0) || (Get_A16 > 2500  && Charge_Delay == 0 && No_Charge_Flag == 0))// && Get_A13 > 2000
     {
         tms_Charge++;
     }
     if(tms_Charge >= 18)
      {
          tms_Charge = 0;
          charging_state = 's';
          car_stop = 1;
          //BEEP_ON;
          Charge_stop_num++;
        //  datatft = Charge_stop_num;
      }
	// 若电容电压大于12V，启动赛车
     if((V_Cap >= 11.7 && charging_state == 's' && Charge_Num == 0) ||
                 (V_Cap > 11.3 && charging_state == 's' && Charge_Num == 1) ||
                 (V_Cap > 12.7 && charging_state == 's' && Charge_Num == 2) ||
               //  (V_Cap > 10.5 && charging_state == 's' && Charge_Num == 3) ||
                 (V_Cap > 10.3 && charging_state == 's' && Charge_Num == 3) ||
                 (V_Cap > 12.5 && charging_state == 's' && Charge_Num == 4))
     {
        L_Motor_PID.err_x = 0;
        R_Motor_PID.err_x = 0;
        Turning_PID.err_x = 0;
	    car_stop = 0;
	    Charge_Num++;
	    charging_state = 'n';
	    Charge_Delay = 1;
	    BEEP_OFF;
	    Charge_Delay_B = 1;
	   // No_Charge_Flag = 1;
	}
//	else BEEP_OFF;
//	// 延时5s后等待下一次充电
	 if(Charge_Delay_B >= 1)
     {
     Charge_Delay_B++;
         if(Charge_Delay_B >= 150) Charge_Delay_B = 0;
     }
	if(Charge_Delay >= 1)
	{
	    Charge_Delay++;
	    if(Charge_Delay >= 150) Charge_Delay = 0;
	}
	//***************************************//
    if(Charge_Num == 1)
    {
        Go_Buxian_Jishi++;
    }

    if(Flag_Branch_road_CiShu == 1)
    {
        No_Charge_Flag = 1;
    }

    if(Flag_Branch_road_CiShu == 2 && Charge_Num < 3)
    {
        No_Charge_Flag = 0;
    }
	Motor_PID();
//	lv_tick_inc(2);

}


IFX_INTERRUPT(cc60_pit_ch1_isr, 0, CCU6_0_CH1_ISR_PRIORITY)
{
	enableInterrupts();//开启中断嵌套
	if(Two_Time_Flag == 1)
	{
	    Two_Time_Flag = 0;
	    BEEP_OFF;
	}
	if(Garage_Go_Success == 1)
	{
	    Garage_Go_Success = 2;
	}
	PIT_CLEAR_FLAG(CCU6_0, PIT_CH1);
}

IFX_INTERRUPT(cc61_pit_ch0_isr, 0, CCU6_1_CH0_ISR_PRIORITY)
{
	enableInterrupts();//开启中断嵌套
	static uint16 tms = 0;
	static uint16 crtms = 0;
	static uint16 Circle_Flag_R_tms = 0;
	static uint16 Circle_Flag_L_tms = 0;
	static int16 HuiHuan_Right_tms = 0;
	static int16 HuiHuan_Left_tms = 0;
	static int16 qiangzhi_fix_tms = 0;
	static int16 Circle_Flag_R_G_tms = 0;
	static int16 Circle_Flag_L_G_tms = 0;
	static int16 Zhunbei_Rush_tms = 0;
	static int16 Zhunbei_Jiansu_tms = 0;
	static int16 Sancha_In_tms = 0;
	static int16 Back_tms = 0;
	static int16 Zhunbei_Start_Huihuan_tms = 0;
	if(Sancha_In == 1)
	{
	    Sancha_In_tms++;
	    if(Sancha_In_tms > 30)
	    {
	        Sancha_In = 0;
	        Sancha_In_tms = 0;
	    }
	}
	if(Zhunbei_Start_Huihuan == 0 && Charge_Num == 1)
	{
	    Zhunbei_Start_Huihuan_tms++;
	    BEEP_ON;
	    if(Zhunbei_Start_Huihuan_tms > 170 && Zhunbei_Start_Huihuan == 0 )
	    {
	        BEEP_OFF;
	        Zhunbei_Start_Huihuan = 1;
	    }
	}
	if(Zhunbei_Rush == 1)
	{
	    Zhunbei_Rush_tms++;
	    if(Zhunbei_Rush_tms >= 50 && Zhunbei_Rush == 1)
	    {
	        Zhunbei_Rush = 2;
	        BEEP_ON;
	        Zhunbei_Rush_tms = 0;
	    }
	}
	if(Zhunbei_Rush == 2)
	{
	    Zhunbei_Jiansu_tms++;
	    if(Zhunbei_Rush == 2 && Zhunbei_Jiansu_tms > 105)
	    {
	        BEEP_OFF;
	        Zhunbei_Rush = 3;
	    }
	}
	if(Flag_Branch_road_CiShu == 2)
	{
	    Zhunbei_Rush = 4;
	}
	if(ZhunBei_Out_CR_Flag == 0 && Circle_Flag_R == 's')
	{
	    Circle_Flag_R_tms++;
	    if(Circle_Flag_R_tms > 20 && ZhunBei_Out_CR_Flag == 0)
        {
            ZhunBei_Out_CR_Flag = 1;
            Circle_Flag_R_tms = 0;
        }
	}
	if(ZhunBei_Out_CL_Flag == 0 && Circle_Flag_L == 's')
	{
	    Circle_Flag_L_tms++;
	    if(Circle_Flag_L_tms > 20 && ZhunBei_Out_CL_Flag == 0)
	    {
	        ZhunBei_Out_CL_Flag = 1;
	        Circle_Flag_L_tms = 0;
	    }
	}
	if(Yuanhuan_Out_Right == 1 && Get_A16 > 2200)
	{
	    Yuanhuan_Out_Right = 0;
	    Circle_Flag_R = 'g';
	}
	if(Circle_Flag_R == 'g' )//Charge_Num == 4    && car_stop == 0&& Charge_Num == 4
	{
	    Circle_Flag_R_G_tms++;
	    if(Circle_Flag_R_G_tms >=150  && Circle_Flag_R == 'g')
	    {
	        Circle_Flag_R = 'n';
	        Circle_Flag_R_G_tms = 0;
	        No_Charge_Flag = 1;
	    }
	}
    if(Yuanhuan_Out_Left == 1 && Get_A16 > 2200)
    {
        Yuanhuan_Out_Left = 0;
        Circle_Flag_L = 'g';
    }
    if(Circle_Flag_L == 'g' && car_stop == 0 )//Charge_Num == 6 &&
    {
        Circle_Flag_L_G_tms++;
        if(Circle_Flag_L_G_tms >= 70  && Circle_Flag_L == 'g')
        {
            Circle_Flag_L = 'n';
            Circle_Flag_L_G_tms = 0;
            No_Charge_Flag = 1;
        }
    }
    ///////////////////////////////////////////////////////////////

    if(Circle_Flag_L == 'i' && car_stop == 0)
    {
        crtms++;

        if(crtms >= 80  && Circle_Flag_L == 'i')
        {
            Circle_Flag_L = 'n';
            crtms = 0;
            Circle_Left_CiShu_Flag++;

        }
    }
    /////////////////////////////////////////////////////////
    if(Huihuan_In_Left == 1)
       {
           HuiHuan_Left_tms++;
       }
       if(HuiHuan_Left_tms > 90 && Huihuan_Left_Flag == 'i')
       {
           Huihuan_Left_Flag = 'n';
           BEEP_OFF;
           Huihuan_In_Left = 0;
           Huihuan_Left_CiShu_Flag++;
           HuiHuan_Left_tms =0;
       }
       if(Huihuan_In_Right == 1)
          {
           BEEP_ON;
           HuiHuan_Right_tms++;
          if(HuiHuan_Right_tms > 70 && Huihuan_Right_Flag == 'i')
                {
                    BEEP_OFF;
                    Huihuan_In_Right = 0;
                    Huihuan_Right_Flag = 'n';
                    Huihuan_Right_CiShu_Flag++;
                    HuiHuan_Right_tms = 0;
                }
          }

    if(Flag_Branch_road == 'i')
    {
        tms++;
    }
    if(tms > 50 && Flag_Branch_road == 'i')
       {
        Flag_Branch_road = 'n';
           BEEP_OFF;
           tms = 0;
       }
    datatft = tms;
    if(qiangzhi_fix_flag == 1)
    {
        BEEP_ON;
        qiangzhi_fix_tms++;
        if(qiangzhi_fix_tms > 30)
        {
            BEEP_OFF;
            qiangzhi_fix_flag = 2;
            qiangzhi_fix_tms = 0;
        }
    }
    if(Back_To == 1)
    {
        Back_tms++;
        if(Back_tms > 150)
        {
            car_stop = 1;
        }
    }
	PIT_CLEAR_FLAG(CCU6_1, PIT_CH0);

}

IFX_INTERRUPT(cc61_pit_ch1_isr, 0, CCU6_1_CH1_ISR_PRIORITY)
{
	enableInterrupts();//开启中断嵌套
	PIT_CLEAR_FLAG(CCU6_1, PIT_CH1);
	RGB_Show((uint8_t)(V_Cap*17.0/13));
//	vofa_send_float((float)fit_x_num - 1);
//    vofa_send_float(mid_slope);
//    vofa_send_float(mid_const - 94);
//    vofa_send_float(L_Motor_PID.feedback);
//    vofa_send_float(R_Motor_PID.feedback);
//    vofa_send_float(L_Motor_PID.input);
//    vofa_send_float(R_Motor_PID.input);
//    vofa_send_float(Turning_PID.output);
//    vofa_send_float(mid_line[70]);
//    vofa_send_end();

}




IFX_INTERRUPT(eru_ch0_ch4_isr, 0, ERU_CH0_CH4_INT_PRIO)
{
	enableInterrupts();//开启中断嵌套
	if(GET_GPIO_FLAG(ERU_CH0_REQ4_P10_7))//通道0中断
	{
		CLEAR_GPIO_FLAG(ERU_CH0_REQ4_P10_7);
	}

	if(GET_GPIO_FLAG(ERU_CH4_REQ13_P15_5))//通道4中断
	{
		CLEAR_GPIO_FLAG(ERU_CH4_REQ13_P15_5);
	}
}

IFX_INTERRUPT(eru_ch1_ch5_isr, 0, ERU_CH1_CH5_INT_PRIO)
{
	enableInterrupts();//开启中断嵌套
	if(GET_GPIO_FLAG(ERU_CH1_REQ5_P10_8))//通道1中断
	{
		CLEAR_GPIO_FLAG(ERU_CH1_REQ5_P10_8);
	}

	if(GET_GPIO_FLAG(ERU_CH5_REQ1_P15_8))//通道5中断
	{
		CLEAR_GPIO_FLAG(ERU_CH5_REQ1_P15_8);
	}
}

//由于摄像头pclk引脚默认占用了 2通道，用于触发DMA，因此这里不再定义中断函数
//IFX_INTERRUPT(eru_ch2_ch6_isr, 0, ERU_CH2_CH6_INT_PRIO)
//{
//	enableInterrupts();//开启中断嵌套
//	if(GET_GPIO_FLAG(ERU_CH2_REQ7_P00_4))//通道2中断
//	{
//		CLEAR_GPIO_FLAG(ERU_CH2_REQ7_P00_4);
//
//	}
//	if(GET_GPIO_FLAG(ERU_CH6_REQ9_P20_0))//通道6中断
//	{
//		CLEAR_GPIO_FLAG(ERU_CH6_REQ9_P20_0);
//
//	}
//}



IFX_INTERRUPT(eru_ch3_ch7_isr, 0, ERU_CH3_CH7_INT_PRIO)
{
	enableInterrupts();//开启中断嵌套
	if(GET_GPIO_FLAG(ERU_CH3_REQ6_P02_0))//通道3中断
	{
		CLEAR_GPIO_FLAG(ERU_CH3_REQ6_P02_0);
		if		(CAMERA_GRAYSCALE == camera_type)	mt9v03x_vsync();
		else if (CAMERA_BIN_UART  == camera_type)	ov7725_uart_vsync();
		else if	(CAMERA_BIN       == camera_type)	ov7725_vsync();

	}
	if(GET_GPIO_FLAG(ERU_CH7_REQ16_P15_1))//通道7中断
	{
		CLEAR_GPIO_FLAG(ERU_CH7_REQ16_P15_1);

	}
}



IFX_INTERRUPT(dma_ch5_isr, 0, ERU_DMA_INT_PRIO)
{
	enableInterrupts();//开启中断嵌套

	if		(CAMERA_GRAYSCALE == camera_type)	mt9v03x_dma();
	else if (CAMERA_BIN_UART  == camera_type)	ov7725_uart_dma();
	else if	(CAMERA_BIN       == camera_type)	ov7725_dma();
}


//串口中断函数  示例
IFX_INTERRUPT(uart0_tx_isr, 0, UART0_TX_INT_PRIO)
{
	enableInterrupts();//开启中断嵌套
    IfxAsclin_Asc_isrTransmit(&uart0_handle);
}
IFX_INTERRUPT(uart0_rx_isr, 0, UART0_RX_INT_PRIO)
{
    static uint8 uart_buff;
	enableInterrupts();//开启中断嵌套
    IfxAsclin_Asc_isrReceive(&uart0_handle);
    //获取接收的数据，以字节为单位送给上位机接受函数处理
    uart_query(UART_0, &uart_buff);
    my_debug(uart_buff);//上位机接收函数
}
IFX_INTERRUPT(uart0_er_isr, 0, UART0_ER_INT_PRIO)
{
	enableInterrupts();//开启中断嵌套
    IfxAsclin_Asc_isrError(&uart0_handle);
}

//串口1默认连接到摄像头配置串口
IFX_INTERRUPT(uart1_tx_isr, 0, UART1_TX_INT_PRIO)
{
	enableInterrupts();//开启中断嵌套
    IfxAsclin_Asc_isrTransmit(&uart1_handle);
}
IFX_INTERRUPT(uart1_rx_isr, 0, UART1_RX_INT_PRIO)
{
	enableInterrupts();//开启中断嵌套
    IfxAsclin_Asc_isrReceive(&uart1_handle);
    if		(CAMERA_GRAYSCALE == camera_type)	mt9v03x_uart_callback();
    else if (CAMERA_BIN_UART  == camera_type)	ov7725_uart_callback();
}
IFX_INTERRUPT(uart1_er_isr, 0, UART1_ER_INT_PRIO)
{
	enableInterrupts();//开启中断嵌套
    IfxAsclin_Asc_isrError(&uart1_handle);
}


//串口2默认连接到无线转串口模块
IFX_INTERRUPT(uart2_tx_isr, 0, UART2_TX_INT_PRIO)
{
	enableInterrupts();//开启中断嵌套
    IfxAsclin_Asc_isrTransmit(&uart2_handle);
}
IFX_INTERRUPT(uart2_rx_isr, 0, UART2_RX_INT_PRIO)
{
	enableInterrupts();//开启中断嵌套
    IfxAsclin_Asc_isrReceive(&uart2_handle);
    switch(wireless_type)
    {
    	case WIRELESS_SI24R1:
    	{
    		wireless_uart_callback();
    	}break;

    	case WIRELESS_CH9141:
		{
		    bluetooth_ch9141_uart_callback();
		}break;
    	default:break;
    }

}
IFX_INTERRUPT(uart2_er_isr, 0, UART2_ER_INT_PRIO)
{
	enableInterrupts();//开启中断嵌套
    IfxAsclin_Asc_isrError(&uart2_handle);
}



IFX_INTERRUPT(uart3_tx_isr, 0, UART3_TX_INT_PRIO)
{
	enableInterrupts();//开启中断嵌套
    IfxAsclin_Asc_isrTransmit(&uart3_handle);
}
IFX_INTERRUPT(uart3_rx_isr, 0, UART3_RX_INT_PRIO)
{
	enableInterrupts();//开启中断嵌套
    IfxAsclin_Asc_isrReceive(&uart3_handle);
}
IFX_INTERRUPT(uart3_er_isr, 0, UART3_ER_INT_PRIO)
{
	enableInterrupts();//开启中断嵌套
    IfxAsclin_Asc_isrError(&uart3_handle);
}
