/*
 * adc.c
 *
 *  Created on: 2022Äê3ÔÂ8ÈÕ
 *      Author: Sun Lee
 */

#include "myheadfile.h"
//A16 A13
void ADC_Init(void)
{
    adc_init(ADC_0, ADC0_CH0_A0);
    adc_init(ADC_1, ADC1_CH1_A17);
    adc_init(ADC_1, ADC1_CH5_A21);
    adc_init(ADC_2, ADC2_CH3_A35);//distant
    adc_init(ADC_1, ADC1_CH8_A24);//close
    adc_init(ADC_0, ADC0_CH13_A13);
    adc_init(ADC_1, ADC1_CH0_A16);
}

float Get_Bat_V(void)
{
    //return (float)adc_mean_filter(ADC_0, ADC0_CH0_A0, ADC_12BIT, 10) * 2 * 3.3 / 4096;
    return (float)adc_mean_filter(ADC_0, ADC0_CH13_A13, ADC_12BIT, 10);
}

float Get_Cap_V(void)
{
    return (float)adc_mean_filter(ADC_1, ADC1_CH1_A17, ADC_12BIT, 10) * 16 * 3.3 / 4095;
  // return (float)adc_mean_filter(ADC_1, ADC1_CH1_A17, ADC_12BIT, 10);
    //return (float)adc_mean_filter(ADC_1, ADC1_CH0_A16, ADC_12BIT, 10);

}

float Get_Charge_I(void)
{
    return (float)adc_mean_filter(ADC_1, ADC1_CH5_A21, ADC_12BIT, 10) * 3.3 * 0.45 / 4095;
    //return (float)adc_mean_filter(ADC_1, ADC1_CH5_A21, ADC_12BIT, 10) ;
}


float Get_Jiance_A16(void)
{
    return (float)adc_mean_filter(ADC_1, ADC1_CH0_A16, ADC_12BIT, 10);
}
float Get_Jiance_A13(void)
{
    return (float)adc_mean_filter(ADC_0, ADC0_CH13_A13, ADC_12BIT, 10);
}
float Get_Charger_Pos(uint16 *Distant_Value, uint16 *Close_Value)
{
    *Distant_Value  =   adc_mean_filter(ADC_2, ADC2_CH3_A35, ADC_12BIT, 10);
    *Close_Value    =   adc_mean_filter(ADC_1, ADC1_CH8_A24, ADC_12BIT, 10);
}
