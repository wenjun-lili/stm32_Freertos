#include "xy_config.h"

void Usart1_Process_Task(void const * argument)
{
	portTickType time_cnt ;
	printf("usart1_task create successful ! \r\n");
	for(;;)
	{
		time_cnt  = xTaskGetTickCount();
		printf("time_cnt  = %d \r\n",time_cnt);
		osDelay(2000);
	}
 
}

