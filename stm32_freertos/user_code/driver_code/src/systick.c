#include "systick.h"
#include "xy_config.h"




/*
�������ܣ���ʼ��ϵͳ�δ�ʱ���� 
�����βΣ���
��������ֵ����
��ע��   1msһ�Ρ�  �����жϽ���SysTick_Handler������ ��FreeRtos�ṩ��������
*/
void bsp_InitTimer(void)
{
    SysTick_Config(SystemCoreClock / 1000); // ������ֵΪ72000    1ms һ��
}



/*
�������ܣ�ϵͳ�δ�ʱ���жϺ������
�����βΣ���
��������ֵ: ��
������ע����
*/
void SysTick_Handler(void)
{
	osSystickHandler();			//FreeRtos ϵͳ����ʹ��
}





/*********************************************END OF FILE**********************/
