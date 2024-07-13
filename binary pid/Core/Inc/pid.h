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
	//速度环PID
	fp32 Kp_speed;
	fp32 Ki_speed;
	fp32 Kd_speed;
	//角度环PID
	fp32 Kp_angle;
	fp32 Ki_angle;
	fp32 Kd_angle;
	//
	fp32 max_out;
	fp32 max_iout;
	
	fp32 set;
	fp32 fdb;
	//在设定值的时候需要进行一个思考，所有的双环pid，都是外环angle环，内环speed环，因为对外环进行设置。
	//我靠那内环怎么返回？外环的输出值作为内环的目标值（set）最终输出的是速度。
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
