#include "line.h"

int turn_int()
{
    D8=-HAL_GPIO_ReadPin(GPIOG,D8_Pin);
    D7=-HAL_GPIO_ReadPin(GPIOB,D7_Pin);
	D6=-HAL_GPIO_ReadPin(GPIOD,D6_Pin);
	D5=-HAL_GPIO_ReadPin(GPIOG,D5_Pin);
	D4=HAL_GPIO_ReadPin(GPIOD,D4_Pin);
	D3=HAL_GPIO_ReadPin(GPIOG,D3_Pin);
	D2=HAL_GPIO_ReadPin(GPIOD,D2_Pin);
	D1=HAL_GPIO_ReadPin(GPIOG,D1_Pin);
	total=D1+D2+D3+D4+D5+D6+D7+D8;
    return total;
}
void turn(int turn)
{
    if(total>0)
	{
		HAL_GPIO_WritePin(ina1_GPIO_Port,ina1_Pin,GPIO_PIN_RESET);
        HAL_GPIO_WritePin(inb1_GPIO_Port,inb1_Pin,GPIO_PIN_SET);  
        __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_2,200+50*total);  //ina1 ina2 -> channel 2  left

        HAL_GPIO_WritePin(ina2_GPIO_Port,ina2_Pin,GPIO_PIN_SET);
        HAL_GPIO_WritePin(inb2_GPIO_Port,inb2_Pin,GPIO_PIN_RESET);
        __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1,200);  //inb1 inb2 -> channel 1  right
	    HAL_Delay(10);
	}
	else
	{
	    HAL_GPIO_WritePin(ina1_GPIO_Port,ina1_Pin,GPIO_PIN_RESET);
	    HAL_GPIO_WritePin(inb1_GPIO_Port,inb1_Pin,GPIO_PIN_SET);  
	    __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_2,200);  //ina1 ina2 -> channel 2  left

	    HAL_GPIO_WritePin(ina2_GPIO_Port,ina2_Pin,GPIO_PIN_SET);
	    HAL_GPIO_WritePin(inb2_GPIO_Port,inb2_Pin,GPIO_PIN_RESET);
	    __HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1,200+50*(-total));  //inb1 inb2 -> channel 1  right
	    HAL_Delay(10);
	}
}
