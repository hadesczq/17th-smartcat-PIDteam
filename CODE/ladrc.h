/*
 * ladrc.h
 *
 *  Created on: 2022年4月17日
 *      Author: Sun Lee
 */

#ifndef CODE_LADRC_H_
#define CODE_LADRC_H_

#include "myheadfile.h"
#include <math.h>

typedef struct LADRC
{
    float h;//离散周期
    float v;//输入的目标
    float v1;
    float v2;
    float r;
    float e;
    float e1;
    float e2;
    float z1;
    float z2;
    float z3;
    float u0;
    float u;//输出的控制量
    float y;//输入的测量量
    float b;//参，补偿系数
    float b01;
    float b02;
    float b03;
    float w0;//参，观测器带宽
    float kp;//参
    float kd;//参
    volatile uint8_t Enable;
}LADRC_t;
//typedef struct LADRC ;


//更新一次控制
void LADRC(LADRC_t* p);
//和上面相同，只不过是非线性d
void LADRC_fal_kd(LADRC_t* p, float d_line);

void LADRC_GetDefultConfig(LADRC_t* p);
float LADRC_sign(float x);
float LADRC_fst(float x1, float x2, float r, float h);
float LADRC_fal(float e, float a, float e_line);

#endif /* CODE_LADRC_H_ */
