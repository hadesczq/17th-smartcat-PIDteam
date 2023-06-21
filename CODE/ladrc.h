/*
 * ladrc.h
 *
 *  Created on: 2022��4��17��
 *      Author: Sun Lee
 */

#ifndef CODE_LADRC_H_
#define CODE_LADRC_H_

#include "myheadfile.h"
#include <math.h>

typedef struct LADRC
{
    float h;//��ɢ����
    float v;//�����Ŀ��
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
    float u;//����Ŀ�����
    float y;//����Ĳ�����
    float b;//�Σ�����ϵ��
    float b01;
    float b02;
    float b03;
    float w0;//�Σ��۲�������
    float kp;//��
    float kd;//��
    volatile uint8_t Enable;
}LADRC_t;
//typedef struct LADRC ;


//����һ�ο���
void LADRC(LADRC_t* p);
//��������ͬ��ֻ�����Ƿ�����d
void LADRC_fal_kd(LADRC_t* p, float d_line);

void LADRC_GetDefultConfig(LADRC_t* p);
float LADRC_sign(float x);
float LADRC_fst(float x1, float x2, float r, float h);
float LADRC_fal(float e, float a, float e_line);

#endif /* CODE_LADRC_H_ */
