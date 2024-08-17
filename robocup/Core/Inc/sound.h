#ifndef __SOUND_H__
#define __SOUND_H__




#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"
#include "gpio.h"
	
void sound_init();
void sound_play(uint16_t A);
#ifdef __cplusplus
}
#endif
#endif 
