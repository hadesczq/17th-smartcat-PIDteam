/*
 * fuzzy.h
 *
 *  Created on: 2022��4��6��
 */
#ifndef _FUZZY_H
#define _FUZZY_H
#include "myheadfile.h"

typedef enum
{
    Fuzzy_Rank7=7,
    Fuzzy_Rank5=5,
    Fuzzy_Rank3=3,
}Fuzzy_Rank_e; // Fuzzy Rank Enum

typedef struct
{
    Fuzzy_Rank_e Rank;  // �ּ�����
    float fe;  // e(k)
    float fec; // e(k)'
    float eRule[7];   // ���������������ֵ
    float ecRule[7];  // ���仯������������ֵ
    float U1Rule[7];  // ���������������ֵ
    int rule[7][7];
    int pe;
    int pec;
    uint8_t get_value;
}FuzzyStruct;  // ģ���ṹ��

extern FuzzyStruct Turning_P_Fuzzy;

//float FuzzyCtrl(FuzzyStruct* Fuzzy_S);
float Fuzzy_Update(FuzzyStruct* F_S,float ek,float ekc);

#endif
