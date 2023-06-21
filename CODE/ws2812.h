#ifndef _WS2812_H_
#define _WS2812_H_

#include "headfile.h"
#include "stdint.h"

#define SNUM 17

#define WS2812_DIN P11_12

#define DI0 IfxPort_setPinLow(&MODULE_P11, 12);
#define DI1 IfxPort_setPinHigh(&MODULE_P11, 12);

extern uint8_t LED_Buff[17][3];

void WS2812_Init(void);
void ResetDataFlow(void);
void SendOnePix(uint8_t *ptr);
void SendOneFrame(uint8_t *ptr);
void SendSameColor(uint8_t *ptr,unsigned char cnt);
void SendOneFrameFrom(unsigned char i,uint8_t *ptr);
void SendOneFrameSince(unsigned char i,uint8_t *ptr);
void RGB_Data_Init(void);
void RGB_Show(uint8_t num);

#endif
