#include "xy_config.h"

void NVIC_Config(void);					//下面的子函数声明

struct rtc_time systmtime;										//RTC时钟


/*
函数功能：设备外设初始化
函数形参：无
函数返回值：无
备注：无
*/
void XY_driver_init(void)
{
	NVIC_Config();							//中断向量配置
	
	bsp_InitTimer();						//系统滴定时器配置（中断）  给Freertos 提供心跳节拍
	
	USART1_Config(9600);					//串口初始化 波特率：9600   printf调试用
	
	Key_EXTI_Config();						//按键中断
	
	EValve_GPIO_Config();					//气阀GPIO初始化， 初始化完成，全部关闭
	
	BME280_Init();							//BME280 三合一传感器初始化			使用myiic.h中的模拟IIC通讯 
	RTC_CheckAndConfig(&systmtime);  		//RTC初始化
}



/*
函数功能：打印系统的运行速率，每个时钟的速率
函数形参：无
函数返回值：无
函数备注：无
*/
void Get_System_clock_freequency(void)
{
	//定义一个RCC_ClocksTypeDef 的结构体
	RCC_ClocksTypeDef get_rcc_clock; 

	//调用RCC_GetClocksFreq获取系统时钟状态
	RCC_GetClocksFreq(&get_rcc_clock);  
	
	XY_DEBUG("系统运行的频率为： %d   系统HCLK的频率为： %d \r\n",get_rcc_clock.SYSCLK_Frequency,get_rcc_clock.HCLK_Frequency);
}
/***************************************************************   子函数 ***********************************************/
/*
函数功能：中断优先级向量配置   优先级分组3
函数形参: 无
函数返回值：无
备注：无
*/
void NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
   
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
    NVIC_Init(&NVIC_InitStructure);
}
