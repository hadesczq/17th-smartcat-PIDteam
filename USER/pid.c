/**
 *　　　　　　　　┏┓　　　┏┓+ +
 *　　　　　　　┏┛┻━━━┛┻┓ + +
 *　　　　　　　┃　　　　　　　┃
 *　　　　　　　┃　　　━　　　┃ ++ + + +
 *　　　　　　 ████━████ ┃+
 *　　　　　　　┃　　　　　　　┃ +
 *　　　　　　　┃　　　┻　　　┃
 *　　　　　　　┃　　　　　　　┃ + +
 *　　　　　　　┗━┓　　　┏━┛
 *　　　　　　　　　┃　　　┃
 *　　　　　　　　　┃　　　┃ + + + +
 *　　　　　　　　　┃　　　┃　　　　Code is far away from bug with the animal protecting
 *　　　　　　　　　┃　　　┃ + 　　　　神兽保佑,代码无bug
 *　　　　　　　　　┃　　　┃
 *　　　　　　　　　┃　　　┃　　+
 *　　　　　　　　　┃　 　　┗━━━┓ + +
 *　　　　　　　　　┃ 　　　　　　　┣┓
 *　　　　　　　　　┃ 　　　　　　　┏┛
 *　　　　　　　　　┗┓┓┏━┳┓┏┛ + + + +
 *　　　　　　　　　　┃┫┫　┃┫┫
 *　　　　　　　　　　┗┻┛　┗┻┛+ + + +
 */
#include "myheadfile.h"

PID L_Motor_PID, R_Motor_PID, Turning_PID, Charge_PID;
PID Turning_PID_Speed1, Turning_PID_Speed2;
int16 L_Motor_Pulse = 0;
int16 R_Motor_Pulse = 0;
int16 L_Motor_Pulse_Integral = 0;
int16 R_Motor_Pulse_Integral = 0;
float Filtre_Mid = 0;
void PID_Init(void)
{
       L_Motor_PID.k_p = 52;//110
       L_Motor_PID.k_i = 0.5;//2
       L_Motor_PID.k_d = 250;//50
       L_Motor_PID.out_max = 9000;
       L_Motor_PID.out_min = -9000;
       L_Motor_PID.input = 0;
       L_Motor_PID.err_x_max = 500;

       R_Motor_PID.k_p = 59.5;//85
       R_Motor_PID.k_i = 0;//1.4
       R_Motor_PID.k_d = 50;//23
       R_Motor_PID.out_max = 9000;
       R_Motor_PID.out_min = -9000;
       R_Motor_PID.input = 0;
       R_Motor_PID.err_x_max = 500;

    Turning_PID.k_p = 1.78;//0.5
    Turning_PID.k_i = 0.001;//0.1
    Turning_PID.k_d = 1;//1.5
    Turning_PID.input = 0;
    Turning_PID.out_max = 300;//+-300
    Turning_PID.out_min = -300;
    Turning_PID.err_x_max = 30;//30

    Turning_PID_Speed1.k_p = 1.2;
    Turning_PID_Speed1.k_i = 0;
    Turning_PID_Speed1.k_d = 1.7;

    Turning_PID_Speed2.k_p = 0.2;
    Turning_PID_Speed2.k_i = 0;
    Turning_PID_Speed2.k_d = 0.1;

    Charge_PID.k_p = 200;
    Charge_PID.k_i = 50;
    Charge_PID.k_d = 0;
    Charge_PID.input = 10;
    Charge_PID.out_max = 9000;
    Charge_PID.out_min = 1000;
    Charge_PID.err_x_max = 300;
}

void PID_Cal(PID *pid)
{
    float p, i, d;

    pid->err_2 = pid->err_1;
    pid->err_1 = pid->input - pid->feedback;

    p = pid->k_p * pid->err_1;
    i = pid->k_i * pid->err_x;
    d = pid->k_d * (pid->err_1 - pid->err_2);
    pid->err_x += pid->err_1;
    pid->output = p + i + d;

    if(pid->output > pid->out_max)      pid->output = pid->out_max;
    if(pid->output < pid->out_min)      pid->output = pid->out_min;
    if(pid->err_x > pid->err_x_max)     pid->err_x = pid->err_x_max;
}

void Motor_PWM_Set(float L, float R)
{
    if(L > 0)   {gpio_set(L_DIR, 0);pwm_duty(ATOM0_CH1_P21_3, L);}  //0110
    else        {gpio_set(L_DIR, 1);pwm_duty(ATOM0_CH1_P21_3, -L);}
    if(R > 0)   {gpio_set(R_DIR, 1);pwm_duty(ATOM0_CH3_P21_5, R);}
    else        {gpio_set(R_DIR, 0);pwm_duty(ATOM0_CH3_P21_5, -R);}
}

float speed;

void PID_Tuning(void)
{
    static float last_feedback = 0;
}

void Get_Boma_speed()
{
    if(gpio_get(P11_9) == 1)
       {
        Speed_up = Speed_Select[0];
       }
    else if(gpio_get(P11_10) == 1)
    {
        Speed_up = Speed_Select[1];
    }
    else if(gpio_get(P11_11) == 1)
    {
        Speed_up = Speed_Select[2];
    }
    else if(gpio_get(P11_12) == 1)
    {
        Speed_up = Speed_Select[3];
    }
    else
    {
        Speed_up = 0;
    }
}
void Speed_Tuning(void)     // 速度调整
{
    static uint16 tms1 = 0;
    static uint16 tms2 = 0;

   // Get_Boma_speed();
    if(Flag_Branch_road_CiShu == 1 && Zhunbei_Rush == 0)
    {
        Zhunbei_Rush = 1;
    }

    if(Zhunbei_Rush == 2 )
    {
        running_speed = 150;
    }
    else if(Zhunbei_Rush == 3)
    {
        running_speed = 110;
    }
    else if(Flag_Branch_road_CiShu == 2 && Charge_Num != 3)
    {
        running_speed = 110;
    }
    else if(Charge_Num == 2 && Flag_Branch_road_CiShu == 2)
    {
        running_speed = 110;
    }
    else if(Charge_Num == 3)
    {
        running_speed = 100;
    }
    else
        running_speed = 110;

    if(Charge_Num == 5)
    {
        running_speed = 120;
        MVF_LENGTH = 4;
    }
}

void Get_Pulse(void)//获取脉冲
{
    L_Motor_Pulse = -gpt12_get(GPT12_T4)/2;
    R_Motor_Pulse = gpt12_get(GPT12_T2)/2;
}
void Zero_Pulse_Integral(void)//清零
{
    L_Motor_Pulse_Integral = 0;
    R_Motor_Pulse_Integral = 0;
}
uint16 Zero_Flag = 0;
uint16 Zero_Num = 0;
void Motor_PID(void)    //10ms
{
    static uint16 tms = 0;
      static float L_Speed = 0, R_Speed = 0;
      float speed_a = 0.3;
      // 保存上次编码器的值
      L_Speed = L_Motor_PID.feedback;
      R_Speed = R_Motor_PID.feedback;
      // 获取当前电机转速 用了一阶滤波 也可以不滤波
      R_Motor_PID.feedback = (1 - speed_a) * gpt12_get(GPT12_T4)/2 + speed_a * R_Speed;
      L_Motor_PID.feedback = -(1 - speed_a) * gpt12_get(GPT12_T2)/2 + speed_a * L_Speed;
      R_Motor_Pulse = gpt12_get(GPT12_T4)/2;
      L_Motor_Pulse = -gpt12_get(GPT12_T2)/2;
      if(L_Motor_Pulse < 0)
      {
          L_Motor_Pulse = 0;
      }
      if(R_Motor_Pulse < 0)
      {
          R_Motor_Pulse = 0;
      }
      L_Motor_Pulse_Integral = L_Motor_Pulse_Integral + L_Motor_Pulse;
      R_Motor_Pulse_Integral = R_Motor_Pulse_Integral + R_Motor_Pulse;
      gpt12_clear(GPT12_T2);
      gpt12_clear(GPT12_T4);
      Speed_Tuning();
      //- 左 +右
      Filtre_Mid = moving_average_filtre(para1 * (mid_const - 47) + para2 * mid_slope);
      if(Garage_Flag == 0)
      {
          Turning_PID.feedback = 25;
      }
      if(Back_To == 1)
      {
          Turning_PID.feedback = 70; // 110  50
          BEEP_ON;
      }
      if(Yuanhuan_In_Right == 1)
      {
          Turning_PID.feedback = 12;
      }
      if(Yuanhuan_Out_Right == 1)
      {
          Turning_PID.feedback = 45; //110  35
         // No_Charge_Flag = 1;
      }
      if(Yuanhuan_In_Left == 1)
      {
          Turning_PID.feedback = -23;
      }
      if(Yuanhuan_Out_Left == 1)
      {
          Turning_PID.feedback = -36; //110 -28
      }
      if(Zebra_Crossing_Num == 1 && qiangzhi_fix_flag == 1)
      {
          Turning_PID.feedback = 7;
      }
      if(Huihuan_In_Right == 1)
        {
            Turning_PID.feedback = 50;
        }
        if(Huihuan_In_Left == 1)
        {
            Turning_PID.feedback = -60;
        }

//        if(Sancha_In == 1)
//        {
//            Turning_PID.feedback = -30;
//        }
      //
      if(Garage_Flag != 0  && Back_Garage_Flag != 'i' && Back_To != 1 &&
              Yuanhuan_In_Right != 1 && Yuanhuan_Out_Right != 1 &&
              Yuanhuan_In_Left != 1 && Yuanhuan_Out_Left != 1 &&qiangzhi_fix_flag != 1
              && Huihuan_In_Right != 1 && Huihuan_In_Left != 1)
       {
           Turning_PID.feedback = Filtre_Mid;
       }
      if(Zhunbei_Rush == 2)
      {

          Turning_PID.feedback = Filtre_Mid + 10;
      }

      if(car_stop)
      {
          R_Motor_PID.input = 0;
          L_Motor_PID.input = 0;
          R_Motor_PID.err_x = 0;
          L_Motor_PID.err_x = 0;
      }
      else
      {
          tms++;
          if(tms >= 2)
          {
              tms = 0;
              if(abs(Turning_PID.feedback - Turning_PID.output) < 10)
              {
                 // BEEP_ON;
              }
              else
              {
                  //BEEP_OFF;
              }

              if(charging_state == 'b')
             {
                 speed = pre_charging_speed;
             }
               else
               {
                   speed = running_speed;
               }
              PID_Cal(&Turning_PID);  // 转向环PID
              if(Turning_PID.output > 0)  //给电机赋转速值的时候 左右轮给不同的比例
              {
                  L_Motor_PID.input = speed - 1.5 * Turning_PID.output;//1.5
                  R_Motor_PID.input = speed + 0.9 * Turning_PID.output;//0.9
              }
              else
              {
                  L_Motor_PID.input = speed - 0.9 * Turning_PID.output;//0.9
                  R_Motor_PID.input = speed + 1.5 * Turning_PID.output;//1.5
              }

//              if(Turning_PID.output > 0)
//              {
//                  L_Motor_PID.input = speed - 1.5 * Turning_PID.output;
//                  R_Motor_PID.input = speed + 0.9 * Turning_PID.output;
//              }
//              else
//              {
//                  L_Motor_PID.input = speed - 0.9 * Turning_PID.output;
//                  R_Motor_PID.input = speed + 1.5 * Turning_PID.output;
//              }
          }
      }


      PID_Cal(&L_Motor_PID);
      PID_Cal(&R_Motor_PID);

      Motor_PWM_Set(L_Motor_PID.output, R_Motor_PID.output);

}
