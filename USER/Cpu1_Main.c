/**
 *������������������������������+ +
 *�������������������ߩ��������ߩ� + +
 *��������������������������������
 *�������������������������������� ++ + + +
 *������������ ������������������ ��+
 *�������������������������������� +
 *�����������������������ߡ�������
 *�������������������������������� + +
 *��������������������������������
 *����������������������������
 *���������������������������� + + + +
 *������������������������������������Code is far away from bug with the animal protecting
 *���������������������������� + �����������ޱ���,������bug
 *����������������������������
 *��������������������������������+
 *���������������������� �������������� + +
 *�������������������� ���������������ǩ�
 *�������������������� ������������������
 *�����������������������������ש����� + + + +
 *�����������������������ϩϡ����ϩ�
 *�����������������������ߩ������ߩ�+ + + +
 */
#include "headfile.h"
#include "myheadfile.h"
#pragma section all "cpu1_dsram"
//���������#pragma section all restore���֮���ȫ�ֱ���������CPU1��RAM��

// ����㷨��ֵ
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
float upper_speed = 20;     //�����ٶ�
float pre_charging_speed = 50;
uint8 straight_road = 'o';// ֱ�߼��ٱ�־
uint16 charging_state = 'n';// n:ɶ��û�� c:��⵽�����Ȧ�� s:ͣ�����
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
int16 Now_Location = 0; // 0Ϊ��������ǰ  1Ϊͨ������������  2Ϊͨ�����Ĵ�����
int16 Back_To = 0;
float L_Correlation = 0, R_Correlation = 0;// ������ض�
float L_Correlation_dt = 0, R_Correlation_dt = 0;// ������ض�
int16 circle_inter_point_y;
uint8 Low_Charge_Flag = 0;
float V_Bat = 0; //��ص�ѹ
float V_Cap = 0; //���ݵ�ѹ
float I_Charge = 0; //�������
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

IFX_ALIGN(4) volatile uint8 mt9v03x_image_orignal[MT9V03X_H][MT9V03X_W];//������ʾԭʼͼ��buff
IFX_ALIGN(4) volatile uint8 mt9v03x_image_otsu[MT9V03X_H][MT9V03X_W];//�����ֵ����ͼ��
IFX_ALIGN(4) volatile uint8 mt9v03x_image_otsu_xunji[MT9V03X_H][MT9V03X_W];//����ѭ����ͼ��

int16 my_acc_x,my_acc_y,my_acc_z;
int16 my_gyro_x,my_gyro_y,my_gyro_z;
void core1_main(void)
{
	disableInterrupts();
    IfxScuWdt_disableCpuWatchdog(IfxScuWdt_getCpuWatchdogPassword());
    //�û��ڴ˴����ø��ֳ�ʼ��������
    //��ʼ��һ���ݼ�������
    for(int i = 0; i < MT9V03X_H; i++) x_value[i] = i;
//    str_reverse(x_value, MT9V03X_H);
	//�ȴ����к��ĳ�ʼ�����
	IfxCpu_emitEvent(&g_cpuSyncEvent);
	IfxCpu_waitEvent(&g_cpuSyncEvent, 0xFFFF);
    enableInterrupts();
    while (TRUE)
    {
        //�û��ڴ˴���д�������
        if(mt9v03x_finish_flag)
        {
            systick_start(STM1);//����ͼ����ʱ��
            gpio_set(P11_2, 1);

            img_compress(mt9v03x_image[0], mt9v03x_image_orignal[0]);//ͼ��ѹ��
            image_threshold = otsuThreshold(mt9v03x_image_orignal[0],MT9V03X_W,MT9V03X_H);//����㷨����ֵ
            if(image_threshold < 23) image_threshold = 23;//��ֵ����

            // ��ֵ��ͼ��
            for(h = 0;h < MT9V03X_H; h++)
                for(w = 0;w < MT9V03X_W; w++)
                    if(mt9v03x_image_orignal[h][w] > image_threshold)   mt9v03x_image_otsu[h][w] = 0xff;
                    else                                                mt9v03x_image_otsu[h][w] = 0x00;
            for(h = 0;h < MT9V03X_H; h++)
                           for(w = 0;w < MT9V03X_W; w++)
                               if(mt9v03x_image_orignal[h][w] > image_threshold)   mt9v03x_image_otsu_xunji[h][w] = 0xff;
                               else                                                mt9v03x_image_otsu_xunji[h][w] = 0x00;
            // ��1�����Ͳ������˲�
            S_Dilate(mt9v03x_image_otsu[0]);
            S_Dilate(mt9v03x_image_otsu_xunji[0]);
            // Ѱ�ҵײ�������е㣬��ʼѲ��
            bottom_longest_white_line_middle_value = look_for_bottom_longest_white_line_middle(mt9v03x_image_otsu[0]);
            mid_line[MT9V03X_H - 1] = bottom_longest_white_line_middle_value;

            mid_length = mid_line_len(mt9v03x_image_otsu,MT9V03X_W/2);
            width=Get_Width(mt9v03x_image_otsu,37);

            buxian_mode_switch();
//            look_for_fist_left_and_right(mt9v03x_image_otsu_xunji[0],left_side, right_side);
//            look_for_left_right_line(mt9v03x_image_otsu_xunji[0],mid_line,left_side, right_side);
            //look_for_fist_left_and_right(mt9v03x_image_otsu[0],left_side_yuansu, right_side_yuansu);
            //look_for_left_right_line(mt9v03x_image_otsu[0],mid_line_yuansu,left_side_yuansu, right_side_yuansu);
            look_for_mid_line(mt9v03x_image_otsu_xunji[0], mid_line, left_side, right_side);// ������
            look_for_mid_line(mt9v03x_image_otsu[0], mid_line_yuansu, left_side_yuansu, right_side_yuansu);// ������
//            stop_num = CarStop(25);
//            if(stop_num == 1)
//            {
//                car_stop = 1;
//            }

            STOP_CAR(mt9v03x_image_otsu);
            // ����ҵ������߲����� ����������� ��ͣ��
//            if(fit_x_num <= 2) car_stop = 1;
//            // ������Ӧ
//            else {routing_end = fit_x_num; routing_start = fit_x_num - 7;}
//            if(routing_end > routing_end_max) {routing_end = routing_end_max; routing_start = routing_start_max;}
            fix_mid_line(left_side, right_side, mid_line, fix_mid_line_flag);  //������߲���

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

            str_copy(mid_line, mid_line_for_show, MT9V03X_H);   //��һ�����߳���������LCD��ʾ
            str_reverse(mid_line, MT9V03X_H);   //�����������ת����
            for(int i = 0; i < MT9V03X_H; i++)
           {
               mt9v03x_image_otsu_show[i][left_side_yuansu[i] + 2] = 0x00;
               mt9v03x_image_otsu_show[i][right_side_yuansu[i] - 2] = 0x00;
               mt9v03x_image_otsu_show[i][mid_line_for_show[i] - 2] = 0x00;

               mt9v03x_image_otsu_show_xunji[i][left_side[i] + 2] = 0x00;
               mt9v03x_image_otsu_show_xunji[i][right_side[i] - 2] = 0x00;
               mt9v03x_image_otsu_show_xunji[i][mid_line_for_show[i] - 2] = 0x00;

           }
            // ��ֵ�������߲���
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
            // �ж��Ƿ���ֱ��
            if(fit_x_num > routing_end_max + 15)
            {
                if(abs(get_mid_value(mid_line, routing_start_max + 7, routing_start_max + 17) - 47) < 5) straight_road = 'i';
                else straight_road = 'o';
            }
            else   straight_road = 'o';
            gpio_set(P11_2, 0);

            use_time = systick_getval_us(STM1);  //����ͼ�����������ʱ�䣬��λ΢�롣
            mt9v03x_finish_flag = 0;//��ͼ��ʹ����Ϻ�  ��������־λ�����򲻻Ὺʼ�ɼ���һ��ͼ��
            //ע�⣺һ��Ҫ��ͼ��ʹ����Ϻ�������˱�־λ
        }
    }
}

#pragma section all restore
