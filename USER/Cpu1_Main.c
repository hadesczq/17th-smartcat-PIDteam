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
#include "headfile.h"
#include "myheadfile.h"
#pragma section all "cpu1_dsram"
//将本语句与#pragma section all restore语句之间的全局变量都放在CPU1的RAM中

// 大津算法阈值
int16 w, h;
uint8 image_threshold;
int16 bottom_longest_white_line_middle_value;
int16 mid_line[MT9V03X_H];
int16 mid_line_for_show[MT9V03X_H];
int16 mid_line_yuansu[MT9V03X_H];
int16 mid_line_for_show_yuansu[MT9V03X_H];
float mid_slope;
float mid_const;
int16 mid_length;
int16 width;

int16 x_value[MT9V03X_H];
int16_t fit_x_num;
int8 fix_mid_line_flag = 0;
int16 left_side[MT9V03X_H];
int16 left_side_1[MT9V03X_H];
int16 left_side_yuansu[MT9V03X_H];
int16 right_side[MT9V03X_H];
int16 right_side_1[MT9V03X_H];
int16 right_side_yuansu[MT9V03X_H];
int16 left_side_for_show[MT9V03X_H];
int16 right_side_for_show[MT9V03X_H];
int16 up_side[MT9V03X_W];
int16 down_side[MT9V03X_W];
int16 branch_road_left[12];
int16 branch_road_right[12];
uint8 Flag_branch_road_left=0;
uint8 Flag_branch_road_right=0;
int16 use_time;
uint8 car_stop = 0;
float running_speed = 140;
float upper_speed = 20;     //加速速度
float pre_charging_speed = 50;
uint8 straight_road = 'o';// 直线加速标志
uint16 charging_state = 'n';// n:啥事没有 c:检测到充电线圈了 s:停车充电
uint8 cross_flag = 'n';
uint16 No_Charge_Flag = 0;
int16 routing_start_max = 20;
int16 routing_end_max = 27;
int16 routing_start = 20;
int16 routing_end = 27;
int16 routing_start_yuansu = 30;
int16 routing_end_yuansu = 37;
int16 stop_num;
int16 qiangzhi_fix_flag = 0;
int16 Now_Location = 0; // 0为两次三岔前  1为通过了两次三岔  2为通过了四次三岔
int16 Back_To = 0;
float L_Correlation = 0, R_Correlation = 0;// 左右相关度
float L_Correlation_dt = 0, R_Correlation_dt = 0;// 左右相关度
int16 circle_inter_point_y;
uint8 Low_Charge_Flag = 0;
float V_Bat = 0; //电池电压
float V_Cap = 0; //电容电压
float I_Charge = 0; //电流检测
int16 Yuanhuan_In_Right = 0;
int16 Yuanhuan_Out_Right = 0;
int16 Yuanhuan_In_Left = 0;
int16 Yuanhuan_Out_Left = 0;
int16 Huihuan_In_Right = 0;
int16 Huihuan_In_Left = 0;
int16 Zhunbei_Rush = 0;
int16 Sancha_In = 0;
float Get_A16;
float Get_A13;
uint16 Charge_Num = 0;
uint16 Charger_Sensor_Distant, Charger_Sensor_Close;
int16 Charger_Sensor_Close_dt;
int Speed_up = 0;
int Speed_Select[4] = {0,9,12,20};
int16 Zhunbei_Start_Huihuan = 0;

int error_num = 0;
int left_num=0;
int right_num=0;
int Temp_xianshi = 0;
int16 debug_charge_pingbi = 0;

IFX_ALIGN(4) volatile uint8 mt9v03x_image_orignal[MT9V03X_H][MT9V03X_W];//用于显示原始图像buff
IFX_ALIGN(4) volatile uint8 mt9v03x_image_otsu[MT9V03X_H][MT9V03X_W];//定义二值化后图像
IFX_ALIGN(4) volatile uint8 mt9v03x_image_otsu_xunji[MT9V03X_H][MT9V03X_W];//定义循迹用图像

int16 my_acc_x,my_acc_y,my_acc_z;
int16 my_gyro_x,my_gyro_y,my_gyro_z;
void core1_main(void)
{
	disableInterrupts();
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    //用户在此处调用各种初始化函数等
    //初始化一个递减的数列
    for(int i = 0; i < MT9V03X_H; i++) x_value[i] = i;
//    str_reverse(x_value, MT9V03X_H);
	//等待所有核心初始化完毕
	IfxCpu_emitEvent(&g_cpuSyncEvent);
	IfxCpu_waitEvent(&g_cpuSyncEvent, 0xFFFF);
    enableInterrupts();
    while (TRUE)
    {
        //用户在此处编写任务代码
        if(mt9v03x_finish_flag)
        {
            systick_start(STM1);//计算图像处理时长
            gpio_set(P11_2, 1);

            img_compress(mt9v03x_image[0], mt9v03x_image_orignal[0]);//图像压缩
            image_threshold = otsuThreshold(mt9v03x_image_orignal[0],MT9V03X_W,MT9V03X_H);//大津算法算阈值
            if(image_threshold < 23) image_threshold = 23;//阈值下限

            // 二值化图像
            for(h = 0;h < MT9V03X_H; h++)
                for(w = 0;w < MT9V03X_W; w++)
                    if(mt9v03x_image_orignal[h][w] > image_threshold)   mt9v03x_image_otsu[h][w] = 0xff;
                    else                                                mt9v03x_image_otsu[h][w] = 0x00;
            for(h = 0;h < MT9V03X_H; h++)
                           for(w = 0;w < MT9V03X_W; w++)
                               if(mt9v03x_image_orignal[h][w] > image_threshold)   mt9v03x_image_otsu_xunji[h][w] = 0xff;
                               else                                                mt9v03x_image_otsu_xunji[h][w] = 0x00;
            // 跑1次膨胀操作，滤波
            S_Dilate(mt9v03x_image_otsu[0]);
            S_Dilate(mt9v03x_image_otsu_xunji[0]);
            // 寻找底部最长白线中点，开始巡线
            bottom_longest_white_line_middle_value = look_for_bottom_longest_white_line_middle(mt9v03x_image_otsu[0]);
            mid_line[MT9V03X_H - 1] = bottom_longest_white_line_middle_value;

            mid_length = mid_line_len(mt9v03x_image_otsu,MT9V03X_W/2);
            width=Get_Width(mt9v03x_image_otsu,37);

            buxian_mode_switch();
//            look_for_fist_left_and_right(mt9v03x_image_otsu_xunji[0],left_side, right_side);
//            look_for_left_right_line(mt9v03x_image_otsu_xunji[0],mid_line,left_side, right_side);
            //look_for_fist_left_and_right(mt9v03x_image_otsu[0],left_side_yuansu, right_side_yuansu);
            //look_for_left_right_line(mt9v03x_image_otsu[0],mid_line_yuansu,left_side_yuansu, right_side_yuansu);
            look_for_mid_line(mt9v03x_image_otsu_xunji[0], mid_line, left_side, right_side);// 找中线
            look_for_mid_line(mt9v03x_image_otsu[0], mid_line_yuansu, left_side_yuansu, right_side_yuansu);// 找中线
//            stop_num = CarStop(25);
//            if(stop_num == 1)
//            {
//                car_stop = 1;
//            }

            STOP_CAR(mt9v03x_image_otsu);
            // 如果找到的中线不够长 代表出赛道了 就停车
//            if(fit_x_num <= 2) car_stop = 1;
//            // 中线适应
//            else {routing_end = fit_x_num; routing_start = fit_x_num - 7;}
//            if(routing_end > routing_end_max) {routing_end = routing_end_max; routing_start = routing_start_max;}
            fix_mid_line(left_side, right_side, mid_line, fix_mid_line_flag);  //弯道丢线补线

//            Add_lines(Right_Above_Inflectionpoint[0],Right_Above_Inflectionpoint[1],0,0);
            copy_img(mt9v03x_image_otsu[0], mt9v03x_image_otsu_show[0]);
            copy_img(mt9v03x_image_otsu_xunji[0], mt9v03x_image_otsu_show_xunji[0]);
            for(int i = 0; i < MT9V03X_W; i++)
            {
//                mt9v03x_image_otsu_show[MT9V03X_H-Left_Above_Inflectionpoint[1]][i] = 0x00;
//                mt9v03x_image_otsu_show[MT9V03X_H-Right_Below_Inflectionpoint[1]][i] = 0x00;
                mt9v03x_image_otsu_show[MT9V03X_H - routing_start][i] = 0x00;
                mt9v03x_image_otsu_show[MT9V03X_H - routing_end][i] = 0x00;
                mt9v03x_image_otsu_show_xunji[MT9V03X_H - routing_start][i] = 0x00;
                mt9v03x_image_otsu_show_xunji[MT9V03X_H - routing_end][i] = 0x00;

            }

            str_copy(mid_line, mid_line_for_show, MT9V03X_H);   //拷一份中线出来，用于LCD显示
            str_reverse(mid_line, MT9V03X_H);   //把中线数组调转方向
            for(int i = 0; i < MT9V03X_H; i++)
           {
               mt9v03x_image_otsu_show[i][left_side_yuansu[i] + 2] = 0x00;
               mt9v03x_image_otsu_show[i][right_side_yuansu[i] - 2] = 0x00;
               mt9v03x_image_otsu_show[i][mid_line_for_show[i] - 2] = 0x00;

               mt9v03x_image_otsu_show_xunji[i][left_side[i] + 2] = 0x00;
               mt9v03x_image_otsu_show_xunji[i][right_side[i] - 2] = 0x00;
               mt9v03x_image_otsu_show_xunji[i][mid_line_for_show[i] - 2] = 0x00;

           }
            // 均值法算中线参数
            DPROC_LinearFitting(x_value, mid_line + routing_start, routing_end - routing_start, &mid_slope, &mid_const);
            mid_const = get_mid_value(mid_line, routing_start, routing_end);
            str_copy(left_side, left_side_for_show, MT9V03X_H);
            str_copy(right_side, right_side_for_show, MT9V03X_H);
            str_reverse(left_side, MT9V03X_H);
            str_reverse(right_side, MT9V03X_H);
            str_reverse(left_side_yuansu, MT9V03X_H);
            str_reverse(right_side_yuansu, MT9V03X_H);
           // Sao_Line_Diuxian_Inflectionpoint(left_side_yuansu, right_side_yuansu);
            Circle_Right(left_side_yuansu, right_side_yuansu);
          //  Left_Budiu_Diu_Budiu();
            Branch_road_new(mt9v03x_image_otsu,left_side, right_side);
            Huihuan_Left(left_side_yuansu, right_side_yuansu);
            Huihuan_Right(left_side_yuansu, right_side_yuansu);
            Circle_Left(left_side_yuansu, right_side_yuansu);

            Now_Location_Judge();
            Zebra_Crossing();
            edge_sum(mt9v03x_image_otsu,routing_start,routing_end);
            mid_length = mid_line_len(mt9v03x_image_otsu,MT9V03X_W/2);
            // 判断是否在直道
            if(fit_x_num > routing_end_max + 15)
            {
                if(abs(get_mid_value(mid_line, routing_start_max + 7, routing_start_max + 17) - 47) < 5) straight_road = 'i';
                else straight_road = 'o';
            }
            else   straight_road = 'o';
            gpio_set(P11_2, 0);

            use_time = systick_getval_us(STM1);  //计算图像处理程序消耗时间，单位微秒。
            mt9v03x_finish_flag = 0;//在图像使用完毕后  务必清除标志位，否则不会开始采集下一幅图像
            //注意：一定要在图像使用完毕后在清除此标志位
        }
    }
}

#pragma section all restore
