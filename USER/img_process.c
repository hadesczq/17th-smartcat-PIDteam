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
#include "myheadfile.h"
#include "ipt_map.h"

uint8 Garage_Flag = 0; //�����־
uint8 Flag_Branch_road_CiShu = 0;
// ����㷨 ���в���
uint8 otsuThreshold(uint8 *image, int16 col, int16 row)
{
    #define GrayScale 256
    int16 width = col;
    int16 height = row;
    int pixelCount[GrayScale];
    float pixelPro[GrayScale];
    int i, j, pixelSum = width * height / 4;
    uint8 threshold = 0;
    uint8* data = image;  //ָ���������ݵ�ָ��
    for (i = 0; i < GrayScale; i++)
    {
        pixelCount[i] = 0;
        pixelPro[i] = 0;
    }

    //ͳ�ƻҶȼ���ÿ������������ͼ���еĸ���
    for (i = 0; i < height; i+=2)
    {
        for (j = 0; j < width; j+=2)
        {
            pixelCount[(int)data[i * width + j]]++;  //������ֵ��Ϊ����������±�
        }
    }

    //����ÿ������������ͼ���еı���
    float maxPro = 0.0;
    for (i = 0; i < GrayScale; i++)
    {
        pixelPro[i] = (float)pixelCount[i] / pixelSum;
        if (pixelPro[i] > maxPro)
        {
            maxPro = pixelPro[i];
        }
    }

    //�����Ҷȼ�[0,255]
    float w0, w1, u0tmp, u1tmp, u0, u1, u, deltaTmp, deltaMax = 0;
    for (i = 0; i < GrayScale; i++)     // i��Ϊ��ֵ
    {
        w0 = w1 = u0tmp = u1tmp = u0 = u1 = u = deltaTmp = 0;
        for (j = 0; j < GrayScale; j++)
        {
            if (j <= i)   //��������
            {
                w0 += pixelPro[j];
                u0tmp += j * pixelPro[j];
            }
            else   //ǰ������
            {
                w1 += pixelPro[j];
                u1tmp += j * pixelPro[j];
            }
        }
        u0 = u0tmp / w0;
        u1 = u1tmp / w1;
        u = u0tmp + u1tmp;
        deltaTmp = w0 * pow((u0 - u), 2) + w1 * pow((u1 - u), 2);
        if (deltaTmp > deltaMax)
        {
            deltaMax = deltaTmp;
            threshold = (uint8)i;
        }
    }

    return threshold;
}

void copy_img(uint8 img_in[MT9V03X_H][MT9V03X_W], uint8 img_out[MT9V03X_H][MT9V03X_W])
{
    int16 w, h;
    for(h = 0;h < MT9V03X_H; h++)
        for(w = 0;w < MT9V03X_W; w++)
            img_out[h][w] = img_in[h][w];
}

// ����������е�
int16 look_for_bottom_longest_white_line_middle(uint8 img_in[MT9V03X_H][MT9V03X_W])
{
    int16 i, j = 0, white_lenth = 0, white_lenth_start[20], lenth[20], max = 0, max_i = 0;
    int16 mid;
    // ����Ѱ�Ұ׵�
    for(i = 0; i < MT9V03X_W; i++)
    {
        // �ҵ��׵�
        if(img_in[MT9V03X_H - 1][i] == 0xff)
        {
            white_lenth = 1;
            // �ҳ��׵㳤��
            while((img_in[MT9V03X_H - 1][i + white_lenth] == 0xff) && (i + white_lenth < MT9V03X_W))
            {
                white_lenth ++;
            }
            if(j >= 19) return 0; //��ֹ�������
            // �洢������������
            lenth[j] = white_lenth;
            white_lenth_start[j] = i;
            j++;
        }
        i += white_lenth;
     }
    // û�ҵ��׵� ���ffff����Ϊ����
    if(j == 0) return 0xffff;
    // �ҵ������
    for(i = 0; i < j; i++)
    {
        if(lenth[i] > max) {max = lenth[i];max_i = i;}
    }
    // ��������ߵ��е�
    mid = white_lenth_start[max_i] + 0.5 * lenth[max_i];
    return (mid > MT9V03X_W) ? 0xffff : mid;
}

float abs(float data)
{
    if(data >= 0) return data;
    else return -data;
}

// ������
void look_for_mid_line(uint8 img_in[MT9V03X_H][MT9V03X_W], int16 *data_out, int16 *left_data, int16 *right_data)
{
    int16 i = 0, row = 0;
    uint8_t first_run = 0;
//    data_out[MT9V03X_H - 1] = 40;
    fit_x_num = 0;
    for(row = MT9V03X_H - 1; row > 1; row--)
    {
//        if(row != MT9V03X_H - 1 && abs(data_out[row] - data_out[row + 1]) > 10) data_out[row] = data_out[row - 1];
        if(img_in[row - 1][data_out[row]] == 0xff ) //&& (first_run == 0))
        {
            // ����Ѱ��
            i = data_out[row];
            while(img_in[row - 1][i] == 0xff && i > 0)
            {
                i--;
            }
            left_data[row - 1] = i;
            // ����Ѱ��
            i = data_out[row];
            while(img_in[row - 1][i] == 0xff && i < MT9V03X_W)
            {
                i++;
            }

            right_data[row - 1] = i;
            data_out[row - 1] = (right_data[row - 1] + left_data[row - 1]) / 2;
            fit_x_num++;
        }
        else
        {
            //if(first_run == 0) {/*fit_x_num = MT9V03X_H - row;*/first_run = 1;}
            left_data[row - 1] = left_data[row];
            right_data[row - 1] = right_data[row];
            data_out[row - 1] = 47;
        }
    }
}

void look_for_upper_line(uint8 img_in[MT9V03X_H][MT9V03X_W], int16 *data_out)
{
    uint8 i,j;
    for(i=0;i<MT9V03X_W;i++)
    {
        for(j=MT9V03X_H-1;j>=0;j--)
        {
            if(img_in[j][i]==0||j==0)
            {
              data_out[i]=j;
              break;
            }
        }
    }
}

/************************���Իع��������б�� y = Ax+B*************************/
float regress(int startline, int endline, int16 *mid_line)
{
    int i = 0, SumX = 0, SumY = 0, SumLines = 0;
    float SumUp = 0, SumDown = 0, avrX = 0, avrY = 0, B, A;
    static float last_data = 0;
    SumLines = endline - startline; // startline Ϊ��ʼ�У� //endline ������ //SumLines

    for (i = startline; i < endline; i++)
    {
        SumX += i;
        SumY += mid_line[i]; //����mid_lineΪ������ߵ�����
    }
    avrX = SumX / SumLines; //X��ƽ��ֵ
    avrY = SumY / SumLines; //Y��ƽ��ֵ
    SumUp = 0;
    SumDown = 0;
    for (i = startline; i < endline; i++)
    {
        SumUp += (mid_line[i] - avrY) * (i - avrX);
        SumDown += (i - avrX) * (i - avrX);
    }
//    if (SumDown == 0)
//        B = 0;
//    else
        B = (SumUp / SumDown);
    A = (SumY - B * SumX) / (float)SumLines; //�ؾ�

    last_data = 0.7*B + 0.3*last_data;  //�����˲�
    return last_data;                         //����б��
}


double get_K(int y1, int y2, uint8 *x2) //y1 < y2
{
    double sumk = 0;
    uint8 tx2 = *x2;
    x2--;
    for (int i = y2 - 1; i >= y1; i--)
    {
        if ((y2 - i) != 0)
            sumk += (double)(*x2 - tx2) / (y2 - i);
        x2--;
    }
    if (y2 - y1 != 0)
        return sumk / (y2 - y1);
    else
        return 0;
}


/*---------------------------------------------------------------------------------------
 ����ԭ��: void DPROC_LinearFitting()
 ��    ��: ��������Ķ���������ֵ����ȡ���Իع麯����ϵ���ͽؾ�
 �������: 1��arrayX�������X���ϵ�ָ��
           2��arrayY�������Y���ϵ�ָ��
           3��len�������ĸ���
 �������:
          1��retFactor�����ص����Իع麯����ϵ��
          2��retConstant�����ص����Իع麯���Ľؾ�
 �� �� ֵ: ==0��ʧ�ܣ���Ϊ��������Ƿ�
           !=0���ɹ�
 ע������: NA
---------------------------------------------------------------------------------------*/
void DPROC_LinearFitting(int16_t *arrayX, int16_t *arrayY, int16_t len,float *pRetFactor,float *pRetConstant)
{
    if(arrayX == NULL || arrayX == NULL || len < 2)
        return;

    float x, y;
    int i;

    float sum_x = 0.0f , sum_y = 0.0f , xySum = 0.0f, x2sum = 0.0f;
    for(i = 0 ; i < len ; i++)
    {
         x = arrayX[i];
         y = arrayY[i];
         sum_x += x;
         sum_y += y;
         xySum += x * y;
         x2sum += x * x;
    }
    *pRetFactor=(sum_x * sum_y/len - xySum)/(sum_x * sum_x/len - x2sum);
    x = sum_y - *pRetFactor * sum_x;
    *pRetConstant= x / len;
//    return 1;
}

float get_mid_value(int16 *data, int16 start, int16 end)
{
    int sum = 0;
    for(int i = 0; i < end - start; i++)
        sum += data[start + i];
    return (float)sum  / (end - start);
}

void str_reverse(int16_t *str, int16_t num)
{
    int16_t i;
    int16_t buff[200];

    for(i = 0; i < num; i++)
    {
        buff[i] = str[i];
    }
    for(i = 0; i < num; i++)
    {
        str[i] = buff[num - i];
    }
}

void str_copy(int16_t *str1, int16_t *str2, int16_t num)
{
    int16_t i;
    int16_t buff[200];

    for(i = 0; i < num; i++)
    {
        str2[i] = str1[i];
    }
}

// �˲� ����ûɶЧ��
void Bin_Image_Filter(void)
{
    sint16 nr; //��
    sint16 nc; //��

    for (nr = 1; nr < MT9V03X_H - 1; nr++)
    {
        for (nc = 1; nc < MT9V03X_W - 1; nc = nc + 1)
        {
            if ((mt9v03x_image_otsu[nr][nc] == 0)
                    && (mt9v03x_image_otsu[nr - 1][nc] + mt9v03x_image_otsu[nr + 1][nc] + mt9v03x_image_otsu[nr][nc + 1] + mt9v03x_image_otsu[nr][nc - 1] > 2))
            {
                mt9v03x_image_otsu[nr][nc] = 1;
            }
            else if ((mt9v03x_image_otsu[nr][nc] == 1)
                    && (mt9v03x_image_otsu[nr - 1][nc] + mt9v03x_image_otsu[nr + 1][nc] + mt9v03x_image_otsu[nr][nc + 1] + mt9v03x_image_otsu[nr][nc - 1] < 2))
            {
                mt9v03x_image_otsu[nr][nc] = 0;
            }
        }
    }
}

//SE    ����
//          1
//      1   X   1
//          1
void S_Dilate (uint8 in_IMG[MT9V03X_H][MT9V03X_W])
{
    uint8 i, j;
    //���Ƴ���������     ʹ��ͼ��СһȦ
    uint8 img_H = MT9V03X_H - 1;
    uint8 img_W = MT9V03X_W - 1;
    uint8 S_UP, S_DN, S_LL, S_RR;

    for (i = 1; i < img_H; i++)
    {
        S_UP = i - 1;
        S_DN = i + 1;
        for (j = 1; j < img_W; j++)
        {
            S_LL = j - 1;
            S_RR = j + 1;
            if (in_IMG[i][j] > 1)
            {
                in_IMG[i][j] = 0xff;
                in_IMG[S_UP][j] = 0xff;     //UP
                in_IMG[S_DN][j] = in_IMG[S_DN][j]==0xff?0xff:1;     //DN
                in_IMG[i][S_LL] = 0xff;     //LL
                in_IMG[i][S_RR] = in_IMG[i][S_RR]==0xff?0xff:1;     //RR
            }
        }
    }
    for(i = 0; i < MT9V03X_W; i++)
        if(in_IMG[MT9V03X_H - 1][i] == 1)
            in_IMG[MT9V03X_H - 1][i] = 0xff;
}

////SE    ����
////          0
////      0   X   0
////          0
//void S_Erode (uint8 in_IMG[MT9V03X_H][MT9V03X_W])
//{
//    uint8 i, j;
//    //���Ƴ���������     ʹ��ͼ��СһȦ
//    uint8 img_H = MT9V03X_H - 1;
//    uint8 img_W = MT9V03X_W - 1;
//    uint8 S_UP, S_DN, S_LL, S_RR;
//
//    for (i = 1; i < img_H; i++)
//    {
//        S_UP = i - 1;
//        S_DN = i + 1;
//        for (j = 1; j < img_W; j++)
//        {
//            S_LL = j - 1;
//            S_RR = j + 1;
//            if (in_IMG[i][j] == 0x00)
//            {
//                in_IMG[i][j] = 0x00;
//                in_IMG[S_UP][j] = 0x00;     //UP
//                in_IMG[S_DN][j] = 0x00;     //DN
//                in_IMG[i][S_LL] = 0x00;     //LL
//                in_IMG[i][S_RR] = 0x00;     //RR
//            }
//        }
//    }
//}

// ѭ�����Ͻ�ֱ�����138
// ѭ�����½�ֱ�����158
// ������߲�������
//int16 white_width[16] = {138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153};
//int16 white_width[16] = {85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100};
int16 white_width[16] = {115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130};

void fix_mid_line(int16 *left_line, int16 *right_line, int16 *mid_line, int8 flag)//flag ǿ�Ʋ��߱�־ -1���� +1 �Ҷ���
{
    int16 i, width;
    switch(flag)
    {
        case 0:
            for(i = 0; i < routing_end - routing_start; i++)
            {
                width = right_line[MT9V03X_H - routing_start - i] - left_line[MT9V03X_H - routing_start - i];
                if(left_line[MT9V03X_H - routing_start - i] == 0 && width < 85)// ������߹�����������߶����� ������
                    mid_line[MT9V03X_H - routing_start - i] = right_line[MT9V03X_H - routing_start - i] - white_width[i] / 4;
                if(right_line[MT9V03X_H - routing_start - i] == MT9V03X_W && width < 85)
                    mid_line[MT9V03X_H - routing_start - i] = left_line[MT9V03X_H - routing_start - i] + white_width[i] / 4;
            }
        break;
        case -1:
            for(i = 0; i < routing_end - routing_start; i++)
                mid_line[MT9V03X_H - routing_start - i] = right_line[MT9V03X_H - routing_start - i] - white_width[i] / 6;
        break;
        case 1:
            for(i = 0; i < routing_end - routing_start; i++)
                mid_line[MT9V03X_H - routing_start - i] = left_line[MT9V03X_H - routing_start - i] + white_width[i] / 6;
        break;
        default:break;
    }
}


void cross_road(int16 *left_line, int16 *right_line, int16 *mid_line)
{
    int16 i, j;
    int16 lost_times = 0;
    for(i = 0; i < routing_end - routing_start; i++)
    {
        if(left_line[MT9V03X_H - routing_start - i] == 0 && right_line[MT9V03X_H - routing_start - i] == MT9V03X_W - 1)//���Ҷ�����
        {
            lost_times++;
        }
    }
    if(lost_times > 2)
    {
        routing_start = 95;
        routing_end = 100;
    }
    else
    {
        routing_start = 65;
        routing_end = 80;
    }
}

void img_compress(uint8 in_IMG[2 * MT9V03X_H][2 * MT9V03X_W], uint8 out_IMG[MT9V03X_H][MT9V03X_W])
{
    uint16 i, j;
    for(i = 0; i < MT9V03X_H; i++)
        for(j = 0; j < MT9V03X_W; j++)
            out_IMG[i][j] = in_IMG[2 * i][2 * j];
}

int16 mid_line_len(uint8 in_IMG[MT9V03X_H][MT9V03X_W],uint8 find_add)
{
    int16 i=0,len=0;
    for(i=MT9V03X_H-10;i>0;i--)
    {
        if(in_IMG[i][find_add]==0xff)
        {
            len++;
        }
        else
            break;
    }
    return len;
}

// ��ضȼ���
float Corrcoef(uint16 *A,uint16 *B, uint16 Length)
{
    float sumA, sumB, aveA, aveB;
    uint16 i;
    //���
    sumA=0;
    for(i=0;i<Length;i++)
    {
        sumA+=A[i];
    }
    sumB=0;
    for(i=0;i<Length;i++)
    {
        sumB+=B[i];
    }
    //��ƽ��ֵ
    aveA = sumA / (float)Length;
    aveB = sumB / (float)Length;
    //�������ϵ��
    float R1=0, R2=0, R3=0;
    for (int i = 0; i < Length; i++)
    {
        R1 += (A[i] - aveA) * (B[i] - aveB);
        R2 += pow((A[i] - aveA), 2);
        R3 += pow((B[i] - aveB), 2);
    }
    return (R1 / sqrt(R2*R3));
}

uint8 Circle_Flag_L = 'n';//b����Բ��->mԲ���м�->i����Բ��->sԲ����ѭ��->o��Բ��->g�������� nû��Բ��
uint8 Circle_Flag_R = 'n';
uint16 Circle_Left_CiShu_Flag = 0;
uint16 Right_Diuxian_Flag = 0;
void Is_Right_Diuxian(int16 *right_line)
{
    uint16 count_right = 0;
        for(int i = routing_start; i < routing_end; i++)
           {
               if(right_line[i] == 94)
                   count_right++;
           }
           if(count_right >= 5)
           {
               Right_Diuxian_Flag = 1;
           }
           else   Right_Diuxian_Flag = 0;
}
uint16 Right_Budiu_Diu_Budiu_Flag = 0;
void Right_Budiu_Diu_Budiu()
{

    Is_Right_Diuxian(right_side_yuansu);
    if(Right_Diuxian_Flag == 0 && Right_Budiu_Diu_Budiu_Flag == 0)
    {
        Right_Budiu_Diu_Budiu_Flag = 1;
    }
    if(Right_Diuxian_Flag == 1 && Right_Budiu_Diu_Budiu_Flag == 1)
    {
        Right_Budiu_Diu_Budiu_Flag = 2;
    }
    if(Right_Diuxian_Flag == 0 && Right_Budiu_Diu_Budiu_Flag == 2)
    {
        Right_Budiu_Diu_Budiu_Flag = 3;
    }


}

uint16 Left_Diuxian_Flag = 0;
void Is_Left_Diuxian(int16 *left_line)
{
    uint16 count_left = 0;
    for(int i = routing_start; i < routing_end; i++)
       {
           if(left_line[i] == 0x00)
               count_left++;
       }
       datatft = count_left;
       if(count_left >= 5)
       {
           Left_Diuxian_Flag = 1;
       }
       else   Left_Diuxian_Flag = 0;
}

uint16 Left_Budiu_Diu_Budiu_Flag = 0;
void Left_Budiu_Diu_Budiu()
{

    Is_Left_Diuxian(left_side_yuansu);
    if(Left_Diuxian_Flag == 0 && Left_Budiu_Diu_Budiu_Flag == 0)
    {
        Left_Budiu_Diu_Budiu_Flag = 1;
    }
    if(Left_Diuxian_Flag == 1 && Left_Budiu_Diu_Budiu_Flag == 1)
    {
        Left_Budiu_Diu_Budiu_Flag = 2;
    }
    if(Left_Diuxian_Flag == 0 && Left_Budiu_Diu_Budiu_Flag == 2)
    {
        Left_Budiu_Diu_Budiu_Flag = 3;
    }


}
uint16 ZhunBei_Out_CL_Flag = 0;
uint16 ZhunBei_Out_CL_In_Flag = 0;
void Circle_Left(int16 *left_line, int16 *right_line)
{
    uint16 count = 0;
    uint16 count1 = 0;
    static uint16 quit_g_flag = 0;

    mid_length = mid_line_len(mt9v03x_image_otsu,MT9V03X_W/2);

        switch (Circle_Flag_L)
        {
            case 'n':
                //BEEP_OFF;
                for(int i = routing_start; i < routing_end; i++)
                {
                    if(left_line[i] == 0x00)
                        count++;
                    if(right_line[i]!=MT9V03X_W)
                        count1++;
                }
                if(count >= 5 && count1 >= 5 && mid_length >= 45)
                {
                    if(Circle_Left_CiShu_Flag == 0 && Huihuan_Left_CiShu_Flag != 0)
                    {
                    Circle_Flag_L = 'b';
                    count = 0;
                    count1 = 0;
                    Low_Charge_Flag = 2;
                    }
                }
                else
                    Circle_Flag_L = 'n';
            break;
            case 'b':
                for(int i = routing_start; i < routing_end; i++)
                {
                    if(left_line[i] != 0x00 && right_line[i] != MT9V03X_W)
                        count++;

                }
                if(count>=5)
                {Circle_Flag_L = 'm';count =0;count1=0;break;}
                else
              // Circle_Flag = 'n';
                break;
            case 'm':
                for(int i = routing_start + 5; i < routing_end + 5; i++)
                {
                    if(left_line[i] == 0x00 )
                        count++;
                    if(right_line[i] != MT9V03X_W )
                        count1++;
                }
                if(count >= 5 && count1 >= 5)
                {Circle_Flag_L = 'i';count =0;count1=0;break;}
                else
               // Circle_Flag = 'n';
                break;
            case 'i':
                BEEP_ON;
                //MVF_LENGTH = 1;
                Yuanhuan_In_Left = 1;
                Right_Budiu_Diu_Budiu();
                Huihuan_Left_CiShu_Flag++;
                if(Right_Budiu_Diu_Budiu_Flag == 3)
                {
                    Circle_Flag_L = 's';
                    Right_Budiu_Diu_Budiu_Flag = 0;
                }
            break;
            case 's':
                BEEP_OFF;
                Yuanhuan_In_Left = 0;
                for(int i = routing_start+5; i < routing_start + 7; i++)
                {
                    if(right_line[i] == MT9V03X_W) count++;
                }
                if(count >= 2 && ZhunBei_Out_CL_Flag == 1) Circle_Flag_L = 'o';
            break;
            case 'o':
                BEEP_ON;
                Yuanhuan_Out_Left = 1;
                //MVF_LENGTH = 1;
            break;
            case 'g':
                Circle_Left_CiShu_Flag++;
                MVF_LENGTH = 4;
                //BEEP_ON;
                BEEP_OFF;
            break;
            default:break;
        }

}
uint16 Circle_Right_CiShu_Flag = 0;
uint16 ZhunBei_Out_CR_Flag = 0;
void Circle_Right(int16 *left_line, int16 *right_line)
{
    uint16 count = 0;
    uint16 count1 = 0;

    mid_length = mid_line_len(mt9v03x_image_otsu,MT9V03X_W/2);

        switch (Circle_Flag_R)
        {
            case 'n':
                BEEP_OFF;
                for(int i = routing_start; i < routing_end; i++)
                {
                    if(left_line[i] != 0x00)
                        count++;
                    if(right_line[i] == MT9V03X_W)
                        count1++;
                }
                if(count >= 5 && count1 >= 5 && mid_length >= 45 && Flag_Branch_road_CiShu >= 2) //&& Flag_Branch_road_CiShu >= 2
                {
                    if(Circle_Right_CiShu_Flag == 0)
                    {
                    Circle_Flag_R = 'b';
                    count = 0;
                    count1 = 0;
                    }
                }
                else
                    Circle_Flag_R = 'n';
            break;
            case 'b':
                for(int i = routing_start; i < routing_end; i++)
                {
                    if(left_line[i] != 0x00 && right_line[i] != MT9V03X_W)
                        count++;
                }
                if(count>=5)
                {Circle_Flag_R = 'm';
                count = 0;
                Low_Charge_Flag = 1;
                break;}
                else
              // Circle_Flag = 'n';
                break;
            case 'm':
                for(int i = routing_start+1; i < routing_end+1; i++)
                {
                    if(left_line[i] != 0x00 )
                        count++;
                    if(right_line[i] == MT9V03X_W )
                        count1++;
                }
                if(count >= 5 && count1>=5)
                {Circle_Flag_R = 'i';
                count = 0;
                count1 = 0;
                break;}
                else
               // Circle_Flag = 'n';
                break;
            case 'i':
                BEEP_ON;
                //MVF_LENGTH = 1;
                Yuanhuan_In_Right = 1;
                Left_Budiu_Diu_Budiu();
                if(Left_Budiu_Diu_Budiu_Flag == 3)
                {
                    Circle_Flag_R = 's';
                    Left_Budiu_Diu_Budiu_Flag = 0;
                }
            break;
            case 's':
                BEEP_OFF;
                //MVF_LENGTH = 1;
                Yuanhuan_In_Right = 0;
                Left_Budiu_Diu_Budiu();
                for(int i = 30+5 ; i < 30+7; i++)
                {
                    if(left_line[i] == 0x00) count++;
                }
                if(count >= 2 && ZhunBei_Out_CR_Flag == 1) Circle_Flag_R = 'o';
            break;
            case 'o':
                BEEP_ON;
                Yuanhuan_Out_Right = 1;
                //MVF_LENGTH = 1;
//                Left_Budiu_Diu_Budiu();
//                if(Left_Budiu_Diu_Budiu_Flag == 3)
//                {
//                    Circle_Flag_R = 'g';
//                }
                No_Charge_Flag = 1;
            break;
            case 'g':
                //BEEP_ON;
                Circle_Right_CiShu_Flag++;
                BEEP_OFF;
                MVF_LENGTH = 4;
               // No_Charge_Flag = 1;

            break;
            default:break;
        }

}

char CarStop(char stoplen)
{
    int i = 0;
    for (i = 0; i < stoplen; i++)
    {
        if (mt9v03x_image_otsu[MT9V03X_H - 3 - i][MT9V03X_W / 2])
        {
            return 0;
        }
    }
    return 1;
}


void STOP_CAR(uint8 img_in[MT9V03X_H][MT9V03X_W])
{
    uint8 i=0,j=0;
    uint16 lost=0;
    for(i=0;i<3;i++)
    {
        for(j=0;j<MT9V03X_W;j++)
        {
            if(img_in[MT9V03X_H-i-1][j]==0x00)
            {
                lost++;
            }
        }
    }
    if(lost>=(3*MT9V03X_W)-5)
    {
        car_stop=1;
    }
}
// ���ߺ���
void connect_line(uint8 Pixle[MT9V03X_H][MT9V03X_W], uint8 x1,uint8 y1,uint8 x2,uint8 y2)
{
    int i,j,swap;
    float k;

    k = ((float)(x2-x1))/(y2-y1);
    for(i=y1;i<=y2;i++)
        Pixle[i][(int)(x1+(i-y1)*k)]=0;
}
void ceshi_zuoyouxian(int16 *left_line, int16 *right_line)
{
    //���߰�Ϊ0x00���߰�ΪMT9V03X_W ���ߺ�Ϊ ���ߺ�Ϊ
    for(int i = 30; i < 37; i++)
   {
       if(left_line[i] == 0x00)
           left_num++;
       if(right_line[i] != MT9V03X_W)
           right_num++;

   }
}

int16 Get_Width(uint8 in_IMG[MT9V03X_H][MT9V03X_W],uint8 find_add)
{                          // Y          X
    int16 i=0;
    int16 width_left=0,width_right=0;
    int16 width = 0;
    //���м�������
    for(i=MT9V03X_W/2;i>0;i--)
    {
        if(in_IMG[find_add][i]!=0xff)
        {
            width_left=i;
            break;
        }
    }
    i=0;
    for(i=MT9V03X_W/2;i<MT9V03X_W;i++)
    {
        if(in_IMG[find_add][i]!=0xff)
        {
            width_right=i;
            break;
        }
    }
    width = width_right-width_left;
    return width;
}

uint8 sumline1,sumline2,sancha_count=0;
void Patching_line(uint8 img_in[MT9V03X_H][MT9V03X_W] ,uint8 x1,uint8 y1,uint8 x2,uint8 y2)//���ߺ���������Ԫ����Ҫ���ߣ����ֶ���һ���߽磩
{

  uint8 i,swap;
  float k;
  if(y1>y2)
  {
    swap = x1;
    x1 = x2;
    x2 = swap;
    swap = y1;
    y1 = y2;
    y2 = swap;
  }
  if(x1==x2)
  {
    for(i=y1;i<y2+1;i++)
//      a[i]=y1++;
    img_in[i][x1]=0;
  }
  else if(y1==y2)
  {
    for(i=x1;i<x2+1;i++)
//      a[i]=x1++;
    img_in[y1][i]=0;
  }
  else
  {
    k = ((float)x2-(float)x1)/((float)y2-(float)y1);
    for(i=y1;i<=y2;i++)
    img_in[i][(short)(x1+(i-y1)*k)]=0;
  }
  in_sancha++;
}
static int Lost_line_right(uint8 thres)
{
  uint8 i;
  for(i=thres;i>30;i--)
  if(right_side[i]==MT9V03X_W-1)     return i;
  return -1;
}
static int Lost_line_left(uint8 thres)
{
  uint8 i;
  for(i=thres;i>30;i--)
  if(left_side[i]==0) return i;
  return -1;
}
uint8 in_sancha=0;
void sancha_line(uint8 img_in[MT9V03X_H][MT9V03X_W],int16 *left_line, int16 *right_line)
{
    uint8 min=MT9V03X_W,min_0=1,mini;
    uint8 lx11=0,ly11=0,lx12 = 0,ly12 = 0;
    int lost_r,lost_l;
    lost_r = Lost_line_right(55);
    lost_l = Lost_line_left(4);
    switch(Flag_Branch_road)
    {
                case 1:
                if((lost_r==-1&&lost_l==-1)&&(sumline2 < 3 || sumline1 < 3))
                {
                    Flag_Branch_road=1;
                }
                break;
                default:Flag_Branch_road=0;
                    break;

         }
            if(Flag_Branch_road==1)  //  ʶ������·�ڣ����½��������Ϲյ�
            {
                if(sancha_count==1||sancha_count==2||sancha_count==4||sancha_count==4)
               {
                   //Patching_line(img_in,93,0,0,59);
                    Patching_line(img_in,0,0,93,59);
                    Flag_Branch_road = 0;
                    in_sancha++;
                }
                else
//                else if(sancha_count==2||sancha_count==4)
//                {
//                    Patching_line(img_in,0,0,93,59);
//                }
                if(sancha_count==4)sancha_count=0;
            }
}
void zhaoxiexianyong(uint8 img_in[MT9V03X_H][MT9V03X_W],uint8*left_line,uint8 *right_line)
{
    uint8 i,row,start;
    for(row = 20; row < MT9V03X_H - 20; row++)
        {
            i = 47;

                // ����Ѱ��
            while(img_in[row][i] == 0xff && i > 0)
            {
                i--;
            }
            left_line[row- 20] = i;
            i = 47;
            // ����Ѱ��
            while(img_in[row][i] == 0xff && i < MT9V03X_W)
            {
                i++;
            }
            right_line[row - 20] = i;
        }
}
uint8 count_habs_xiangsu(int8 *line,uint8 dir)
{
    uint8 val=0,i;
    if(dir)
    {
        for(i = 1;i<20;i++)
        if(line[i] > line[i-1])
        {
            val++;
        }
    }
    else
    {
        for(i = 1;i<20;i++)
        if(line[i] < line[i-1])
        {
            val++;
        }
    }
        return val;
}
uint8 Flag_Branch_road = 'n';
void Branch_road_new(uint8 img_in[MT9V03X_H][MT9V03X_W],int16 *left_line, int16 *right_line)
{
        uint8 ll[20],rl[20],mid_len;
        int lost_r,lost_l;
        zhaoxiexianyong(img_in,ll,rl);
        sumline1 = count_habs_xiangsu(ll,1);
        sumline2 = count_habs_xiangsu(rl,0);
        mid_len = mid_line_len(mt9v03x_image_otsu,MT9V03X_W/2);
        switch(Flag_Branch_road)
        {
            case 'n':
                //BEEP_OFF;
           if(sumline1>=5&&sumline2>=5&&Circle_Flag_R=='n'&&Circle_Flag_L=='n'&&mid_len < 40)//&&edge_debug<4&&sumline<50&&sumline>46)/*&&sum_one_line(img_in,1,22)<70&&edge_debug<5&&edge_sum(img_in,49,59,0)<5*///����
           {
               Flag_Branch_road='b';
           }
           else
               Flag_Branch_road = 'n';
           break;
            case 'b':
                lost_r = Lost_line_right(55);
                lost_l = Lost_line_left(4);
                if(((lost_r==-1&&lost_l==-1) && (sumline2 > 3 || sumline1 > 3) && Charge_Num > 1)) //
                {
                    Flag_Branch_road='i';
                    Flag_Branch_road_CiShu++;
                }
           break;
            case 'i':
                BEEP_ON;
                Sancha_In = 1;
            break;
        }
}
uint8 edge_debug,end_flag,end_num;
uint8 edge_sum(uint8 img_in[MT9V03X_H][MT9V03X_W],uint8 height_start,uint8 height_end)
{
    uint8 i,j,buf=0;
    uint16 sum = 0;
    //��Ե�������жϴ�start~end�������м���ͻ��
    for(i = 30;i<=37;i++)
    {
        for(j = 0;j<MT9V03X_W;j++)
        {
            if(img_in[i][j] != buf)
            {
                buf = img_in[i][j];
                sum++;
            }
        }
    }
    sum /=  (height_end-height_start+1);

    edge_debug = (uint8)sum;
}
void cheku_pre_control(uint8 img_in[MT9V03X_H][MT9V03X_W])
{
    static uint16 cheku = 0;
    /*
     * edge_debugs�Ǽ������ļ����ڱ�Ե������ƽ��ֵ,��edge_sum��������м�¼������������Ĳ�����ı�edge_debug������
     *            ͨ���ж����������ȷ���Ƿ���ͣ��λ�ã�ͦ׼�ģ��������õ�����û�����ü�
     * */
    if(edge_debug >= 7)
    {
        end_flag = 1;
        end_num++;
    }
    else
    {
        end_flag = 0;
    }
    if(end_flag)
    {
        if(end_num <4)
        {
            Patching_line(img_in,30,0,30,59);
        }
        if(end_num == 2)
        {
            cheku=1;
        }
    }
    if(cheku==1)
    {
        Patching_line(img_in,93,0,0,59);
        car_stop = 1;
    }
}
uint16 Garage_Go_Success = 0;
uint16 Go_Buxian_Jishi = 0;
void Left_Garage_Go()
{
    if(Garage_Flag == 0)
    {
    Patching_line(mt9v03x_image_otsu_xunji,50,0,80,59);
   // Patching_line(mt9v03x_image_otsu,25,0,25,30);
    if(Charge_Num == 1 && Go_Buxian_Jishi > 110)
        {
          Garage_Flag = 1;
        }
    }

}

void Right_Garage_Go()
{
    if(Garage_Flag == 0)
    {
    Patching_line(mt9v03x_image_otsu_xunji,50,0,20,59);
   // Patching_line(mt9v03x_image_otsu,25,0,25,30);
    if(Charge_Num == 1 && Go_Buxian_Jishi > 100)
        {
          Garage_Flag = 1;
        }
    }

}

uint8 Huihuan_Left_Flag = 'n';
uint16 Huihuan_Left_CiShu_Flag = 0;
uint8 Huihuan_Right_Flag = 'n';
uint16 Huihuan_Right_CiShu_Flag = 0;

void Huihuan_Right(int16 *left_line, int16 *right_line)
{
      uint16 count = 0;
      uint16 count1 = 0;
          switch (Huihuan_Right_Flag)
          {
              case 'n':
                 // BEEP_OFF;
                  for(int i = routing_start+5; i < routing_start+8; i++)
                  {
                      if(left_line[i] == 0x00)
                          count++;
                      if(right_line[i] == MT9V03X_W)
                          count1++;
                  }
                  if(count >= 2 && count1 >= 2)
                  {
                      if(Huihuan_Right_CiShu_Flag == 0 && Garage_Flag == 1 && Zhunbei_Start_Huihuan == 1)//
                      {
                          Huihuan_Right_Flag = 'i';
                          Huihuan_In_Right = 1;
                          BEEP_ON;
                      }
                  }
                  else
                      Huihuan_Right_Flag = 'n';
              break;
          }

}

void Huihuan_Left(int16 *left_line, int16 *right_line)
{
      uint16 count = 0;
      uint16 count1 = 0;
      mid_length = mid_line_len(mt9v03x_image_otsu,MT9V03X_W/2);
          switch (Huihuan_Left_Flag)
          {
              case 'n':
                 // BEEP_OFF;
                  for(int i = routing_start+5; i < routing_start+8; i++)
                  {
                      if(left_line[i] == 0x00)
                          count++;
                      if(right_line[i] == MT9V03X_W)
                          count1++;
                  }
                  if(count >= 2 && count1 >= 2)
                  {
                      if(Huihuan_Left_CiShu_Flag == 0 && Circle_Right_CiShu_Flag != 0 && Circle_Left_CiShu_Flag == 0)// && Circle_Right_CiShu_Flag != 0 && Circle_Left_CiShu_Flag == 0
                      {
                          Huihuan_Left_Flag = 'i';
                          Huihuan_In_Left = 1;
                          BEEP_ON;
                          count = 0;
                          count1 = 0;
                          No_Charge_Flag = 0;
                      }
                  }
                  else
                      Huihuan_Left_Flag = 'n';
              break;
          }

}
uint8 Zebra_Crossing_Num = 0;
uint16 Two_Time_Flag = 0;
void Zebra_Crossing()
{
    if((Now_Location == 0 || Now_Location == 2 || Charge_Num == 5) && Garage_Flag == 1)//(Huihuan_Right_CiShu_Flag != 0) || Flag_Branch_road_CiShu > 3
    {
        edge_sum(mt9v03x_image_otsu,routing_start,routing_end);
        if(edge_debug >= 7&&Two_Time_Flag ==0)
        {
            if((Zebra_Crossing_Num == 1 && Flag_Branch_road_CiShu == 4) || Zebra_Crossing_Num == 0)
            {
            BEEP_ON;
            Zebra_Crossing_Num++;
            Two_Time_Flag = 1;
            }
        }
    }
    if(Zebra_Crossing_Num == 1 && qiangzhi_fix_flag == 0)
    {
        qiangzhi_fix_flag = 1;
        No_Charge_Flag = 0;
    }
    if(Zebra_Crossing_Num == 0 && Garage_Flag == 1)
    {
        No_Charge_Flag = 1;
    }
    if(Zebra_Crossing_Num == 2)
    {
        Back_Garage_Flag = 'i';
        Back_To = 1;
    }
}
uint8 Back_Garage_Flag = 'n';
void Back_Garage()
{
    if(Zebra_Crossing_Num == 2)
    {
        Back_Garage_Flag = 'i';
        Back_To = 1;
    }
}
uint16 datatft;
uint16 tubian_hang = 0;
void Is_Width_Tubian(int16 *left_line, int16 *right_line)
{
    uint16 width_first = 0;
    uint16 width_next = 0;
    uint16 Start_line = 20;
    for(int i = Start_line;i < MT9V03X_H -1;i++)
    {
        width_first = right_line[i] - left_line[i];
        width_next = right_line[i + 1] - left_line[i + 1];
        if(width_next - width_first > 10)
        {
            tubian_hang = i + 1;
            break;
        }
    }
}
uint16 Start_Lost_Line_Right = 0;
uint16 Start_Lost_Line_Left = 0;
uint16 Left_Above_Inflectionpoint[2];//���Ϲյ�
uint16 Left_Below_Inflectionpoint[2];//���¹յ�
uint16 Right_Above_Inflectionpoint[2];//���Ϲյ�
uint16 Right_Below_Inflectionpoint[2];//���¹յ�
void Sao_Line_Diuxian_Inflectionpoint(int16 *left_line, int16 *right_line)
{
    uint16 Right_Lost_Num = 0;
    uint16 Start_line = 20;
    uint16 width_first = 0;
    uint16 width_next = 0;
    for(int i = Start_line;i < MT9V03X_H;i++)
    {
        if(right_line[i] == right_line[i+1])
        {
            if(right_line[i+1] == right_line[i+2])
            {
                if(right_line[i+2] == right_line[i+3])
                {
                    if(right_line[i+3] == 94)
                    {
                        Start_Lost_Line_Right = i+1;
                        break;
                    }
                }
            }
        }
    }
    for(int i = Start_Lost_Line_Right;i < MT9V03X_H -1;i++)
        {
            width_first = right_line[i] - left_line[i];
            width_next = right_line[i + 1] - left_line[i + 1];
            if(width_next - width_first > 10)
            {
                Right_Above_Inflectionpoint[1] = i;
                break;
            }
            if(width_first - width_next > 10)
            {
                Right_Above_Inflectionpoint[1] = i+1;
                break;
            }
        }
    Right_Above_Inflectionpoint[0] = right_line[Right_Above_Inflectionpoint[1]];
    for(int i = Start_Lost_Line_Right;i > 3;i--)
        {
            width_first = right_line[i] - left_line[i];
            width_next = right_line[i - 1] - left_line[i - 1];
            if(width_next - width_first > 10)
            {
                Right_Below_Inflectionpoint[1] = i;
                break;
            }
            if(width_first - width_next > 10)
            {
                Right_Below_Inflectionpoint[1] = i-1;
                break;
            }
        }
    Right_Below_Inflectionpoint[0] = right_line[Right_Below_Inflectionpoint[1]];
    for(int i = Start_line;i < MT9V03X_H;i++)
       {
           if(left_line[i] == left_line[i+1])
           {
               if(left_line[i+1] == left_line[i+2])
               {
                   if(left_line[i+2] == left_line[i+3])
                   {
                       if(left_line[i+3] == 0)
                       {
                           Start_Lost_Line_Left = i+1;
                           break;
                       }
                   }
               }
           }
       }

    for(int i = Start_Lost_Line_Left;i < MT9V03X_H - 1;i++)
           {
               width_first = right_line[i] - left_line[i];
               width_next = right_line[i + 1] - left_line[i + 1];
               if(width_next - width_first > 10)
               {
                   Left_Above_Inflectionpoint[1] = i;
                   break;
               }
               if(width_first - width_next > 10)
               {
                   Left_Above_Inflectionpoint[1] = i + 1;
                   break;
               }
           }
    Left_Above_Inflectionpoint[0] = left_line[Left_Above_Inflectionpoint[1]];

    for(int i = Start_Lost_Line_Left;i > 3;i--)
       {
           width_first = right_line[i] - left_line[i];
           width_next = right_line[i - 1] - left_line[i - 1];
           if(width_next - width_first > 10)
           {
               Left_Below_Inflectionpoint[1] = i;
               break;
           }
           if(width_first - width_next > 10)
           {
               Left_Below_Inflectionpoint[1] = i-1;
               break;
           }
       }
    Left_Below_Inflectionpoint[0] = left_line[Left_Below_Inflectionpoint[1]];


}
int16 abs16(int16 number)
{
    int16 n;
    if(number > 0)
    {
        n = number;
    }
    if(number < 0)
    {
        n = -number;
    }
    return n;
}

void Add_lines(uint16 ax,uint16 ay,uint16 bx,uint16 by)
{
    ay = MT9V03X_H - ay;
    by = MT9V03X_H - by;

    int16 i;
    int16 j;
    int16 n;
    int16 r_flag = 0;

    int16 divisor;
    int16 remainder;

    int16 x;
    int16 y;
    int16 e;

    int8 o;

    if(bx < 47)//�յ�����ߣ���һ
    {
        o = 1;
    }
    if(bx >= 47)//�յ����ұߣ���һ
    {
        o = -1;
    }
    x = ax - bx;
    y = by - ay;
    e = x/abs16(x);
    n = 1;
    if(abs16(x) <= abs16(y))
    {
        j = divisor = y/abs16(x); //��
        remainder = y%abs16(x);  //����
        //������
        mt9v03x_image_otsu_xunji[by][bx] = 0x00;
        mt9v03x_image_otsu_xunji[by][bx+o] = 0x00;

        for(i = 1; i <= y; i++)
        {
            r_flag = 0;
            if(j == 0&&remainder !=0) //�̺�������û����
            {
                remainder--;   //������һ
                r_flag = 1;
            }
            if(j != 0)   //��û����
            {
                j--;
            }
            if(remainder == 0) //����������
            {
                r_flag = 1;
            }
            mt9v03x_image_otsu_xunji[by-i][bx+n*e] = 0x00;
            mt9v03x_image_otsu_xunji[by-i][bx+n*e+o] = 0x00;
            if(j == 0 && r_flag == 1) //�̺�������������
            {
                n++;  //��һ��
                j = divisor;
            }
        }

    }
    n = 1;
    if(abs16(x) > abs16(y))
    {
        j = divisor = abs16(x)/y;
        remainder = abs16(x)%y;
        mt9v03x_image_otsu_xunji[ay][ax] = 0x00;
        mt9v03x_image_otsu_xunji[ay][ax+o] = 0x00;
        for(i = 1; i <= abs16(x); i++)
        {
            r_flag = 0;
            if(j == 0&&remainder !=0)
            {
                remainder--;
                r_flag = 1;
            }
            if(j != 0)
            {
                j--;
            }
            if(remainder == 0)
            {
                r_flag = 1;
            }
            mt9v03x_image_otsu_xunji[ay+n][ax-e*i] = 0x00;
            mt9v03x_image_otsu_xunji[ay+n][ax-e*i+o] = 0x00;
            if(j == 0 && r_flag == 1)
            {
                n++;
                j = divisor;
            }
        }
    }
}

void look_for_fist_left_and_right(uint8 img_in[MT9V03X_H][MT9V03X_W],int16 *left_data, int16 *right_data)
{
    uint8 i=0;
    uint8 len=0;
    for(i = MT9V03X_W/2;i>0; i--)
    {
        len++;
        if(img_in[MT9V03X_H-1][i]==0x00)
        {
            left_data[MT9V03X_H-1]=i;
            break;
        }
    }
    if(len==94)
    {
        left_data[MT9V03X_H-1]=0;
    }
    len=0;
    for(i = MT9V03X_W/2;i<MT9V03X_W; i++)
    {
        len++;
        if(img_in[MT9V03X_H-1][i]==0x00)
        {
            right_data[MT9V03X_H-1]=i;
            break;
        }
    }
    if(len==94)
    {
        right_data[MT9V03X_H-1]=MT9V03X_W-1;
    }
}

void look_for_left_right_line(uint8 img_in[MT9V03X_H][MT9V03X_W],int16 *out_data,int16 *left_data, int16 *right_data)
{
    uint8 i=0;
    int16 j=0;
    uint8 len=0;
    for(i=MT9V03X_H-2;i>0;i--)
    {
        out_data[i+1]=(left_data[i+1]+right_data[i+1])/2;
        for(j=out_data[i+1];j>0;j--)
        {
            len++;
            if(img_in[i][j]==0x00)
            {
                left_data[i]=j;
                break;
            }
        }
        if(len==out_data[i+1])
        {
            left_data[i]=0;
        }
        len=0;
        for(j=out_data[i+1];j<MT9V03X_W;j++)
        {
            len++;
            if(img_in[i][j]==0x00)
            {
                right_data[i]=j;
                break;
            }
        }
        if(len==MT9V03X_W-out_data[i+1])
        {
            right_data[i]=MT9V03X_W-1;
        }
        len=0;
    }
}

/*����ƽ���˲�������*/
//#define MVF_LENGTH 4   //ֱ��
int MVF_LENGTH = 4;
float moving_average_filtre(float xn)
{
  static int index = -1;
  static float buffer[4];
  static float sum = 0;
  float yn = 0;
  int i = 0;
  if(index == -1)
  {
    //��ʼ��
    for(i = 0; i <MVF_LENGTH; i++)
    {
      buffer[i] = xn;
    }
    sum = xn*MVF_LENGTH;
    index = 0;
  }
  else
  {
    sum -= buffer[index];
    buffer[index] = xn;
    sum += xn;
    index++;
    if(index >= MVF_LENGTH)
    {
      index = 0;
    }
  }
  yn = sum/MVF_LENGTH;
  return yn;
}

void buxian_mode_switch()
{
    Right_Garage_Go();
    //Left_Garage_Go();
    //Garage_Flag = 1;
    if(Flag_Branch_road == 'i')
    {
       // Patching_line(mt9v03x_image_otsu,30,0,30,59);
       // Patching_line(mt9v03x_image_otsu_xunji,60,0,25,59);
        Patching_line(mt9v03x_image_otsu_xunji,30,0,75,59);
        BEEP_ON;
    }
    if(Circle_Flag_L == 'b')
       {
           Patching_line(mt9v03x_image_otsu_xunji,30,0,5,59);
       }
    if(Circle_Flag_L == 'i')
    {
       // Patching_line(mt9v03x_image_otsu_xunji,40,0,30,59);
     //   Patching_line(mt9v03x_image_otsu_xunji,30,0,90,59);
    }
    if(Circle_Flag_L == 'o')
    {
     //   Patching_line(mt9v03x_image_otsu_xunji,35,0,591,59);
        //Add_lines(23,50,Right_Below_Inflectionpoint[0],Right_Below_Inflectionpoint[1]);
    }
    if(Circle_Flag_L == 'g')
  {
      Patching_line(mt9v03x_image_otsu_xunji,40,0,30,59);
     // Add_lines(Left_Above_Inflectionpoint[0],Left_Above_Inflectionpoint[1],10,1);
  }
    if(Circle_Flag_R == 'b')
    {
        Patching_line(mt9v03x_image_otsu_xunji,60,0,80,59);
    }
    if(Circle_Flag_R == 'i')
    {
//        Patching_line(mt9v03x_image_otsu,60,0,80,59);
//        Patching_line(mt9v03x_image_otsu_xunji,60,0,80,59);
        Circle_Flag_L = 'n';
    }
    if(Circle_Flag_R == 'o')
    {
        Add_lines(75,50,Left_Below_Inflectionpoint[0],Left_Below_Inflectionpoint[1]);
        Circle_Flag_L = 'n';
    }
    if(Circle_Flag_R == 'g' && car_stop == 0)
  {

      Patching_line(mt9v03x_image_otsu,60,0,80,59);
      Patching_line(mt9v03x_image_otsu_xunji,60,0,80,59);
      //BEEP_ON;
  }
    if(Huihuan_Left_Flag == 'i')
    {
        Patching_line(mt9v03x_image_otsu_xunji,40,0,80,59);
    }
    if(Huihuan_Right_Flag == 'i')
    {
        Patching_line(mt9v03x_image_otsu_xunji,65,0,20,59);
      //  Huihuan_Right_CiShu_Flag ++;
        //BEEP_ON;
    }
//  if(Circle_Flag_R == 'g' && mid_length < 35)
//  {
//      Circle_Flag_R = 'n';
//      BEEP_OFF;
//  }
    if(Back_Garage_Flag == 'i')
    {
        Patching_line(mt9v03x_image_otsu_xunji,20,0,90,59);
    }
}
uint8 Eight_Xun_X[8] = {1,1,0,-1,-1,-1,0,1};
uint8 Eight_Xun_Y[8] = {0,1,1,1,0,-1,-1,-1};
void Eight_Find_Line(uint8 img_in[MT9V03X_H][MT9V03X_W], int16 *left_data, int16 *right_data)
{
    //ȷ����ʼ����
    uint8 Start_Find_Line_Left[2];
    uint8 Start_Find_Line_Right[2];
    uint8 Now_Start_Find_Line_Left[2];
    uint8 Now_Start_Find_Line_Right[2];
    for(int i = MT9V03X_H -1; i > 0 ;i--)
    {
        for(int j = MT9V03X_W / 2; j < MT9V03X_W - 1 ; j++)
        {
            if(img_in[i][j] == 0x00)
            {
                Start_Find_Line_Right[0] = j;
                Start_Find_Line_Right[1] = i;
                break;
            }
        }
    }
    for(int i = MT9V03X_H -1; i > 0 ;i--)
       {
           for(int j = MT9V03X_W / 2; j > 0 ; j--)
           {
               if(img_in[i][j] == 0x00)
               {
                   Start_Find_Line_Left[0] = j;
                   Start_Find_Line_Left[1] = i;
                   break;
               }
           }
       }
    //     3  2  1
    //     4  *  0
    //     5  6  7
    for(int i = 0; i < 6 ; i++)
    {
        if(img_in[Start_Find_Line_Left[1] + Eight_Xun_Y[i]][Start_Find_Line_Left[0] + Eight_Xun_X[i]] == 0x00)
        {
            Now_Start_Find_Line_Left[0] = Start_Find_Line_Left[0] + Eight_Xun_X[i];
            Now_Start_Find_Line_Left[1] = Start_Find_Line_Left[1] + Eight_Xun_Y[i];

        }
    }
}
void Now_Location_Judge()
{
    if(Flag_Branch_road_CiShu < 2)
    {
        Now_Location = 0;
    }
    if(Flag_Branch_road_CiShu >= 2 && Flag_Branch_road_CiShu <4)
    {
        Now_Location = 1;
    }
    if(Flag_Branch_road_CiShu >= 4 )
    {
        Now_Location = 2;
    }

}
