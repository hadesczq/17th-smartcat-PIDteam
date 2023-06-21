#include <myheadfile.h>
#include <headfile.h>
#include <string.h>

#define RXBUFFERSIZE 1

float Variable[20];     //����
float Parameter[20];    //����
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

/*����֪ͨ��λ���µ�һ�����ݿ�ʼ��Ҫ�������ݱ��뷢����*/
void Send_Begin()
{ 
  my_putchar(0x55);
  my_putchar(0xaa);
  my_putchar(0xae);
}

//������������ 1
void Testdata_generate()    //generate����
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

//���ͱ���
// Variable ���� 1
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

//�޸� ����
void Modify_Parameter(uint8 *buff)     //Modify �޸� Parameter����
{
  uint8 i=0,addr=0;
  float temp;
  uint8 Parameter_num=14; //14���ɸĲ���
  /*          �޸Ĳ�������         */
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

//���Ͳ���
void Send_Parameter()
{
  uint8 i=0,ch=0;
  float temp=0;
  uint8 Parameter_num=14;  //14���ɸĲ���
  
  /*         ������ֵ���µ�����������  ʾ��         */
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
  my_putchar(0X0b);//֡β
}

void send_init()//��λ�������ݳ�ʼ��
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
  static uint8 Data_Receiving=0;   //Data_Receiving���ݽ���
  
  //if(uart_query(uart1)==1)  uart_getchar (uart1,(uint8*)(&recv));  //����ʵ�ʵĴ������޸�     uart_query��ѯ�Ƿ���յ�һ���ֽ�     uart_getchar�ȴ����� 1 ���ֽ�
  /**********�������ڽ���������λ���Ĳ�������*********/
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
      data_cnt=0;    //�ﵽ֡��
      Data_Receiving=0;
      if(recv==0xab)  //֡β
      {
        Modify_Parameter(Recv_Buff);
        SendPara=1;      //�����ش���ȷ�ϲ����޸����
        Save_Flag=1;
      }
    }
  }
  else
  {
    // beep=1; //����������
    
    switch(recv)         //�жϹ�����
    {
    case 0x30:           //��ģ��ͣ���� �յ����ݺ���Կ���С����������ͣ
        L_Motor_PID.err_x = 0;
        R_Motor_PID.err_x = 0;
        Turning_PID.err_x = 0;
        if(car_stop == 0)
            car_stop = 1;
        else
            car_stop = 0;
      break;
      
    case 0x31:           //���ݷ��Ϳ���


      /*********�������ݷ���ʱҪռ�ò���CPU��Դ������ʱ�䣬С������ʱ�����鷢�����ݣ����Կ��Թرշ���*********/
      break;
      
    case 0x32:           //��ȡ����
      if(SendPara==0)
        SendPara=1;
      break;        
    case 0X33:             //�޸Ĳ���
      Data_Receiving=1;
      data_cnt=0;
      break;
    case 0X34:             //�������
      break;
      
    case 0X35:             //SD�����ݱ��濪��
      
      break;
      
    case 0X36:             //��ȡSD�����ݱ�����ʼ��������Ϣ
      
      break;
      
    case 0X37:             //SD����һ֡
      
      break;
      
    case 0X38:             //SD����һ֡
      
      break;
      
    case 0X39:             //������ת
      
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
