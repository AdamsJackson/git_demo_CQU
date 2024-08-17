#ifndef __CAR_H__
#define __CAR_H__




#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "tim.h"
#include "gpio.h"
void car_init(void);
void go(void);
void stop(void);
void turn_left(void);
void turn_right(void);
void hands(void);

	
	
#ifdef __cplusplus
}
#endif
#endif 
