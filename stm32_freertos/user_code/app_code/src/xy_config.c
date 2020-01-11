#include "xy_config.h"

void NVIC_Config(void);					//������Ӻ�������


/*
�������ܣ��豸�����ʼ��
�����βΣ���
��������ֵ����
��ע����
*/
void XY_driver_init(void)
{
	NVIC_Config();							//�ж���������
	bsp_InitTimer();						//ϵͳ�ζ�ʱ�����ã��жϣ�  ��Freertos �ṩ��������
	USART1_Config(9600);					//���ڳ�ʼ�� �����ʣ�9600   printf������
	Key_EXTI_Config();
}



/*
�������ܣ���ӡϵͳ���������ʣ�ÿ��ʱ�ӵ�����
�����βΣ���
��������ֵ����
������ע����
*/
void Get_System_clock_freequency(void)
{
	//����һ��RCC_ClocksTypeDef �Ľṹ��
	RCC_ClocksTypeDef get_rcc_clock; 

	//����RCC_GetClocksFreq��ȡϵͳʱ��״̬
	RCC_GetClocksFreq(&get_rcc_clock);  
	
	XY_DEBUG("ϵͳ���е�Ƶ��Ϊ�� %d   ϵͳHCLK��Ƶ��Ϊ�� %d \r\n",get_rcc_clock.SYSCLK_Frequency,get_rcc_clock.HCLK_Frequency);
}
/***************************************************************   �Ӻ��� ***********************************************/
/*
�������ܣ��ж����ȼ���������   ���ȼ�����3
�����β�: ��
��������ֵ����
��ע����
*/
void NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
   
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
    NVIC_Init(&NVIC_InitStructure);
}
