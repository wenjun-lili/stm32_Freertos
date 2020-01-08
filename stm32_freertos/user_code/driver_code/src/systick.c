#include "systick.h"
#include "xy_config.h"




/*
函数功能：初始化系统滴答定时器。 
函数形参：无
函数返回值：无
备注：   1ms一次。  产生中断进入SysTick_Handler（）， 给FreeRtos提供心跳节拍
*/
void bsp_InitTimer(void)
{
    SysTick_Config(SystemCoreClock / 1000); // 计数初值为72000    1ms 一次
}



/*
函数功能：系统滴答定时器中断函数入口
函数形参：无
函数返回值: 无
函数备注：无
*/
void SysTick_Handler(void)
{
	osSystickHandler();			//FreeRtos 系统调度使用
}





/*********************************************END OF FILE**********************/
