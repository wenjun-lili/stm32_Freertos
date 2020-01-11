#ifndef _XY_USART1_H__
#define	_XY_USART1_H__

#include "stm32f10x.h"
#include <stdio.h>

#define USART_RECV_LEN   200
#define USART_SEND_LEN   50


typedef struct {
	char Recv_data[USART_RECV_LEN];					//USART���յĻ�����
	char send_data[USART_SEND_LEN];					//USART�������ݵĻ�����
	u8 	 recv_lenth;								//����һ֡���ݵĳ���
	u8 	 recv_ok_flag;								//������ɱ�־
	int  time_cnt;									//��������֮�󣬾�����յ��������ݵ�ʱ��
}USART_Message;


extern USART_Message Usart1;


void USART1_Config(int bpr);
void USART1_Timeout_UserCallback(void);






#endif /* __USART1_H */


 
 
