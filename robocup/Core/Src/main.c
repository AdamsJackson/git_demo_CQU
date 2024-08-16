/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "tim.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
void pwm_start(void);
void stop(void);
void turn_left(void);
void turn_right(void);
void hands(void);
void go(void);
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM2_Init();
  MX_TIM4_Init();
  /* USER CODE BEGIN 2 */
	pwm_start();
	hands();
	go();
	HAL_Delay(2000);
	turn_left();
	HAL_Delay(3000);
	stop();
	HAL_Delay(50);
	turn_right();
	HAL_Delay(5000);
	
	stop();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 72;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void pwm_start(void){
	
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);    //servo_r
	HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_2);		//servo_l
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_1);    //motor_pwm2
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_2);    //motor_pwm1
		
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
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
