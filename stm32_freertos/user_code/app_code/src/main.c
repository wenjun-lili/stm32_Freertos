#include "stm32f10x.h"
#include "xy_config.h"

/*
����: ���ľ�
���䣺632970690@qq.com
��ע�����׵���ֲFreeRtosϵͳ����������ȥ���书�ܡ�
*/


#define USE_STM32_SYSTEM_CUBE    1

int main(void)
{	
	XY_driver_init();						//�豸�����ʼ��
	Get_System_clock_freequency();			//��ȡϵͳʱ�������ٶ�
	
	
#if USE_STM32_SYSTEM_CUBE					//�Ƿ�ʹ��STM32CUBE�������ɵĴ��룬�ǵĻ���������Ĵ����������������л���ת����ԭʼFreeRTOS��xTaskCreate����������vTaskStartScheduler����
	MX_FREERTOS_Init();					    //��ʼ������һ������
	osKernelStart();						//ϵͳ���ȡ� �����������Զ���в�����һ��
#else
	
#endif
	
	while(1);

}





