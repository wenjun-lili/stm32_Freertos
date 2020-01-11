#include  "xy_config.h"
#include  "xy_key.h"

/*************************************************************************************************/


/**
  * @brief  配置按键用到的外部中断
  * @param  无
  * @retval 无
  */
void Key_EXTI_Config(void)
{
	EXTI_InitTypeDef  EXTI_InitStructure;
	NVIC_InitTypeDef  NVIC_InitStructure;
	GPIO_InitTypeDef  GPIO_InitStructure;

  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD | RCC_APB2Periph_AFIO, ENABLE);   
	//按键需使能GPIOA时钟，时钟外部中断，需要使能AFIO时钟  
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPD;      //浮空输入，外部上拉
	GPIO_InitStructure.GPIO_Pin   = GPIO_PinSource8;    //PA8
	GPIO_Init(GPIOD, &GPIO_InitStructure);              //系统按键

	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD, GPIO_PinSource8);   //配置外部中断8
	//GPIOD.8 中断线以及中断初始化配置
	EXTI_InitStructure.EXTI_Line    = EXTI_Line8;
	EXTI_InitStructure.EXTI_Mode    = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;          //上升下降沿中断
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);     //根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器  
  
	NVIC_InitStructure.NVIC_IRQChannel                    = EXTI9_5_IRQn;   //配置中断源    PC7外部中断线7  使用的是EXTI9_5_IRQn
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd                 = ENABLE;
	NVIC_Init(&NVIC_InitStructure);     //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
  
}


/**
  * @brief  配置按键用到的I/O口
  * @param  无
  * @retval 无
  */
void Key_GPIO_Config(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

  
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	//开启按键端口(GPIOPC)的时钟
  
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPD;      //浮空输入，外部上拉
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;         //PC9
	GPIO_Init(GPIOC, &GPIO_InitStructure);              //上翻按键   
  
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPD;      //浮空输入，外部上拉
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8;         //PC8
	GPIO_Init(GPIOC, &GPIO_InitStructure);              //下翻按键
  
	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IPD;      //浮空输入，外部上拉
	GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_7;         //PC7
	GPIO_Init(GPIOC, &GPIO_InitStructure);              //确定按键
    

}





/*********************************************END OF FILE**********************/
