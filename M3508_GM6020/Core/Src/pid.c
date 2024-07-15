#include "pid.h"
#include "main.h"
#include <math.h>
//宏定义解释寻取最大值
#define LimitMax(input, max)   \
    {                          \
        if (input > max)       \
        {                      \
            input = max;       \
        }                      \
        else if (input < -max) \
        {                      \
            input = -max;      \
        }                      \
    }
		
void PID_init(pid_type_def *pid, uint8_t mode, /*const fp32 PID_speed[3],const fp32 PID_angle[3],*/ fp32 max_out, fp32 max_iout)  
//注意是对速度环和角度环分别设置了PID，储存在数组里，就是在函数引用的时候较为麻烦，对数组的定义在main.c里
{  
    if (pid == NULL /*|| PID_speed == NULL*/)
    {
        return;
    }	
    
		pid->mode = mode;
//    
//		pid->Kp_speed = PID_speed[0];
//    pid->Ki_speed = PID_speed[1];
//    pid->Kd_speed = PID_speed[2];
		
//		pid->Kp_angle = PID_angle[0];
//    pid->Ki_angle = PID_angle[1];
//    pid->Kd_angle = PID_angle[2];
//		
    pid->max_out = max_out;
    pid->max_iout = max_iout;
    pid->Dbuf[0] = pid->Dbuf[1] = pid->Dbuf[2] = 0.0f;
    pid->error[0] = pid->error[1] = pid->error[2] = pid->Pout = pid->Iout = pid->Dout = pid->out = 0.0f;
}		

fp32 PID_calc(pid_type_def *pid, fp32 ref, fp32 set)
{//现在的问题是对PID的计算？目前没有找到合适的。
    if (pid == NULL)
    {
        return 0.0f;
    }

    pid->error[2] = pid->error[1];
    pid->error[1] = pid->error[0];
    pid->set = set;
    pid->fdb = ref;
    pid->error[0] = set - ref;
    if (pid->mode == PID_POSITION)
    {
        pid->Pout = pid->Kp_speed * pid->error[0];
        pid->Iout += pid->Ki_speed * pid->error[0];
        pid->Dbuf[2] = pid->Dbuf[1];
        pid->Dbuf[1] = pid->Dbuf[0];
        pid->Dbuf[0] = (pid->error[0] - pid->error[1]);
        pid->Dout = pid->Kd_speed * pid->Dbuf[0];
        LimitMax(pid->Iout, pid->max_iout);
        pid->out = pid->Pout + pid->Iout + pid->Dout;
        LimitMax(pid->out, pid->max_out);
    }
    else if (pid->mode == PID_DELTA)
    {
        pid->Pout = pid->Kp_speed * (pid->error[0] - pid->error[1]);
        pid->Iout = pid->Ki_speed * pid->error[0];
        pid->Dbuf[2] = pid->Dbuf[1];
        pid->Dbuf[1] = pid->Dbuf[0];
        pid->Dbuf[0] = (pid->error[0] - 2.0f * pid->error[1] + pid->error[2]);
        pid->Dout = pid->Kd_speed * pid->Dbuf[0];
        pid->out += pid->Pout + pid->Iout + pid->Dout;
        LimitMax(pid->out, pid->max_out);
    }
    return pid->out;
}

void PID_clear(pid_type_def *pid)
{
    if (pid == NULL)
    {
        return;
    }

    pid->error[0] = pid->error[1] = pid->error[2] = 0.0f;
    pid->Dbuf[0] = pid->Dbuf[1] = pid->Dbuf[2] = 0.0f;
    pid->out = pid->Pout = pid->Iout = pid->Dout = 0.0f;
    pid->fdb = pid->set = 0.0f;
}

