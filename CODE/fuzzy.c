/*
 * fuzzy.c
 *
 *  Created on: 2022年4月6日
 */
#include "myheadfile.h"

// 转向P模糊表 输入为误差和误差变化率
//FuzzyStruct Turning_P_Fuzzy =
//{
//    Fuzzy_Rank7,
//    0,
//    0,
//    {-100,-50,-30,0,30,50,100}, //e
//    {-10,-6,-2,0,2,6,10},       //ec
//    {1.4,1.6,1.8,2.0,2.2,2.4,2.6},               //P
//    {
//// 误差变化率   -3,-2,-1, 0, 1, 2, 3       // 误差
//            { 2, 2, 2, 3, 3, 4, 2 },    //   -3
//            { 2, 1, 2, 2, 3, 5, 4 },    //   -2
//            { 2, 2, 1, 1, 2, 3, 3 },    //   -1
//            { 2, 2, 1, 0, 1, 2, 2 },    //    0
//            { 3, 3, 2, 1, 1, 2, 2 },    //    1
//            { 4, 5, 3, 2, 2, 1, 2 },    //    2
//            { 2, 4, 3, 3, 2, 2, 2 },    //    3
//    }
//};

// 转向P模糊表 输入为误差和车速
FuzzyStruct Turning_P_Fuzzy =
{
    Fuzzy_Rank7,
    0,
    0,
    {0,70,100,120,140,150,170},               //e
    {50,70,90,110,130,150,170},             //speed
    {1.8,2,2.2,2.4,2.6,2.8,3},          //k_p
    {
//speed               0, 1, 2, 3, 4, 5, 6       //     e
            { 1, 2, 3, 4, 5, 5, 6 },    //     1
           { 1, 2, 2, 3, 4, 5, 6 },    //     2
           { 0, 1, 2, 2, 3, 5, 6 },    //     3
           { 0, 1, 1, 2, 3, 4, 6 },    //     4
           { 0, 1, 1, 2, 2, 4, 6 },    //     5
           { 0, 0, 1, 1, 2, 4, 6 },    //     6
           { 0, 0, 0, 1, 2, 4, 6 },    //     7
    }
};

//{ 1, 2, 3, 4, 5, 5, 6 },    //     1
//{ 1, 2, 2, 3, 4, 5, 6 },    //     2
//{ 0, 1, 2, 2, 3, 5, 6 },    //     3
//{ 0, 1, 1, 2, 3, 4, 6 },    //     4
//{ 0, 1, 1, 2, 2, 4, 6 },    //     5
//{ 0, 0, 1, 1, 2, 4, 6 },    //     6
//{ 0, 0, 0, 1, 2, 4, 6 },    //     7

float FuzzyCtrl(FuzzyStruct* Fuzzy_S)
{
    float  eFuzzy[2]  = {0.0, 0.0};
    float  ecFuzzy[2] = {0.0, 0.0};
    float  U1Fuzzy[7] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
    int  num=0,pe=0,pec=0;
    float kp = 0.0;
    int rank;
    int i = 0;
    rank=7;// 设置模糊阶数
    switch(rank)
    {
    case 7:
        {
                        /*-----误差隶属函数描述-----*/
            if(Fuzzy_S->fe <= Fuzzy_S->eRule[0])                // |x_x_x_x_x_x_x_
            {
                eFuzzy[0] =0;
                pe= 0;
            }
            else if(Fuzzy_S->fe <= Fuzzy_S->eRule[1])           // _x|x_x_x_x_x_x_
            {
                eFuzzy[0] = (Fuzzy_S->eRule[1]-Fuzzy_S->fe)/(Fuzzy_S->eRule[1]-Fuzzy_S->eRule[0]);
                pe = 1;
            }
            else if(Fuzzy_S->fe <= Fuzzy_S->eRule[2])           // _x_x|x_x_x_x_x_
            {
                eFuzzy[0] = (Fuzzy_S->eRule[2]-Fuzzy_S->fe)/(Fuzzy_S->eRule[2]-Fuzzy_S->eRule[1]);
                pe =2;
            }
            else if(Fuzzy_S->fe <= Fuzzy_S->eRule[3])           // _x_x_x|x_x_x_x_
            {
                eFuzzy[0] = (Fuzzy_S->eRule[3]-Fuzzy_S->fe)/(Fuzzy_S->eRule[3]-Fuzzy_S->eRule[2]);
                pe =3;
            }
            else if(Fuzzy_S->fe<=Fuzzy_S->eRule[4])             // _x_x_x_x|x_x_x_
            {
                eFuzzy[0] = (Fuzzy_S->fe-Fuzzy_S->eRule[3])/(Fuzzy_S->eRule[4]-Fuzzy_S->eRule[3]);
                pe=4;
            }
            else if(Fuzzy_S->fe<=Fuzzy_S->eRule[5])             // _x_x_x_x_x|x_x_
            {
                eFuzzy[0] = (Fuzzy_S->fe-Fuzzy_S->eRule[4])/(Fuzzy_S->eRule[5]-Fuzzy_S->eRule[4]);
                pe=5;
            }
            else if(Fuzzy_S->fe<=Fuzzy_S->eRule[6])             // _x_x_x_x_x_x|x_
            {
                eFuzzy[0] = (Fuzzy_S->fe-Fuzzy_S->eRule[5])/(Fuzzy_S->eRule[6]-Fuzzy_S->eRule[5]);
                pe=6;
            }
            else                                // _x_x_x_x_x_x_x|
            {
                eFuzzy[0] =0;
                pe=6;
            }

            /*-----误差隶属函数描述-----*/
            if(Fuzzy_S->fec <= Fuzzy_S->ecRule[0])
            {
                ecFuzzy[0] =0;
                pec = 0;
            }
            else if(Fuzzy_S->fec <= Fuzzy_S->ecRule[1])
            {
                ecFuzzy[0] = (Fuzzy_S->ecRule[1]-Fuzzy_S->fec)/(Fuzzy_S->ecRule[1]-Fuzzy_S->ecRule[0]);
                pec = 1 ;
            }
            else if(Fuzzy_S->fec <= Fuzzy_S->ecRule[2])
            {
                ecFuzzy[0] = (Fuzzy_S->ecRule[2]-Fuzzy_S->fec)/(Fuzzy_S->ecRule[2]-Fuzzy_S->ecRule[1]);
                pec = 2;
            }
            else if(Fuzzy_S->fec <= Fuzzy_S->ecRule[3])
            {
                ecFuzzy[0] = (Fuzzy_S->ecRule[3]-Fuzzy_S->fec)/(Fuzzy_S->ecRule[3]-Fuzzy_S->ecRule[2]);
                pec = 3 ;
            }
            else if(Fuzzy_S->fec <= Fuzzy_S->ecRule[4])
            {
                ecFuzzy[0] = (Fuzzy_S->fec-Fuzzy_S->ecRule[3])/(Fuzzy_S->ecRule[4]-Fuzzy_S->ecRule[3]);
                pec=4;
            }
            else if(Fuzzy_S->fec <= Fuzzy_S->ecRule[5])
            {
                ecFuzzy[0] = (Fuzzy_S->fec-Fuzzy_S->ecRule[4])/(Fuzzy_S->ecRule[5]-Fuzzy_S->ecRule[4]);
                pec=5;
            }
            else if(Fuzzy_S->fec<=Fuzzy_S->ecRule[6])
            {
                ecFuzzy[0] = (Fuzzy_S->fec-Fuzzy_S->ecRule[5])/(Fuzzy_S->ecRule[6]-Fuzzy_S->ecRule[5]);
                pec=6;
            }
            else
            {
                ecFuzzy[0] =0;
                pec=6;
            }
            break;
        }//...end case 7
    default: break;
    }//...end switch
    /*查询模糊控制表*/
    num =Fuzzy_S->rule[pe][pec];
    U1Fuzzy[num] = eFuzzy[0];
    if(num<6) kp = Fuzzy_S->U1Rule[num] + (Fuzzy_S->U1Rule[num+1] - Fuzzy_S->U1Rule[num]) * (eFuzzy[0] - ecFuzzy[0]);
    else if(num>=6) kp = Fuzzy_S->U1Rule[num];// 边缘处理

    Fuzzy_S->pe=pe;
    Fuzzy_S->pec=pec;
    Fuzzy_S->get_value=num;
    return(kp);
}


float Fuzzy_Update(FuzzyStruct* F_S,float ek,float ekc)
{
  float value=0;
  F_S->fe=ek;
  F_S->fec=ekc;
  value=FuzzyCtrl(F_S);
  return value;
}//...end Fuzzy_Update();
