#include "systick.h"
#include "cmsis_os.h"
#include "stm32f10x.h"


typedef unsigned int  	uint32_t;
typedef int  			int32_t;
typedef unsigned char  	uint8_t;
/* ��2��ȫ�ֱ���������bsp_DelayMS()   */
static volatile uint32_t s_uiDelayCount = 0;
static volatile uint8_t  s_ucTimeOutFlag = 0;

/*
�ڴ˶������ɸ������ʱ��ȫ�ֱ���
ע�⣬��������__IO �� volatile����Ϊ����������жϺ���������ͬʱ�����ʣ��п�����ɱ����������Ż���
*/
#define TMR_COUNT	4		/* �����ʱ���ĸ�������1��������bsp_DelayMS()ʹ�� */

SOFT_TMR g_Tmr[TMR_COUNT];

void bsp_InitTimer(void)
{
    SysTick_Config(SystemCoreClock / 1000); // ������ֵΪ72000
}


void SysTick_Handler(void)
{
	osSystickHandler();
}





/*********************************************END OF FILE**********************/
