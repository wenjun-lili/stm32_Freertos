#include "stm32f10x.h"
#include "xy_config.h"

/*
作者: 李文君
邮箱：632970690@qq.com
备注：简易的移植FreeRtos系统，会慢慢的去补充功能。
*/


#define USE_STM32_SYSTEM_CUBE    1

int main(void)
{	
	XY_driver_init();						//设备外设初始化
	Get_System_clock_freequency();			//获取系统时钟运行速度
	
	
#if USE_STM32_SYSTEM_CUBE					//是否使用STM32CUBE工具生成的代码，是的话就是下面的创建函数，它里面有会跳转到最原始FreeRTOS的xTaskCreate创建函数和vTaskStartScheduler（）
	MX_FREERTOS_Init();					    //开始穿件第一个任务
	osKernelStart();						//系统调度。 正常情况下永远运行不到这一步
#else
	
#endif
	
	while(1);

}





