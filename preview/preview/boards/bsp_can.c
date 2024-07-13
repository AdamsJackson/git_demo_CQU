#include "bsp_can.h"
#include "main.h"


extern CAN_HandleTypeDef hcan1;
extern CAN_HandleTypeDef hcan2;

void can_filter_init(void)
{

    CAN_FilterTypeDef can_filter_st;                   //��ʼ��can1��������
    can_filter_st.FilterActivation = ENABLE;           //enable ���ù�����
    can_filter_st.FilterMode = CAN_FILTERMODE_IDMASK;  //Mode����ʾ��������ģʽΪ��ʶ������״̬
	
    can_filter_st.FilterScale = CAN_FILTERSCALE_32BIT; //32λ
    can_filter_st.FilterIdHigh = 0x0000;               //��ʶ����λ
    can_filter_st.FilterIdLow = 0x0000;                //��ʶ����λ   
    can_filter_st.FilterMaskIdHigh = 0x0000;           //���α�ʶ���ĸߵ�λ
    can_filter_st.FilterMaskIdLow = 0x0000;            //
    can_filter_st.FilterBank = 0;                      //����������
    can_filter_st.FilterFIFOAssignment = CAN_RX_FIFO0; //����洢��RX-���գFFIFOO�
    HAL_CAN_ConfigFilter(&hcan1, &can_filter_st);      //�Թ���������
    HAL_CAN_Start(&hcan1);                             //����can����  �ؼ�
    HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING);   


    can_filter_st.SlaveStartFilterBank = 14;
    can_filter_st.FilterBank = 14;
    HAL_CAN_ConfigFilter(&hcan2, &can_filter_st);
    HAL_CAN_Start(&hcan2);
    HAL_CAN_ActivateNotification(&hcan2, CAN_IT_RX_FIFO0_MSG_PENDING);



}
