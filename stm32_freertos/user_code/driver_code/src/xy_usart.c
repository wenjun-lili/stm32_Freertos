/**
  ******************************************************************************
  * @file    xy_usart.c
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   �����õ�printf���ڣ��ض���printf������
  ******************************************************************************
  * @attention
 
  ******************************************************************************
  */ 

#include "xy_usart.h"
#include <string.h>


/**
  * @brief  USART1_NVIC_Config(void)
	* @datail ����USART1�����ж�
	* @param  none
	* @return none
  */
static void USART1_NVIC_Config(void)
{
	NVIC_InitTypeDef NVIC_InitStructure; 

	/* Enable the USARTy Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}



 /**
  * @brief  USART GPIO ����,������������
  * @param  bpr     ���õĴ��ڲ�����
  * @retval none
  * @��ע��  USART1     PA9->TX   PA10->RX     �����жϹ���
  */
void USART1_Config(int bpr)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 | RCC_APB2Periph_GPIOA, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);    

	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	USART_InitStructure.USART_BaudRate =bpr;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);
	
	#if 0
	USART_Cmd(USART1, ENABLE);					//���ж�ģʽ
    #elif 1
	USART_Cmd(USART1, ENABLE);					//�ж�ģʽ
	USART1_NVIC_Config();
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	
	USART_ClearFlag(USART1, USART_FLAG_TC);
    #endif
}

#if 1								//	printf��ӡģʽ

int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);
	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);		
	return (ch);
}

int fgetc(FILE *f)
{
	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);
	return (int)USART_ReceiveData(USART1);
}
#endif

 



#if 1

/**
  * @brief  USART1_IRQHandler(void)
	* @datail USART1 �жϴ������
	* @param  none
	* @return none
  */ 
void USART1_IRQHandler(void)
{

	
	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
	{ 	
		 USART_ClearITPendingBit(USART1, USART_IT_RXNE);//  ����жϱ�־λ
		 
	} 

}

#endif

/********************************END OF FILE************************/

