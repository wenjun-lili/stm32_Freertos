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
�������ܣ�������һ������
�����βΣ���
��������ֵ����
��ע��������һ�������������ʼȥ������������

osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 	0,	 	128);
˵����	    ����ָ��		  ��������ڵ�ַ	���ȼ�	  			    	��ջ��С

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
	
	osThreadDef(usart1_task, Usart1_Process_Task, osPriorityNormal, 0, 128);					//���������߳�
	
	usart_Task_Handle = osThreadCreate(osThread(usart1_task), NULL);
	
	for(;;)
	{
		
		osDelay(10000);
		
	}
	vTaskDelete(NULL);						//��ֹ�������������ѭ���������������ɾ�����������еĺ�������NULL��ʾɾ����ǰ�ĺ�����
}




