
#include "pidcom.h"
						

int PID_ComMain(unsigned char *buf, float *kP, float *kI, float *kD, float *target)
{
	PID_DF *pidrecv = (PID_DF *)buf;
	PID_DF piddf;
	if(pidrecv->head == 0x435A5850)
	{
		if(pidrecv->check == sizeof(PID_DF) * 8)
		{
			switch(pidrecv->command)
			{
			case START:
			
				piddf.head = 0x4F5A5850;		
				piddf.command = START;	
				piddf.check = sizeof(PID_DF) * 8;
				
				SEND((unsigned char *)&piddf, sizeof(PID_DF));

//				PWM_START();
//				TIM_START();

				return pidrecv->command;
			case STOP:
			
				piddf.head = 0x4F5A5850;		
				piddf.command = STOP;
				piddf.check = sizeof(PID_DF) * 8;
				
				SEND((unsigned char *)&piddf, sizeof(PID_DF));	
		
//				PWM_STOP();
//				TIM_STOP();
//				RET_ZERO();

				return pidrecv->command;
			case CHANGEVAL_PID:
			
				*kP = (double)pidrecv->kP;
				*kI = (double)pidrecv->kI;
				*kD = (double)pidrecv->kD;
			
				piddf.head = 0x4F5A5850;		
				piddf.command = CHANGEVAL_PID;		
				piddf.check = sizeof(PID_DF) * 8;
				
				SEND((unsigned char *)&piddf, sizeof(PID_DF));
				
				return pidrecv->command;
			case CHANGEVAL_TARGET:
			
				*target = (float)pidrecv->target;
			
				piddf.head = 0x4F5A5850;		
				piddf.command = CHANGEVAL_TARGET;		
				piddf.check = sizeof(PID_DF) * 8;
				
				SEND((unsigned char *)&piddf, sizeof(PID_DF));

				return pidrecv->command;
			default:
				return pidrecv->command;
			}
		}
		else
		{
			//鏍￠獙閿欒
		}
	}
	else if(pidrecv->head == 0x4F5A5850)
	{
		if(pidrecv->check == sizeof(PID_DF) * 8)
		{
			switch(pidrecv->command)
			{
			case START_SLAVE:
		
				//PWM_START();
				TIM_START();
				
				return pidrecv->command;
			case STOP_SLAVE:
								
				//PWM_STOP();
				TIM_STOP();
				RET_ZERO();
				
				return pidrecv->command;
			case CHANGEVAL_SLAVE:
				
				return pidrecv->command;
			default:
				return pidrecv->command;
			}
		}
		else
		{
			//鏍￠獙閿欒
		}
	}
	return pidrecv->command;
}

PID_STREAM PID_StreamSend(float value)
{
	PID_STREAM data;
	data.head = 0x445A5850;
	data.actual = value;
	SEND((unsigned char *)&data, sizeof(PID_STREAM));
	return data;
}

PID_DF PID_SlaveStart(float kP, float kI, float kD, float target)
{
	PID_DF data;
	data.head = 0x435A5850;
	data.command = START_SLAVE;
	data.datasize = sizeof(PID_DF);
	data.kP = (float)kP;
	data.kI = (float)kI;
	data.kD = (float)kD;
	data.target = (float)target;
	data.check = sizeof(PID_DF) * 8;
	SEND((unsigned char *)&data, sizeof(PID_DF));
	return data;
}

PID_DF PID_SlaveStop(float value)
{
	PID_DF data;
	data.head = 0x435A5850;
	data.command = STOP_SLAVE;
	data.target = (float)value;
	SEND((unsigned char *)&data, sizeof(PID_DF));
	return data;
}

PID_DF PID_SlaveChangeVal(float kP, float kI, float kD, float target)
{
	PID_DF data;
	data.head = 0x435A5850;
	data.command = CHANGEVAL_SLAVE;
	data.datasize = sizeof(PID_DF);
	data.kP = (float)kP;
	data.kI = (float)kI;
	data.kD = (float)kD;
	data.target = (float)target;
	data.check = sizeof(PID_DF) * 8;
	SEND((unsigned char *)&data, sizeof(PID_DF));
	return data;
}
//4F5A5850鍥為澶达紝0x435A5850鍙戦�佹寚浠ゅご锛�0x445A5850鍙戦�佹祦澶�
