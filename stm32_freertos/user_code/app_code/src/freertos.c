#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"
#include "stdio.h"
#include "xy_config.h"



osThreadId defaultTaskHandle;


void StartDefaultTask(void const * argument);

void StartDefaultTask111(void const * argument);


/*
�������ܣ�������һ������
�����βΣ���
��������ֵ����
��ע��������һ�������������ʼȥ������������

osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 	0,	 	128);
˵����	    ����ָ��		  ��������ڵ�ַ	���ȼ�	  		����Ĳ���	��ջ��С

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




