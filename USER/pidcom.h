#ifndef _PIDCOM_H_
#define _PIDCOM_H_

#include "pid.h"

//#define XP_PIDCOM_NOFEEDBACK  1
#include "myheadfile.h"

#define SEND(data, length)  uart_putbuff(UART_0, data, length)
#define PWM_START()         (flag = 1)
#define TIM_START()         0
#define PWM_STOP()          (flag = 0)
#define TIM_STOP()          0
#define RET_ZERO()          0

enum PID_CMD
{
    TEST = 0,
	OK = 1,

    CHANGEVAL_PID = 11,
    CHANGEVAL_TARGET = 12,
    START = 13,
    STOP = 14,

    CHANGEVAL_SLAVE = 21,
    START_SLAVE = 22,
    STOP_SLAVE = 23
};

typedef struct DataFrame
{
    unsigned int head;
    unsigned char command;
    unsigned char datasize;
    float kP;
    float kI;
    float kD;
    float target;
    unsigned int check;
}PID_DF;

typedef struct DataStream
{
    unsigned int head;
    float actual;
}PID_STREAM;

typedef union PacketOfPID
{
    PID_DF pid;
    unsigned char byte[sizeof(PID_DF)];
}PacketOfPID;

typedef union PacketOfStream
{
    PID_STREAM pidStream;
    unsigned char byte[sizeof(PID_STREAM)];
}PacketOfStream;

int PID_ComMain(unsigned char *buf, float *kP, float *kI, float *kD, float *target);
PID_STREAM PID_StreamSend(float value);
PID_DF PID_SlaveStart(float kP, float kI, float kD, float target);
PID_DF PID_SlaveStop(float value);
PID_DF PID_SlaveChangeVal(float kP, float kI, float kD, float target);

#endif
//4F5A5850回馈，0x435A5850发送指令头，0x445A5850发送流头
