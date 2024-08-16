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
#include "can.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "pid.h"
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
//pid_type_def motor_pid[7];
motor_measure_t *motor_data;
motor_measure_t *motor_6020;

pid_type_def motor_pid[7];   //对多个电机读取pid
pid_type_def gamble_demo;
//M3508的PID设置
const fp32 KP_M3508 = 20.0;
const fp32 KI_M3508 = 0.0;
const fp32 KD_M3508 = 0.0;
const int set_speed = 10;

//GM6020的PID设置
const fp32 KP_GM6020 = 10.0;
const fp32 KI_GM6020 = 0.5;
const fp32 KD_GM6020 = 0.1;

const fp32 set_angle = 0.5;

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
  MX_CAN1_Init();
  /* USER CODE BEGIN 2 */
	
		
		PID_init(&motor_pid[4],PID_POSITION,10000,1000);
			motor_pid[4].Kp_speed = KP_GM6020;
			motor_pid[4].Ki_speed = KI_GM6020;
			motor_pid[4].Kd_speed = KD_GM6020;
			motor_pid[4].Kp_angle = KP_GM6020;
			motor_pid[4].Ki_angle = KI_GM6020;
			motor_pid[4].Kd_angle = KD_GM6020;
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {motor_data = get_chassis_motor_measure_point(4);
    /* USER CODE END WHILE */
		/*对3508进行pid计算*/
		fp32 angle_out = PID_calc(&motor_pid[4], motor_data->ecd, set_angle);
		fp32 speed_out = PID_calc(&motor_pid[4], motor_data->speed_rpm, angle_out);
			//motor_pid[4].out = PID_CascadeCalc(&motor_pid[4], set_angle, motor_data->ecd, motor_data->speed_rpm);
		CAN_cmd_Gamble(speed_out,10,10,10);
		//		for(int i = 0; i<7; i++)
//	{
//		motor_data = get_chassis_motor_measure_point(i);
//		if(i<4){
//			PID_init(&motor_pid[i],PID_POSITION,10000,100);
//			motor_pid[i].Kp_speed = KP_M3508;
//			motor_pid[i].Ki_speed = KI_M3508;
//			motor_pid[i].Kd_speed = KD_M3508;
//			
//			motor_pid[i].out = PID_calc(&motor_pid[i],motor_data -> speed_rpm, set_speed);
//		}
//		else{
//			PID_init(&motor_pid[i],PID_POSITION,25000,100);
//			motor_pid[i].Kp_speed = KP_GM6020;
//			motor_pid[i].Ki_speed = KI_GM6020;
//			motor_pid[i].Kd_speed = KD_GM6020;
//			motor_pid[i].Kp_angle = KP_GM6020;
//			motor_pid[i].Ki_angle = KI_GM6020;
//			motor_pid[i].Kd_angle = KD_GM6020;
//			// motor 1 ecd rpm
//			motor_pid[i].out = PID_CascadeCalc(&motor_pid[i], set_angle, motor_data->ecd, motor_data->speed_rpm);
//			if (i == 4)
//			{
//					motor_6020 = motor_data;
//			}
//		}
//		
//	}
		CAN_cmd_chassis(motor_pid[0].out,0,0,0/*motor_pid[1].out,motor_pid[2].out,motor_pid[3].out */);
		
		HAL_Delay(5);
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
  RCC_OscInitStruct.PLL.PLLN = 168;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

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
