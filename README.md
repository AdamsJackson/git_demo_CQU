在这个文件夹下，我们进行一些对工程文件的放置，以及我的一些思路
需要补充的内容是ADC测量电压以及板间浮点数的通信。首先CSDN了解基础原理后，开始自主手搓。
README.md文件只展示部分重要的操作和bug点，具体的理论需要自行去总结。
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

/************************M3508 & GM6020************************************/
最这两款电机应该算是老朋友了，但是原来用的A板，现在用C板的话，需要进行一些调整，不过大体是一致的，我们仍然需要理一下思路。
从阅读开发板的用户手册开始，我们了解芯片选型：A: f427IIH6；C:f427VIT6
控制这俩货，最难的地方应该是can通信的突破。
如果你的目的只是为了让电机转起来，你只需要配置can的通信口，(尽管你可能会用PID甚至是多环。)
CAN1_TX -> PD1(ac一致)
CAN1_RX -> PD0
A板存在四个可控的电源接口（需要对PH2-PH5这四个接口使能），C板则没有这样的烦恼了。
打开cubemx.注意配置can的时候要保证一下10^6 bit/s(168MHZ-CLK,3-10-3)
开启RX0的中断，从而调用回调函数，这个回调函数的寻找注意是0号FIFO，因为再初始化配置的时候用的是can_filter_st.FilterFIFOAssignment = CAN_RX_FIFO0;
我们可以知道，所有的接收端rx中断是当接收到消息就会触发的。
在回调函数里我们获得对应电机的一些物理量 --> 用于位置环/速度环的处理
see you tomorrow
