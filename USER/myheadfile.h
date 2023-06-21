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

#ifndef USER_MYHEADFILE_H_
#define USER_MYHEADFILE_H_

#include <headfile.h>
#include "lvgl.h"
#include "ws2812.h"
#include "fuzzy.h"
#include "ladrc.h"

//#define IMG_IPT_H   120
//#define IMG_IPT_W   188

#define BEEP_ON         gpio_set(P11_6, 0)
#define BEEP_OFF        gpio_set(P11_6, 1)

#define BYTE0(Temp)       (*(char *)(&Temp))
#define BYTE1(Temp)       (*((char *)(&Temp) + 1))
#define BYTE2(Temp)       (*((char *)(&Temp) + 2))
#define BYTE3(Temp)       (*((char *)(&Temp) + 3))

#define L_DIR   P21_2
#define R_DIR   P21_4
#define para1   2.5
#define para2   10
extern int16 my_acc_x,my_acc_y,my_acc_z;
extern int16 my_gyro_x,my_gyro_y,my_gyro_z;
extern int16 routing_start_max;
extern int16 routing_end_max;
extern int16 routing_start;
extern int16 routing_end;
extern int16 routing_start_yuansu;
extern int16 routing_end_yuansu;
extern int16 x_value[MT9V03X_H];
extern int16 width;
extern int16 branch_road_left[12];
extern int16 branch_road_right[12];
extern uint8 Flag_branch_road_left;
extern uint8 Flag_branch_road_right;
extern uint8 Flag_Branch_road;
extern int16 L_Motor_Pulse;
extern int16 R_Motor_Pulse;
extern int16 L_Motor_Pulse_Integral;
extern int16 R_Motor_Pulse_Integral;

void Get_Pulse(void);//获取脉冲
void Zero_Pulse_Integral(void);
void buxian_mode_switch();
void Branch_road_new(uint8 img_in[MT9V03X_H][MT9V03X_W],int16 *left_line, int16 *right_line);
extern uint8 in_sancha;
void Patching_line(uint8 img_in[MT9V03X_H][MT9V03X_W] ,uint8 x1,uint8 y1,uint8 x2,uint8 y2);
extern float running_speed;
extern float upper_speed;
extern int error_num;

extern int left_num,right_num;
void ceshi_zuoyouxian(int16 *left_line, int16 *right_line);
extern float V_Bat;
extern float V_Cap;
extern float I_Charge;

extern float Variable[20];
extern float Parameter[20];
extern uint8 aRxBuffer;
extern uint8 SendPara,send_data_contorl,Save_Flag;
extern float test1;
extern int16 adc_result[60];
extern uint16 Huihuan_Left_CiShu_Flag;
void Huihuan_Left(int16 *left_line, int16 *right_line);

void vofa_send_float(float dat);
void vofa_send_end(void);
void Testdata_generate();
void Send_Begin();
void Send_Parameter();
void Send_Variable();
void send_init();
void my_debug(unsigned char tmp);
char CarStop(char stoplen);

/****************图传代码************************/
/*图像尺寸大小        切记必须与上位机填写的尺寸对应否则无法使用*/
/*图像尺寸大小        不得超过 长×宽<=10000*/
#define     ZW_ImgSize_H        60
#define     ZW_ImgSize_W        94

/*UART数据发宏定义    需要用户更改为自己的UART发送函数*/
#define     ZW_Putchar(ZW_data)     uart_putchar(UART_0, ZW_data);

/*数据类型*/
typedef         unsigned char       ZW_uint8;

/*函数声明*/
void ZW_Send_Image(ZW_uint8 ZW_Image[ZW_ImgSize_H][ZW_ImgSize_W]);

void my_lvinit(void);
void lv_showimg(uint8 p[MT9V03X_H][MT9V03X_W]);

extern volatile uint8 mt9v03x_image_otsu[MT9V03X_H][MT9V03X_W];
extern volatile uint8 mt9v03x_image_otsu_xunji[MT9V03X_H][MT9V03X_W];
extern volatile uint8 mt9v03x_image_otsu_show[MT9V03X_H][MT9V03X_W];
extern volatile uint8 mt9v03x_image_otsu_show_xunji[MT9V03X_H][MT9V03X_W];
extern uint8 image_threshold;
extern int16 use_time;
// 给LVGL显示用变量
extern volatile uint8 mt9v03x_image_for_lvgl[MT9V03X_H][MT9V03X_W];
extern volatile uint8 mt9v03x_image1_for_lvgl[MT9V03X_H][MT9V03X_W];
extern volatile uint8 mt9v03x_image_orignal[MT9V03X_H][MT9V03X_W];

extern lv_obj_t * img1_p;
extern lv_obj_t * label1_p;

// 定义lvgl显示图像类型结构体
//static lv_img_dsc_t my_img_dsc = {
//    .header.always_zero = 0,
//    .header.w = 188,
//    .header.h = 120,
//    .data_size = 188 * 120 * LV_COLOR_DEPTH / 8,
//    .header.cf = LV_IMG_CF_ALPHA_8BIT,          /*Set the color format*/
//    .data = mt9v03x_image_for_lvgl,
//};
//
//static lv_img_dsc_t my_img1_dsc = {
//    .header.always_zero = 0,
//    .header.w = 188,
//    .header.h = 120,
//    .data_size = 188 * 120 * LV_COLOR_DEPTH / 8,
//    .header.cf = LV_IMG_CF_ALPHA_8BIT,          /*Set the color format*/
//    .data = mt9v03x_image1_for_lvgl,
//};


extern int16 bottom_longest_white_line_middle_value;
extern int16 mid_line[MT9V03X_H];
extern int16 mid_line_for_show[MT9V03X_H];
extern float mid_slope, mid_const;
extern int16 mid_length;
extern int16 fit_x_num;
extern int8 fix_mid_line_flag;
extern int16 left_side[MT9V03X_H];
extern int16 left_side_1[MT9V03X_H];
extern int16 left_side_yuansu[MT9V03X_H];
extern int16 right_side[MT9V03X_H];
extern int16 right_side_1[MT9V03X_H];
extern int16 right_side_yuansu[MT9V03X_H];
extern int16 left_side_for_show[MT9V03X_H];
extern int16 right_side_for_show[MT9V03X_H];
extern int16 mid_line_yuansu[MT9V03X_H];
extern int16 mid_line_for_show_yuansu[MT9V03X_H];
extern int16 up_side[MT9V03X_W];
extern int16 down_side[MT9V03X_W];
extern uint8 car_stop;
extern float L_Correlation, R_Correlation;
extern float L_Correlation_dt, R_Correlation_dt;
extern uint8 Circle_Flag_L;
extern uint8 Circle_Flag_R;
extern uint8 Huihuan_Left_Flag;
extern float left_side_slope, left_side_const;
extern float right_side_slope, right_side_const;
extern uint8 straight_road;
extern int16 circle_inter_point_y;
extern uint8 Flag_Branch_road_CiShu;
extern uint8 edge_debug;
extern uint8 Zebra_Crossing_Num;
extern uint8 Huihuan_Right_Flag;
extern uint16 Huihuan_Right_CiShu_Flag;
extern uint16 Two_Time_Flag;
extern uint8 Back_Garage_Flag;
extern uint16 Garage_Go_Success;
extern int16 qiangzhi_fix_flag;
void Zebra_Crossing();
extern uint16 datatft;
extern uint16 Left_Diuxian_Flag;
void Is_Left_Diuxian(int16 *left_line);
extern uint16 Left_Budiu_Diu_Budiu_Flag;
void Left_Budiu_Diu_Budiu();
extern uint16 ZhunBei_Out_CR_Flag;
extern uint16 ZhunBei_Out_CL_Flag;
extern uint16 Right_Diuxian_Flag;
extern uint16 Right_Budiu_Diu_Budiu_Flag;
void Is_Width_Tubian(int16 *left_line, int16 *right_line);
extern uint16 tubian_hang;
extern uint16 Left_Above_Inflectionpoint[2];//左上拐点
extern uint16 Left_Below_Inflectionpoint[2];//左下拐点
extern uint16 Right_Above_Inflectionpoint[2];//右上拐点
extern uint16 Right_Below_Inflectionpoint[2];//右下拐点
void Add_lines(uint16 ax,uint16 ay,uint16 bx,uint16 by);
void look_for_fist_left_and_right(uint8 img_in[MT9V03X_H][MT9V03X_W],int16 *left_data, int16 *right_data);
void look_for_left_right_line(uint8 img_in[MT9V03X_H][MT9V03X_W],int16 *out_data,int16 *left_data, int16 *right_data);
void STOP_CAR(uint8 img_in[MT9V03X_H][MT9V03X_W]);
extern uint16 ZhunBei_Out_CL_In_Flag;
extern uint16 No_Charge_Flag;
extern uint8 Low_Charge_Flag;
float moving_average_filtre(float xn);
extern float Filtre_Mid;
extern int MVF_LENGTH;
extern uint16 Circle_Right_CiShu_Flag;
extern uint16 Circle_Left_CiShu_Flag;
extern int16 Now_Location;
extern int16 Back_To;
extern int16 Yuanhuan_In_Right;
extern int16 Yuanhuan_Out_Right;
extern int16 Yuanhuan_In_Left;
extern int16 Yuanhuan_Out_Left;
extern int16 debug_charge_pingbi;
extern int16 Huihuan_In_Right;
extern int16 Huihuan_In_Left;
extern int16 Zhunbei_Rush;
extern int16 Sancha_In;
extern int Temp_xianshi;
extern int Speed_Select[4];
extern int Speed_up;
// image process

/******逆透视变换******/
//输入图片尺寸
#define CAMERA_H  120
#define CAMERA_W  188
//输出图片尺寸
#define OUT_H  60
#define OUT_W  94

extern uint8 sumline1,sumline2;
float abs(float data);
int16 mid_line_len(uint8 in_IMG[MT9V03X_H][MT9V03X_W],uint8 find_add);
uint8 otsuThreshold(uint8 *image, int16 col, int16 row);
void copy_img(uint8 img_in[MT9V03X_H][MT9V03X_W], uint8 img_out[MT9V03X_H][MT9V03X_W]);
int16 look_for_bottom_longest_white_line_middle(uint8 img_in[MT9V03X_H][MT9V03X_W]);
void look_for_mid_line(uint8 img_in[MT9V03X_H][MT9V03X_W], int16 *data_out, int16 *left_data, int16 *right_data);
//void look_for_upper_line(uint8 img_in[MT9V03X_H][MT9V03X_W], int16 *data_out);
float regress(int startline, int endline, int16 *mid_line);
double get_K(int y1, int y2, uint8 *x2);
void DPROC_LinearFitting(int16_t *arrayX, int16_t *arrayY, int16_t len,float *pRetFactor,float *pRetConstant);
float get_mid_value(int16 *data, int16 start, int16 end);
void str_reverse(int16_t *str, int16_t num);
void str_copy(int16_t *str1, int16_t *str2, int16_t num);
void Bin_Image_Filter(void);//去除噪点
void S_Dilate (uint8 in_IMG[MT9V03X_H][MT9V03X_W]);
void S_Erode (uint8 in_IMG[MT9V03X_H][MT9V03X_W]);
void fix_mid_line(int16 *left_line, int16 *right_line, int16 *mid_line, int8 flag);
void cross_road(int16 *left_line, int16 *right_line, int16 *mid_line);
void img_compress(uint8 in_IMG[2 * MT9V03X_H][2 * MT9V03X_W], uint8 out_IMG[MT9V03X_H][MT9V03X_W]);
float Corrcoef(uint16 *A,uint16 *B, uint16 Length);
void Circle_Left(int16 *left_line, int16 *right_line);
void Circle_Right(int16 *left_line, int16 *right_line);
uint16 look_for_line_turning_small_point(int16 *line, int16 size);
void connect_line(uint8 Pixle[MT9V03X_H][MT9V03X_W], uint8 x1,uint8 y1,uint8 x2,uint8 y2);

typedef struct
{
    float input;
    float output;
    float feedback;
    float k_p;
    float k_i;
    float k_d;
    float err_1;
    float err_2;
    float err_x;

    float out_max;
    float out_min;
    float err_x_max;
}PID;

extern PID L_Motor_PID, R_Motor_PID, Turning_PID, Charge_PID;
extern PID Turning_PID_Speed1, Turning_PID_Speed2;

void PID_Init(void);
void PID_Cal(PID *pid);
void Motor_PWM_Set(float L, float R);
void Motor_PID(void);

extern uint16 Charger_Sensor_Distant, Charger_Sensor_Close;
extern int16 Charger_Sensor_Close_dt;
extern float pre_charging_speed;
extern uint16 charging_state;

extern float Get_A16;
extern float Get_A13;
extern uint16 Charge_Num;
extern uint8 Garage_Flag;
extern uint16 Go_Buxian_Jishi;
void ADC_Init(void);
float Get_Bat_V(void);
float Get_Cap_V(void);
float Get_Charge_I(void);
float Get_Charger_Pos(uint16 *Distant_Value, uint16 *Close_Value);
float Get_Jiance_A16(void);
float Get_Jiance_A13(void);
extern int16 Zhunbei_Start_Huihuan;
#endif /* USER_MYHEADFILE_H_ */
