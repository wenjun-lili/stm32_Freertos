#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "stdio.h"
#include "xy_config.h"



osThreadId defaultTaskHandle;
osThreadId usart_Task_Handle;

void StartDefaultTask(void const * argument);

void Usart1_Process_Task(void const * argument);


/*
函数功能：创建第一个任务。
函数形参：无
函数返回值：无
备注：创建第一个任务，这个任务开始去创建其他任务。

osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 	0,	 	128);
说明：	    任务指针		  任务函数入口地址	优先级	  			    	堆栈大小

*/
int a = 5;
void MX_FREERTOS_Init(void) 
{
	
	XY_DEBUG("Create the StartDefaultTask  Task !\r\n");
	osThreadDef(defaultTask, StartDefaultTask, osPriorityHigh, 0, 128);
	defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

	if(defaultTaskHandle == NULL)
	{
		XY_DEBUG("Create StartDefaultTask err!\r\n");
	}
	
}

void StartDefaultTask(void const * argument)
{
	
	osThreadDef(usart1_task, Usart1_Process_Task, osPriorityNormal, 0, 128);					//创建串口线程
	
	usart_Task_Handle = osThreadCreate(osThread(usart1_task), NULL);
	
	for(;;)
	{
		
		osDelay(10000);
		
	}
	vTaskDelete(NULL);						//防止如果程序在跳出循环，则在这里进行删除任务，在运行的函数里用NULL表示删除当前的函数。
}




