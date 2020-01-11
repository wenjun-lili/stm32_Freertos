#ifndef _XY_USART1_H__
#define	_XY_USART1_H__

#include "stm32f10x.h"
#include <stdio.h>

#define USART_RECV_LEN   200
#define USART_SEND_LEN   50


typedef struct {
	char Recv_data[USART_RECV_LEN];					//USART接收的缓冲区
	char send_data[USART_SEND_LEN];					//USART发送数据的缓冲区
	u8 	 recv_lenth;								//接收一帧数据的长度
	u8 	 recv_ok_flag;								//接收完成标志
	int  time_cnt;									//发送数据之后，距离接收到返回数据的时间
}USART_Message;


extern USART_Message Usart1;


void USART1_Config(int bpr);
void USART1_Timeout_UserCallback(void);






#endif /* __USART1_H */


 
 
