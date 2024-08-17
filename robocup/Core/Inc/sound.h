#ifndef __SOUND_H__
#define __SOUND_H__




#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "gpio.h"
	
void sound_init(void);
void sound_play(int A);
#ifdef __cplusplus
}
#endif
#endif 
