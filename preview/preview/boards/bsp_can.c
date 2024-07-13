#include "bsp_can.h"
#include "main.h"


extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;

void can_filter_init(void)
{

    CAN_FilterTypeDef can_filter_st;                   //³õÊ¼»¯can1¹ıÂËÆ÷£»
    can_filter_st.FilterActivation = ENABLE;           //enable ÆôÓÃ¹ıÂËÆ÷
    can_filter_st.FilterMode = CAN_FILTERMODE_IDMASK;  //Mode¼´±íÊ¾¹ıÂËÆ÷µÄÄ£Ê½Îª±êÊ¶·ûÆÁ±Î×´Ì¬
	
    can_filter_st.FilterScale = CAN_FILTERSCALE_32BIT; //32Î»
    can_filter_st.FilterIdHigh = 0x0000;               //±êÊ¶·û¸ßÎ»
    can_filter_st.FilterIdLow = 0x0000;                //±êÊ¶·ûµÍÎ»   
    can_filter_st.FilterMaskIdHigh = 0x0000;           //ÆÁ±Î±êÊ¶·ûµÄ¸ßµÍÎ»
    can_filter_st.FilterMaskIdLow = 0x0000;            //
    can_filter_st.FilterBank = 0;                      //¹ıÂËÆ÷×é±àºÅ
    can_filter_st.FilterFIFOAssignment = CAN_RX_FIFO0; //½á¹û´æ´¢£¨RX-½ÓÊÕ£FFIFOO©
    HAL_CAN_ConfigFilter(&hcan1, &can_filter_st);      //¶Ô¹ıÂËÆ÷ÅäÖÃ
    HAL_CAN_Start(&hcan1);                             //ÆôÓÃcan×ÜÏß  ¹Ø¼ü
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);   


    can_filter_st.SlaveStartFilterBank = 14;
    can_filter_st.FilterBank = 14;
    HAL_CAN_ConfigFilter(&hcan2, &can_filter_st);
    HAL_CAN_Start(&hcan2);
    HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);



}
