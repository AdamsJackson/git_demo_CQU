/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Servo_R_Pin GPIO_PIN_0
#define Servo_R_GPIO_Port GPIOA
#define Servo_L_Pin GPIO_PIN_1
#define Servo_L_GPIO_Port GPIOA
#define IO_0_Pin GPIO_PIN_0
#define IO_0_GPIO_Port GPIOG
#define IO_1_Pin GPIO_PIN_1
#define IO_1_GPIO_Port GPIOG
#define IO_2_Pin GPIO_PIN_2
#define IO_2_GPIO_Port GPIOG
#define IO_3_Pin GPIO_PIN_3
#define IO_3_GPIO_Port GPIOG
#define IO_4_Pin GPIO_PIN_4
#define IO_4_GPIO_Port GPIOG
#define IO_5_Pin GPIO_PIN_5
#define IO_5_GPIO_Port GPIOG
#define IO_6_Pin GPIO_PIN_6
#define IO_6_GPIO_Port GPIOG
#define IO_7_Pin GPIO_PIN_7
#define IO_7_GPIO_Port GPIOG
#define PE_Switch4_Pin GPIO_PIN_11
#define PE_Switch4_GPIO_Port GPIOC
#define PE_Switch3_Pin GPIO_PIN_12
#define PE_Switch3_GPIO_Port GPIOC
#define inb1_Pin GPIO_PIN_0
#define inb1_GPIO_Port GPIOD
#define D2_Pin GPIO_PIN_1
#define D2_GPIO_Port GPIOD
#define ina2_Pin GPIO_PIN_3
#define ina2_GPIO_Port GPIOD
#define inb2_Pin GPIO_PIN_4
#define inb2_GPIO_Port GPIOD
#define D4_Pin GPIO_PIN_5
#define D4_GPIO_Port GPIOD
#define D6_Pin GPIO_PIN_7
#define D6_GPIO_Port GPIOD
#define D8_Pin GPIO_PIN_9
#define D8_GPIO_Port GPIOG
#define D1_Pin GPIO_PIN_11
#define D1_GPIO_Port GPIOG
#define D3_Pin GPIO_PIN_13
#define D3_GPIO_Port GPIOG
#define D5_Pin GPIO_PIN_15
#define D5_GPIO_Port GPIOG
#define D7_Pin GPIO_PIN_4
#define D7_GPIO_Port GPIOB
#define ina1_Pin GPIO_PIN_5
#define ina1_GPIO_Port GPIOB
#define motor_pwm2_Pin GPIO_PIN_6
#define motor_pwm2_GPIO_Port GPIOB
#define motor_pwm1_Pin GPIO_PIN_7
#define motor_pwm1_GPIO_Port GPIOB
#define PE_Switch1_Pin GPIO_PIN_8
#define PE_Switch1_GPIO_Port GPIOB
#define PE_Switch2_Pin GPIO_PIN_9
#define PE_Switch2_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
extern int total;  
extern int D1; 
extern int D2;
extern int D3;
extern int D4;
extern int D5;
extern int D6;
extern int D7;
extern int D8;
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
