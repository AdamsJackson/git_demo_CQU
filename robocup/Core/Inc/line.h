#ifndef __LINE_H__
#define __LINE_H__




#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "gpio.h"
#include "tim.h"
#include "car.h"

int turn_check(void); //检查各个传感器数值 while里
void turn(int turn);  //实现差速转弯
	
#ifdef __cplusplus
}
#endif
#endif 