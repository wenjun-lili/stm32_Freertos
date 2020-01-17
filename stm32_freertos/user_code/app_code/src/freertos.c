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
	
	//XY_DEBUG("Create the StartDefaultTask  Task !\r\n");
	
	osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);				//������һ������
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

	while(1)
	{
		if(BtnPressedFlag != BTN_FLAG_CLR)
		{	
			XY_DEBUG("BtnPressedFlag = %d \r\n",BtnPressedFlag);
			switch(BtnPressedFlag)
			{
				case BTN_FLAG_RUN_KEY:											// INPUT����    ����ģʽ
					{
						Clean_Key_status();										//�������״̬
						//Measure_Process();									
						break;
					}
				case BTN_FLAG_SET_KEY:											//RUN/SET����    ȥ���ò���
					{
						Clean_Key_status();		
						//Set_Parameter_Process();								//���ò�������������ʦģʽ���û�ģʽ���֣�
						break;
					}
				case BTN_FLAG_UP_KEY:											//UP����   C02�궨ģʽ
					{
						Clean_Key_status();
						//CO2_Calibration_Process();								
						break;
					}
				case BTN_FLAG_DOWN_KEY:											//DOWN����	�ʿ�ģʽ
					{
						Clean_Key_status();	
						//Quality_Control_Process();								
						break;
					}
				case BTN_FLAG_LEFT_KEY:											//LEFT����	����ģʽ
					{
						Clean_Key_status();				
						//Make_Gas_Process();										
						break;
					}
				case BTN_FLAG_RIGHT_KEY:										//RIGHT���� 	CO�궨ģʽ
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
		//Time_Display( RTC_GetCounter(),&systmtime); //��ȡʱ��
		osDelay(10);
		
	}
	vTaskDelete(NULL);						//��ֹ�������������ѭ���������������ɾ�����������еĺ�������NULL��ʾɾ����ǰ�ĺ�����
}




