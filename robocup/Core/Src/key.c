#include "key.h"

void collision(void)
{
    //E18-D80NK 前方有障碍物 红灯亮 为reset；反之则为set
    pin_value = HAL_GPIO_ReadPin(PE_Switch1_GPIO_Port,PE_Switch1_Pin);
    if(pin_value == 0){
        hands();
    }
    else{
        sound_play(7);
    }
}