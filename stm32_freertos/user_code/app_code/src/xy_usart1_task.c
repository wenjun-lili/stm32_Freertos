#include "xy_config.h"

void Usart1_Process_Task(void const * argument)
{
	
	//printf("usart1_task create successful!  \r\n");
	while(1)
	{
		if(Usart1.recv_ok_flag == 1 )
		{
			printf("len =%d     buf = %s \r\n",Usart1.recv_lenth,Usart1.Recv_data);
			Usart1.recv_ok_flag = 0;
		}
		osDelay(10);
	}
	vTaskDelete(NULL);										//防止程序跳出循环，若跳出循环，则删除自身任务。
}

