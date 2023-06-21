#include <myheadfile.h>
#include <headfile.h>
#include <string.h>

#define RXBUFFERSIZE 1

float Variable[20];     //变量
float Parameter[20];    //参数
float test1;
int16 adc_result[60];

uint8 SendPara,send_data_contorl=0,Save_Flag=0;

char RxBuffer[RXBUFFERSIZE];
uint8 aRxBuffer;
uint8 Uart1_Rx_Cnt = 0;


void my_putchar(uint8 temp)
{
    uart_putchar(UART_0, temp);
}

void vofa_send_float(float dat)
{
    my_putchar(BYTE0(dat));
    my_putchar(BYTE1(dat));
    my_putchar(BYTE2(dat));
    my_putchar(BYTE3(dat));
}

void vofa_send_end(void)
{
    my_putchar(0x00);
    my_putchar(0x00);
    my_putchar(0x80);
    my_putchar(0x7f);
}

/*用来通知上位机新的一组数据开始，要保存数据必须发送它*/
void Send_Begin()
{ 
  my_putchar(0x55);
  my_putchar(0xaa);
  my_putchar(0xae);
}

//测试数据生产 1
void Testdata_generate()    //generate生成
{
    Variable[0]=Turning_PID.k_p;
    Variable[1]=L_Motor_PID.feedback;
    Variable[2]=R_Motor_PID.feedback;
    Variable[3]=L_Motor_PID.input;
    Variable[4]=R_Motor_PID.input;
    Variable[5]=Turning_PID.output;
    Variable[6]=Turning_PID.input;
    Variable[12]=L_Motor_PID.output;
    Variable[13]=R_Motor_PID.output;
    Variable[14]=V_Bat;
    Variable[15]=V_Cap;
//    Variable[4]=100 * R_Correlation_dt;
//    Variable[5]=R_Correlation<-0.99?100 * (L_Correlation_dt - R_Correlation_dt):0;
//    Variable[6]=70 * atan(Turning_PID.feedback / 100);
//    Variable[7]=Turning_PID.feedback;
//    Variable[8]=L_Motor_PID.output;
//    Variable[9]=L_Motor_PID.output;
//
//    Variable[10]=Charger_Sensor_Distant;
//    Variable[11]=Charger_Sensor_Close_dt;
//    Variable[12]=Charge_PID.output;
//    Variable[13]=V_Bat;
//    Variable[14]=V_Cap;
//    Variable[15]=V_Cap*I_Charge;
//	Variable[1]=IfxScuCcu_getPllFrequency()/1000;
//	Variable[2]=IfxScuCcu_getCpuFrequency(IfxCpu_getCoreIndex())/1000;
//	Variable[3]=IfxScuCcu_getSpbFrequency()/1000;
//	Variable[4]=IfxStm_getFrequency(&MODULE_STM0)/1000;
//	Variable[5]=adc_result[0];
//	Variable[6]=adc_result[1];
//	Variable[7]=adc_result[2];
//	Variable[8]=adc_result[3];
//	Variable[9]=adc_result[4];
//	Variable[10]=adc_result[5];

}

//发送变量
// Variable 变量 1
void Send_Variable()
{
  uint8 i=0,ch=0;
  float temp=0;
  uint8 Variable_num=16;
  my_putchar(0x55);
  my_putchar(0xaa);
  my_putchar(0xad);
  my_putchar(Variable_num);
  for(i=0;i<Variable_num;i++)
  {
    temp=Variable[i];
    ch=BYTE0(temp);
    my_putchar(ch);
    ch=BYTE1(temp);
    my_putchar(ch);
    ch=BYTE2(temp);
    my_putchar(ch);
    ch=BYTE3(temp);
    my_putchar(ch);
  }
  my_putchar(0x0d);
}

//修改 参数
void Modify_Parameter(uint8 *buff)     //Modify 修改 Parameter参数
{
  uint8 i=0,addr=0;
  float temp;
  uint8 Parameter_num=14; //14个可改参数
  /*          修改参数数组         */
  for(i=0;i<Parameter_num;i++)
  {
    BYTE0(temp)=*(uint8*)(buff+addr);
    addr++;
    BYTE1(temp)=*(uint8*)(buff+addr);
    addr++;
    BYTE2(temp)=*(uint8*)(buff+addr);
    addr++;
    BYTE3(temp)=*(uint8*)(buff+addr);
    addr++;
    Parameter[i]=temp;
  }
      L_Motor_PID.k_p=Parameter[0];
      L_Motor_PID.k_i=Parameter[1];
      L_Motor_PID.k_d=Parameter[2];
      R_Motor_PID.k_p=Parameter[3];
      R_Motor_PID.k_i=Parameter[4];
      R_Motor_PID.k_d=Parameter[5];
      Turning_PID.k_p=Parameter[6];
      Turning_PID.k_i=Parameter[7];
      Turning_PID.k_d=Parameter[8];
      running_speed = Parameter[9];
}

//发送参数
void Send_Parameter()
{
  uint8 i=0,ch=0;
  float temp=0;
  uint8 Parameter_num=14;  //14个可改参数
  
  /*         将参数值更新到参数数组中  示例         */
    Parameter[0]=L_Motor_PID.k_p;
    Parameter[1]=L_Motor_PID.k_i;
    Parameter[2]=L_Motor_PID.k_d;
    Parameter[3]=R_Motor_PID.k_p;
    Parameter[4]=R_Motor_PID.k_i;
    Parameter[5]=R_Motor_PID.k_d;
    Parameter[6]=Turning_PID.k_p;
    Parameter[7]=Turning_PID.k_i;
    Parameter[8]=Turning_PID.k_d;
    Parameter[9]=running_speed;
  
  my_putchar(0x55);
  my_putchar(0xaa);
  my_putchar(0xab);
  my_putchar(Parameter_num);
  for(i=0;i<Parameter_num;i++)
  {
    temp=Parameter[i];
    ch=BYTE0(temp);
    my_putchar(ch);
    ch=BYTE1(temp);
    my_putchar(ch);
    ch=BYTE2(temp);
    my_putchar(ch);
    ch=BYTE3(temp);
    my_putchar(ch);
  }
  my_putchar(0X0b);//帧尾
}

void send_init()//上位机发数据初始化
{
  if(SendPara)
  {
     SendPara=0;
     Send_Parameter();
  }
  Send_Begin();
  Testdata_generate();
  Send_Variable();
}

void my_debug(unsigned char tmp)
{
  static uint8 recv;
  static uint8 data_cnt=0;
  static uint8 predata[10];
  static uint8 Recv_Buff[100];
  static uint8 Data_Receiving=0;   //Data_Receiving数据接收
  
  //if(uart_query(uart1)==1)  uart_getchar (uart1,(uint8*)(&recv));  //根据实际的串口来修改     uart_query查询是否接收到一个字节     uart_getchar等待接收 1 个字节
  /**********代表正在接收来自上位机的参数数据*********/
	recv = tmp;

  if(Data_Receiving)
  {
    if(data_cnt<56)
    {
      Recv_Buff[data_cnt]= recv;
      data_cnt++;
    }
    else
    {
      data_cnt=0;    //达到帧长
      Data_Receiving=0;
      if(recv==0xab)  //帧尾
      {
        Modify_Parameter(Recv_Buff);
        SendPara=1;      //参数回传，确认参数修改完成
        Save_Flag=1;
      }
    }
  }
  else
  {
    // beep=1; //开启蜂鸣器
    
    switch(recv)         //判断功能字
    {
    case 0x30:           //车模启停开关 收到数据后可以控制小车的启动和停
        L_Motor_PID.err_x = 0;
        R_Motor_PID.err_x = 0;
        Turning_PID.err_x = 0;
        if(car_stop == 0)
            car_stop = 1;
        else
            car_stop = 0;
      break;
      
    case 0x31:           //数据发送开关


      /*********由于数据发送时要占用部分CPU资源和运行时间，小车运行时不建议发送数据，所以可以关闭发送*********/
      break;
      
    case 0x32:           //读取参数
      if(SendPara==0)
        SendPara=1;
      break;        
    case 0X33:             //修改参数
      Data_Receiving=1;
      data_cnt=0;
      break;
    case 0X34:             //保存参数
      break;
      
    case 0X35:             //SD卡数据保存开关
      
      break;
      
    case 0X36:             //读取SD卡数据保存起始扇区的信息
      
      break;
      
    case 0X37:             //SD卡上一帧
      
      break;
      
    case 0X38:             //SD卡下一帧
      
      break;
      
    case 0X39:             //扇区跳转
      
      break;
      
      
    default:           //
      break;
    }
  }
  predata[3]=predata[2];
  predata[2]=predata[1];
  predata[1]=predata[0];
  predata[0]=recv;
}

void ZW_Send_Image(ZW_uint8 ZW_Image[ZW_ImgSize_H][ZW_ImgSize_W])
{
    ZW_uint8 ZW_data = 0;
    ZW_uint8 ZW_i,ZW_j;
    for(ZW_i=0;ZW_i<ZW_ImgSize_H;ZW_i++)
    {
        for(ZW_j=0;ZW_j<ZW_ImgSize_W/8;ZW_j++)
        {
            ZW_data = 0;
            if(ZW_Image[ZW_i][ZW_j*8+0])    ZW_data |= 0x01<<7;
            if(ZW_Image[ZW_i][ZW_j*8+1])    ZW_data |= 0x01<<6;
            if(ZW_Image[ZW_i][ZW_j*8+2])    ZW_data |= 0x01<<5;
            if(ZW_Image[ZW_i][ZW_j*8+3])    ZW_data |= 0x01<<4;
            if(ZW_Image[ZW_i][ZW_j*8+4])    ZW_data |= 0x01<<3;
            if(ZW_Image[ZW_i][ZW_j*8+5])    ZW_data |= 0x01<<2;
            if(ZW_Image[ZW_i][ZW_j*8+6])    ZW_data |= 0x01<<1;
            if(ZW_Image[ZW_i][ZW_j*8+7])    ZW_data |= 0x01<<0;
            ZW_Putchar(ZW_data);
        }
        ZW_data = 0;
        for(ZW_j=0;ZW_j<ZW_ImgSize_W%8;ZW_j++)
        {
            if(ZW_Image[ZW_i][(ZW_ImgSize_W-ZW_ImgSize_W%8)+ZW_j])  ZW_data |= 0x01<<(7-ZW_j);
        }
        ZW_Putchar(ZW_data);
        ZW_data = 0;
    }
}
