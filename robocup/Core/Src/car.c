#include "car.h"

void car_init(void){
	
	HAL_GPIO_WritePin(ina1_GPIO_Port,ina1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(inb1_GPIO_Port,inb1_Pin,GPIO_PIN_RESET);  

	HAL_GPIO_WritePin(ina2_GPIO_Port,ina2_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(inb2_GPIO_Port,inb2_Pin,GPIO_PIN_RESET);
}


void go(void){

	HAL_GPIO_WritePin(ina1_GPIO_Port,ina1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(inb1_GPIO_Port,inb1_Pin,GPIO_PIN_SET);  
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_2,300);  //ina1 ina2 -> channel 2  left

	HAL_GPIO_WritePin(ina2_GPIO_Port,ina2_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(inb2_GPIO_Port,inb2_Pin,GPIO_PIN_RESET);
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1,300);  //inb1 inb2 -> channel 1  right
}

void turn_left(void){

	/*ina1 high inb1 low  back */
	HAL_GPIO_WritePin(ina1_GPIO_Port,ina1_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(inb1_GPIO_Port,inb1_Pin,GPIO_PIN_RESET);  
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_2,200);  //ina1 ina2 -> channel 2  left
	/*ina2 high inb2 low  strgight*/
	HAL_GPIO_WritePin(ina2_GPIO_Port,ina2_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(inb2_GPIO_Port,inb2_Pin,GPIO_PIN_RESET);
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1,200);  //inb1 inb2 -> channel 1  right
}

void stop(void){
	
	HAL_GPIO_WritePin(ina1_GPIO_Port,ina1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(inb1_GPIO_Port,inb1_Pin,GPIO_PIN_RESET);  

	HAL_GPIO_WritePin(ina2_GPIO_Port,ina2_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(inb2_GPIO_Port,inb2_Pin,GPIO_PIN_RESET);
}

void turn_right(void){

	/*ina1 low inb1 high  go */
	HAL_GPIO_WritePin(ina1_GPIO_Port,ina1_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(inb1_GPIO_Port,inb1_Pin,GPIO_PIN_SET);  
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_2,200);  //ina1 ina2 -> channel 2  left
	/*ina2 low inb2 high  back*/
	HAL_GPIO_WritePin(ina2_GPIO_Port,ina2_Pin,GPIO_PIN_RESET);
	HAL_GPIO_WritePin(inb2_GPIO_Port,inb2_Pin,GPIO_PIN_SET);
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_1,200);  //inb1 inb2 -> channel 1  right
	
}

void hands(void){
	
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,50);
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,250);
	HAL_Delay(1000);
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,150);
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2,100);
	
}
