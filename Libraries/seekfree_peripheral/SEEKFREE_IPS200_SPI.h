
/*/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,逐飞科技
 * All rights reserved.
 * 技术讨论QQ群：三群：824575535
 *
 * 以下所有内容版权均属逐飞科技所有，未经允许不得用于商业用途，
 * 欢迎各位使用并传播本程序，修改内容时必须保留逐飞科技的版权声明。
 *
 * @file       		2.0寸IPS屏幕
 * @company	   		成都逐飞科技有限公司
 * @author     		逐飞科技(QQ3184284598)
 * @version    		查看doc内version文件 版本说明
 * @Software 		ADS v1.2.2
 * @Target core		TC264D
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-3-23
 * @note		
						电源引脚
						VCC 3.3V电源
						GND 电源地
						最大分辨率240*320
					------------------------------------ 

 ********************************************************************************************************************/

#ifndef _SEEKFREE_IPS200SPI_H
#define _SEEKFREE_IPS200SPI_H

#include "common.h"
#include "SEEKFREE_FONT.h"

     
//-------常用颜色在SEEKFREE_FONT.h文件中定义----------
//#define RED          	    0xF800	//红色
//#define BLUE         	    0x001F  //蓝色
//#define YELLOW       	    0xFFE0	//黄色
//#define GREEN        	    0x07E0	//绿色
//#define WHITE        	    0xFFFF	//白色
//#define BLACK        	    0x0000	//黑色 
//#define GRAY  			0X8430 	//灰色
//#define BROWN 			0XBC40 	//棕色
//#define PURPLE    		0XF81F	//紫色
//#define PINK    		    0XFE19	//粉色


#define IPS200_BGCOLOR      WHITE	//背景颜色
#define IPS200_PENCOLOR     RED		//画笔颜色


//-----------------引脚定义------------------------------
#define IPS200_SPIN    SPI_2           //定义使用的SPI号
#define IPS200_SCL     SPI2_SCLK_P15_3 //定义SPI_SCK引脚
#define IPS200_SDA     SPI2_MOSI_P15_5 //定义SPI_MOSI引脚
#define IPS200_SDA_IN  SPI2_MISO_P15_4 //定义SPI_MISO引脚  IPS没有MISO引脚，但是这里任然需要定义，在spi的初始化时需要使用
#define IPS200_CS      SPI2_CS0_P15_2  //定义SPI_CS引脚

#define IPS200_BL_PIN      P15_4           //液晶背光引脚定义 由于实际通讯未使用P15_4因此 这里复用为GPIO
#define IPS200_REST_PIN    P15_1           //液晶复位引脚定义
#define IPS200_DC_PIN      P15_0           //液晶命令位引脚定义

#define IPS200_DC(x)       gpio_set(IPS200_DC_PIN,x)
#define IPS200_RST(x)      gpio_set(IPS200_REST_PIN,x)

#define IPS200_W 240
#define IPS200_H 320


//定义显示方向
//0 竖屏模式
//1 竖屏模式  旋转180°
//2 横屏模式
//3 横屏模式  旋转180°
#define IPS200_DISPLAY_DIR 3

#if (0==IPS200_DISPLAY_DIR || 1==IPS200_DISPLAY_DIR)
#define	IPS200_X_MAX	IPS200_W	//液晶X方宽度
#define IPS200_Y_MAX	IPS200_H   //液晶Y方宽度
     
#elif (2==IPS200_DISPLAY_DIR || 3==IPS200_DISPLAY_DIR)
#define	IPS200_X_MAX	IPS200_H	//液晶X方宽度
#define IPS200_Y_MAX	IPS200_W   //液晶Y方宽度
     
#else
#error "IPS200_DISPLAY_DIR 定义错误"
     
#endif


void ips200_init(void); //初始化硬件
void ips200_w_data(uint8 dat);
void ips200_wr_reg(uint8 com);
void ips200_wr_data(uint8 dat);
void ips200_wr_data16(uint16 dat);
void ips200_w_reg(uint8 com,uint8 dat);
void ips200_address_set(uint16 x1,uint16 y1,uint16 x2,uint16 y2);
void ips200_clear(uint16 color);
void ips200_drawpoint(uint16 x,uint16 y,uint16 color);
void ips200_showchar(uint16 x,uint16 y,const int8 dat);
void ips200_showstr(uint16 x,uint16 y,const int8 dat[]);


void ips200_showint8(uint16 x,uint16 y,int8 dat);
void ips200_showuint8(uint16 x,uint16 y,uint8 dat);
void ips200_showint16(uint16 x,uint16 y,int16 dat);
void ips200_showuint16(uint16 x,uint16 y,uint16 dat);
void ips200_showint32(uint16 x,uint16 y,int dat,uint8 num);
void ips200_showfloat(uint16 x,uint16 y,double dat,int8 num,int8 pointnum);
void ips200_showimage(uint16 x,uint16 y,uint16 w,uint16 l,const unsigned char *p);

void ips200_displayimage032(uint16 start_x, uint16 start_y, uint16 width, uint16 height, uint8 *p);
void ips200_displayimage032_zoom(uint8 *p, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height);
void ips200_displayimage032_zoom1(uint8 *p, uint16 width, uint16 height, uint16 start_x, uint16 start_y, uint16 dis_width, uint16 dis_height);
void ips200_displayimage8660_zoom(uint16 *p, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height);
void ips200_displayimage8660_zoom1(uint16 *p, uint16 width, uint16 height, uint16 start_x, uint16 start_y, uint16 dis_width, uint16 dis_height);
void ips200_displayimage8660_grayscale_zoom(uint16 *p, uint16 width, uint16 height, uint16 dis_width, uint16 dis_height);
void ips200_displayimage7725(uint8 *p, uint16 width, uint16 height);
void ips200_display_chinese(uint16 x, uint16 y, uint8 size, const uint8 *p, uint8 number, uint16 color);

#endif

