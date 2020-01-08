#include "systick.h"
#include "cmsis_os.h"
#include "stm32f10x.h"


typedef unsigned int  	uint32_t;
typedef int  			int32_t;
typedef unsigned char  	uint8_t;
/* 这2个全局变量适用于bsp_DelayMS()   */
static volatile uint32_t s_uiDelayCount = 0;
static volatile uint8_t  s_ucTimeOutFlag = 0;

/*
在此定义若干个软件定时器全局变量
注意，必须增加__IO 即 volatile，因为这个变量在中断和主程序中同时被访问，有可能造成编译器错误优化。
*/
#define TMR_COUNT	4		/* 软件定时器的个数，第1个保留给bsp_DelayMS()使用 */

SOFT_TMR g_Tmr[TMR_COUNT];

void bsp_InitTimer(void)
{
    SysTick_Config(SystemCoreClock / 1000); // 计数初值为72000
}


void SysTick_Handler(void)
{
	osSystickHandler();
}





/*********************************************END OF FILE**********************/
