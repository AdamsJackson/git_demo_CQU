在这个文件夹下，我们进行一些对工程文件的放置，以及我的一些思路
需要补充的内容是ADC测量电压以及板间浮点数的通信。首先CSDN了解基础原理后，开始自主手搓。

/*************************ADC************************************/
在adc测量的过程中，用到的几个重要的hal库函数：
HAL_ADCEx_Calibration_Start(&hadc1); //这里的句柄取决于你所开启的通道
接下来需要在while循环里读取电压状态：
HAL_ADC_Start(&hadc1);
HAL_ADC_PollForConversion(&hadc1,50); 
需要判断adc状态
if(HAL_IS_BIT_SET(HAL_ADC_GetState(&hadc1),HAL_ADC_STATE_REG_EOC))
{
    ADC_Value = HAL_ADC_GetState(&hadc1);
    Voltage = ADC_value*3.3f / ADC_Parameter;
}
最后为了方便，我们可以自主添加串口传输数据，然后结合万用表进行数据验证。

/*************************BOARD_COMMUNICATION(FLOAT)************************************/
这个章节就是对串口数据传输的进阶（中断-DMA）发现dma实现不定长的本质是缓冲区的充分利用
这里给出两个包装好的hal库来向直接传输简单浮点数和字符串，不用每次都得强制转换类型后再发送：
void UART_SendString(UART_HandleTypeDef *huart, const char* str){
	HAL_UART_Transmit(huart, (uint8_t*)str, strlen(str), 50);
}

void UART_SendFloat(UART_HandleTypeDef *huart, float value, int precision) {
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "%.*f", precision, value);
    HAL_UART_Transmit(huart, (uint8_t*)buffer, strlen(buffer), 50);
}
attention:（都是血泪教训）
strlen()需要#include <string.h>
snprintf()需要#include <stdlib.h>
在终端过程中，需要自己去it文件中找到，weak，来进行实例化中断回调函数[void HAL_UARTEx_RxEventCallback()]，警惕“half”
HAL_UART_Transmit();最基础
HAL_UARTEx_ReceiveToIdle_DMA();dma接受


