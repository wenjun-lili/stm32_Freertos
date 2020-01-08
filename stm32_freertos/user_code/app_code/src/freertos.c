#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "stdio.h"
#include "xy_config.h"



osThreadId defaultTaskHandle;


void StartDefaultTask(void const * argument);

void StartDefaultTask111(void const * argument);


/*
函数功能：创建第一个任务。
函数形参：无
函数返回值：无
备注：创建第一个任务，这个任务开始去创建其他任务。

osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 	0,	 	128);
说明：	    任务指针		  任务函数入口地址	优先级	  		传入的参数	堆栈大小

*/
void MX_FREERTOS_Init(void) 
{
	XY_DEBUG("System create the first Task !\r\n");
	osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
	defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);
}

void StartDefaultTask(void const * argument)
{
	
	osThreadDef(defaultTask, StartDefaultTask111, osPriorityNormal, 0, 128);
	defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  for(;;)
  {
	 printf("333\r\n");
    osDelay(10000);
  }
 
}

void StartDefaultTask111(void const * argument)
{
	

  for(;;)
  {
	 printf("2222\r\n");
    osDelay(1000);
  }
 
}




