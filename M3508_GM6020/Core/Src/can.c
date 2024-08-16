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
motor_measure_t motor_chassis[7]; //Ω·ππÃÂ¿‡–Õœ¬µƒ ˝◊È

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
  //can_filter_init
	CAN_FilterTypeDef can_filter_st;                   //≥ı ºªØcan1π˝¬À∆˜£ª
    can_filter_st.FilterActivation = ENABLE;           //enable ∆Ù”√π˝¬À∆˜
    can_filter_st.FilterMode = CAN_FILTERMODE_IDMASK;  //Modeº¥±Ì æπ˝¬À∆˜µƒƒ£ ΩŒ™±Í ∂∑˚∆¡±Œ◊¥Ã¨
	
    can_filter_st.FilterScale = CAN_FILTERSCALE_32BIT; //32Œª
    can_filter_st.FilterIdHigh = 0x0000;               //±Í ∂∑˚∏ﬂŒª
    can_filter_st.FilterIdLow = 0x0000;                //±Í ∂∑˚µÕŒª   
    can_filter_st.FilterMaskIdHigh = 0x0000;           //∆¡±Œ±Í ∂∑˚µƒ∏ﬂµÕŒª
    can_filter_st.FilterMaskIdLow = 0x0000;            //
    can_filter_st.FilterBank = 0;                      //π˝¬À∆˜◊È±‡∫≈
    can_filter_st.FilterFIFOAssignment = CAN_RX_FIFO0; //Ω·π˚¥Ê¥¢£®RX-Ω” ’£FFIFOO©
    HAL_CAN_ConfigFilter(&hcan1, &can_filter_st);      //∂‘π˝¬À∆˜≈‰÷√
    HAL_CAN_Start(&hcan1);                             //∆Ù”√can◊‹œﬂ  πÿº¸
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

    __HAL_RCC_GPIOD_CLK_ENABLE();
    /**CAN1 GPIO Configuration
    PD0     ------> CAN1_RX
    PD1     ------> CAN1_TX
    */
    GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
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
    PD0     ------> CAN1_RX
    PD1     ------> CAN1_TX
    */
    HAL_GPIO_DeInit(GPIOD, GPIO_PIN_0|GPIO_PIN_1);

    /* CAN1 interrupt Deinit */
    HAL_NVIC_DisableIRQ(CAN1_RX0_IRQn);
  /* USER CODE BEGIN CAN1_MspDeInit 1 */

  /* USER CODE END CAN1_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
//µ◊≈Ã3508øÿ÷∆
void CAN_cmd_chassis(int16_t motor1, int16_t motor2, int16_t motor3, int16_t motor4)
{
	chassis_tx_message.StdId = 0X200;
	chassis_tx_message.IDE = CAN_ID_STD;
	chassis_tx_message.RTR = CAN_RTR_DATA;
	chassis_tx_message.DLC = 0x08;  //“ª∏ˆ±Í◊º
	//ø™ º∆¥Ω”∏ﬂµÕ∞ÀŒª
		chassis_can_send_data[0] = (motor1 >> 8)&0xff;
		chassis_can_send_data[1] = (motor1)&0xff;
		chassis_can_send_data[2] = (motor2 >> 8)&0xff;
		chassis_can_send_data[3] = (motor2)&0xff;
		chassis_can_send_data[4] = (motor3 >> 8)&0xff;
		chassis_can_send_data[5] = (motor3)&0xff;
		chassis_can_send_data[6] = (motor4 >> 8)&0xff;
		chassis_can_send_data[7] = (motor4)&0xff;
	
	HAL_CAN_AddTxMessage(&hcan1,&chassis_tx_message,chassis_can_send_data,(uint32_t*)CAN_TX_MAILBOX0);
 }
//‘∆Ã®6020øÿ÷∆
void CAN_cmd_Gamble(int16_t v1, int16_t v2, int16_t v3, int16_t v4)
{
	gamble_tx_message.StdId = 0x1ff;
	gamble_tx_message.IDE = CAN_ID_STD;
	gamble_tx_message.RTR = CAN_RTR_DATA;
	gamble_tx_message.DLC = 8;
	
	gamble_can_send_data[0] = (v1 >> 8)&0xff;
	gamble_can_send_data[1] = 		(v1)&0xff;
	gamble_can_send_data[2] = (v2 >> 8)&0xff;
  gamble_can_send_data[3] =    (v2)&0xff; 
  gamble_can_send_data[4] = (v3 >> 8)&0xff;
  gamble_can_send_data[5] =    (v3)&0xff;
	gamble_can_send_data[6] = (v4 >> 8)&0xff;
	gamble_can_send_data[7] = (v4)&0xff;
	
	HAL_CAN_AddTxMessage(&hcan1, &gamble_tx_message, gamble_can_send_data,(uint32_t*)CAN_TX_MAILBOX0);
}
//Ω” ’∂À÷–∂œªÿµ˜
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
motor_measure_t *get_chassis_motor_measure_point(uint8_t i)
{
    return &motor_chassis[(i & 0x03)];			
}

/* USER CODE END 1 */
