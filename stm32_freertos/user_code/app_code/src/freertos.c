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
	
	//XY_DEBUG("Create the StartDefaultTask  Task !\r\n");
	
	osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);				//创建第一个任务
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

	while(1)
	{
		if(BtnPressedFlag != BTN_FLAG_CLR)
		{	
			XY_DEBUG("BtnPressedFlag = %d \r\n",BtnPressedFlag);
			switch(BtnPressedFlag)
			{
				case BTN_FLAG_RUN_KEY:											// INPUT按键    测量模式
					{
						Clean_Key_status();										//清除按键状态
						//Measure_Process();									
						break;
					}
				case BTN_FLAG_SET_KEY:											//RUN/SET按键    去设置参数
					{
						Clean_Key_status();		
						//Set_Parameter_Process();								//设置参数按键（工程师模式和用户模式两种）
						break;
					}
				case BTN_FLAG_UP_KEY:											//UP按键   C02标定模式
					{
						Clean_Key_status();
						//CO2_Calibration_Process();								
						break;
					}
				case BTN_FLAG_DOWN_KEY:											//DOWN按键	质控模式
					{
						Clean_Key_status();	
						//Quality_Control_Process();								
						break;
					}
				case BTN_FLAG_LEFT_KEY:											//LEFT按键	配气模式
					{
						Clean_Key_status();				
						//Make_Gas_Process();										
						break;
					}
				case BTN_FLAG_RIGHT_KEY:										//RIGHT按键 	CO标定模式
					{
						Clean_Key_status();		
						//CO_Calibration_Process();							
						break;
					}
				default:
					{		
						break;
					}
			}
		}
		//Time_Display( RTC_GetCounter(),&systmtime); //读取时间
		osDelay(10);
		
	}
	vTaskDelete(NULL);						//防止如果程序在跳出循环，则在这里进行删除任务，在运行的函数里用NULL表示删除当前的函数。
}




