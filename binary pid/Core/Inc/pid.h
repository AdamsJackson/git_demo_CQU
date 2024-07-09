#ifndef __PID_H__
#define __PID_H__

#include "main.h"
enum PID_MODE
{
	PID_POSITION = 0,
	PID_DELTA
	
};

typedef struct
{
	uint8_t mode;
	//�ٶȻ�PID
	fp32 Kp_speed;
	fp32 Ki_speed;
	fp32 Kd_speed;
	//�ǶȻ�PID
	fp32 Kp_angle;
	fp32 Ki_angle;
	fp32 Kd_angle;
	//
	fp32 max_out;
	fp32 max_iout;
	
	fp32 set;
	fp32 fdb;
	//���趨ֵ��ʱ����Ҫ����һ��˼�������е�˫��pid�������⻷angle�����ڻ�speed������Ϊ���⻷�������á�
	//�ҿ����ڻ���ô���أ��⻷�����ֵ��Ϊ�ڻ���Ŀ��ֵ��set��������������ٶȡ�
	fp32 out;
	fp32 Pout;
	fp32 Iout;
	fp32 Dout;
	fp32 Dbuf[3];
	fp32 error[3];
} pid_type_def;

extern void PID_init(pid_type_def *pid, uint8_t mode,const fp32 PID_speed[3],const fp32 PID_angle[3], fp32 max_out, fp32 max_iout);

extern fp32 PID_calc(pid_type_def *pid, fp32 ref, fp32 set);

extern void PID_clear(pid_type_def *pid);
#endif
