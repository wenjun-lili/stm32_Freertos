#include  "xy_config.h"
#include  "xy_key.h"

/*************************************************************************************************/


/**
  * @brief  ���ð����õ����ⲿ�ж�
  * @param  ��
  * @retval ��
  */
void Key_EXTI_Config(void)
{
	EXTI_InitTypeDef  EXTI_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;

  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE);   
	//������ʹ��GPIOAʱ�ӣ�ʱ���ⲿ�жϣ���Ҫʹ��AFIOʱ��  
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPD;      //�������룬�ⲿ����
	GPIO_InitStructure.GPIO_Pin   = GPIO_PinSource8;    //PA8
	GPIO_Init(GPIOD, &GPIO_InitStructure);              //ϵͳ����

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource8);   //�����ⲿ�ж�8
	//GPIOD.8 �ж����Լ��жϳ�ʼ������
	EXTI_InitStructure.EXTI_Line    = EXTI_Line8;
	EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;          //�����½����ж�
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);     //����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���  
  
	NVIC_InitStructure.NVIC_IRQChannel                    = EXTI9_5_IRQn;   //�����ж�Դ    PC7�ⲿ�ж���7  ʹ�õ���EXTI9_5_IRQn
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;
	NVIC_Init(&NVIC_InitStructure);     //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
  
}


/**
  * @brief  ���ð����õ���I/O��
  * @param  ��
  * @retval ��
  */
void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	//���������˿�(GPIOPC)��ʱ��
  
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPD;      //�������룬�ⲿ����
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;         //PC9
	GPIO_Init(GPIOC, &GPIO_InitStructure);              //�Ϸ�����   
  
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPD;      //�������룬�ⲿ����
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8;         //PC8
	GPIO_Init(GPIOC, &GPIO_InitStructure);              //�·�����
  
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPD;      //�������룬�ⲿ����
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_7;         //PC7
	GPIO_Init(GPIOC, &GPIO_InitStructure);              //ȷ������
    

}





/*********************************************END OF FILE**********************/
