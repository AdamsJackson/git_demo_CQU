/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    can.c
  * @brief   This file provides code for the configuration
  *          of the CAN instances.
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
#include "can.h"

/* USER CODE BEGIN 0 */
//宏定义获取电机id 处理电机数据 -- 角度，速度等
#define get_motor_measure(ptr, data)                                    \
    {                                                                   \
        (ptr)->last_ecd = (ptr)->ecd;                                   \
        (ptr)->ecd = (uint16_t)((data)[0] << 8 | (data)[1]);            \
        (ptr)->speed_rpm = (uint16_t)((data)[2] << 8 | (data)[3]);      \
        (ptr)->given_current = (uint16_t)((data)[4] << 8 | (data)[5]);  \
        (ptr)->temperate = (data)[6];                                   \
    }
		
static CAN_TxHeaderTypeDef  chassis_tx_message;
static CAN_TxHeaderTypeDef  gamble_tx_message;
static uint8_t              chassis_can_send_data[8];
static uint8_t              gamble_can_send_data[8];
motor_measure_t motor_chassis[7]; //结构体类型下的数组

/* USER CODE END 0 */

CAN_HandleTypeDef hcan1;

/* CAN1 init function */
void MX_CAN1_Init(void)
{

  /* USER CODE BEGIN CAN1_Init 0 */

  /* USER CODE END CAN1_Init 0 */

  /* USER CODE BEGIN CAN1_Init 1 */

  /* USER CODE END CAN1_Init 1 */
  hcan1.Instance = CAN1;
  hcan1.Init.Prescaler = 3;
  hcan1.Init.Mode = CAN_MODE_NORMAL;
  hcan1.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan1.Init.TimeSeg1 = CAN_BS1_10TQ;
  hcan1.Init.TimeSeg2 = CAN_BS2_3TQ;
  hcan1.Init.TimeTriggeredMode = DISABLE;
  hcan1.Init.AutoBusOff = DISABLE;
  hcan1.Init.AutoWakeUp = DISABLE;
  hcan1.Init.AutoRetransmission = DISABLE;
  hcan1.Init.ReceiveFifoLocked = DISABLE;
  hcan1.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN1_Init 2 */
	//can_filter_init
	CAN_FilterTypeDef can_filter_st;                   //初始化can1过滤器；
    can_filter_st.FilterActivation = ENABLE;           //enable 启用过滤器
    can_filter_st.FilterMode = CAN_FILTERMODE_IDMASK;  //Mode即表示过滤器的模式为标识符屏蔽状态
	
    can_filter_st.FilterScale = CAN_FILTERSCALE_32BIT; //32位
    can_filter_st.FilterIdHigh = 0x0000;               //标识符高位
    can_filter_st.FilterIdLow = 0x0000;                //标识符低位   
    can_filter_st.FilterMaskIdHigh = 0x0000;           //屏蔽标识符的高低位
    can_filter_st.FilterMaskIdLow = 0x0000;            //
    can_filter_st.FilterBank = 0;                      //过滤器组编号
    can_filter_st.FilterFIFOAssignment = CAN_RX_FIFO0; //结果存储（RX-接收FIFOO�
    HAL_CAN_ConfigFilter(&hcan1, &can_filter_st);      //对过滤器配置
    HAL_CAN_Start(&hcan1);                             //启用can总线  关键
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);   


    can_filter_st.SlaveStartFilterBank = 14;
    can_filter_st.FilterBank = 14;
  /* USER CODE END CAN1_Init 2 */

}

void HAL_CAN_MspInit(CAN_HandleTypeDef* canHandle)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};
  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspInit 0 */

  /* USER CODE END CAN1_MspInit 0 */
    /* CAN1 clock enable */
    __HAL_RCC_CAN1_CLK_ENABLE();

    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**CAN1 GPIO Configuration
    PB9     ------> CAN1_TX
    PD0     ------> CAN1_RX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_9;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF9_CAN1;
    HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

    /* CAN1 interrupt Init */
    HAL_NVIC_SetPriority(CAN1_RX0_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspInit 1 */

  /* USER CODE END CAN1_MspInit 1 */
  }
}

void HAL_CAN_MspDeInit(CAN_HandleTypeDef* canHandle)
{

  if(canHandle->Instance==CAN1)
  {
  /* USER CODE BEGIN CAN1_MspDeInit 0 */

  /* USER CODE END CAN1_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_CAN1_CLK_DISABLE();

    /**CAN1 GPIO Configuration
    PB9     ------> CAN1_TX
    PD0     ------> CAN1_RX
    */
    HAL_GPIO_DeInit(GPIOB, GPIO_PIN_9);

    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_0);

    /* CAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
/**
  * @brief          发送电机控制电流(0x201,0x202,0x203,0x204)
  * @param[in]      motor1: (0x201) 3508电机控制电流, 范围 [-16384,16384]
  * @param[in]      motor2: (0x202) 3508电机控制电流, 范围 [-16384,16384]
  * @param[in]      motor3: (0x203) 3508电机控制电流, 范围 [-16384,16384]
  * @param[in]      motor4: (0x204) 3508电机控制电流, 范围 [-16384,16384]
  * @retval         none
  */
void CAN_cmd_chassis(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4)
{
	uint32_t send_mail_box;
	chassis_tx_message.StdId = 0X200;
	chassis_tx_message.IDE = CAN_ID_STD;
	chassis_tx_message.RTR = CAN_RTR_DATA;
	chassis_tx_message.DLC = 0x08;  //一个标准
	//开始拼接高低八位
		chassis_can_send_data[0] = (motor1 >> 8)&0xff;
		chassis_can_send_data[1] = (motor1)&0xff;
		chassis_can_send_data[2] = (motor2 >> 8)&0xff;
		chassis_can_send_data[3] = (motor2)&0xff;
		chassis_can_send_data[4] = (motor3 >> 8)&0xff;
		chassis_can_send_data[5] = (motor3)&0xff;
		chassis_can_send_data[6] = (motor4 >> 8)&0xff;
		chassis_can_send_data[7] = (motor4)&0xff;
	
	HAL_CAN_AddTxMessage(&hcan1,&chassis_tx_message,chassis_can_send_data,&send_mail_box);
 }

void set_gamble_voltage(int16_t v1, int16_t v2, int16_t v3)
{
  gamble_tx_message.StdId = 0x2ff;//(id_range == 0)?(0x1ff):(0x2ff); //0x2ff  -- 3个电机控制(非零)
  gamble_tx_message.IDE   = CAN_ID_STD;
  gamble_tx_message.RTR   = CAN_RTR_DATA;
  gamble_tx_message.DLC   = 8;
	
  gamble_can_send_data[0] = (v1 >> 8)&0xff;
  gamble_can_send_data[1] =    (v1)&0xff;  //获取低八位
  gamble_can_send_data[2] = (v2 >> 8)&0xff;
  gamble_can_send_data[3] =    (v2)&0xff;
  gamble_can_send_data[4] = (v3 >> 8)&0xff;
  gamble_can_send_data[5] =    (v3)&0xff;
  HAL_CAN_AddTxMessage(&hcan1, &gamble_tx_message, gamble_can_send_data,(uint32_t*)CAN_TX_MAILBOX0); 
}

//接下来我们需要写接收流程利用RX0的中断
//hal_can.c的1907行的弱定义函数在这里进行定义
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
  CAN_RxHeaderTypeDef rx_header;
	uint8_t rx_data[8];
	
	HAL_CAN_GetRxMessage(hcan,CAN_RX_FIFO0,&rx_header,rx_data);
	
	switch(rx_header.StdId)
	{
		case CAN_3508_M1_ID:
		case CAN_3508_M2_ID:
		case CAN_3508_M3_ID:
		case CAN_3508_M4_ID:
		case CAN_YAW_MOTOR_ID:
		case CAN_PIT_MOTOR_ID:
		case CAN_TRIGGER_MOTOR_ID:
		{
			static uint8_t i = 0;
			//get motor id 
			i = rx_header.StdId - CAN_3508_M1_ID;
			get_motor_measure(&motor_chassis[i],rx_data);	
		}
	}
}
//因为要读取电机速度，所以需要进行读取数据嘛
const motor_measure_t *get_chassis_motor_measure_point(uint8_t i)
{
    return &motor_chassis[(i & 0x03)];			
}

/* USER CODE END 1 */
