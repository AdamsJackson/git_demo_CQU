#include "sound.h"

void sound_init(){
    HAL_GPIO_WritePin(IO_0_GPIO_Port,IO_0_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(IO_1_GPIO_Port,IO_1_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(IO_2_GPIO_Port,IO_2_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(IO_3_GPIO_Port,IO_3_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(IO_4_GPIO_Port,IO_4_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(IO_5_GPIO_Port,IO_5_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(IO_6_GPIO_Port,IO_6_Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(IO_7_GPIO_Port,IO_7_Pin,GPIO_PIN_SET);
}

