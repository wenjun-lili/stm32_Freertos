#include "xy_config.h"

//电磁阀的GPIO口定义


/*
函数功能：电磁阀的GPIO初始化
函数形参: 无
函数返回值：无
备注：
		 PF15  E1_CON				CO气室
		 PG0   E2_CON				CO2气室
		 PG1   E3_CON				肺泡气袋
		 PE11  E4_CON				环境本底气袋
		 PE12  E5_CON				肺泡气倒气袋
		 PE13  E6_CON				本底气倒气袋
		 PE14  E7_CON				零气
		 
	初始化完需要关闭所有的气阀，开启每次的测量等，首先第一步都是要关闭气阀，确保气阀一开始是关闭状态的
*/
void EValve_GPIO_Config( void )
{
	/*定义一个GPIO_InitTypeDef类型的结构体*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*开启GPIOB和GPIOF的外设时钟*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG, ENABLE);
	
	
	/*设置引脚模式为通用推挽输出*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //推挽输出
	/*设置引脚速率为50MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 	
	/* 初始化GPIOE引脚 11 12 13 14 */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 ;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	/* ???GPIOF?? 15 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	/* 初始化GPIOG引脚 0 1 */                
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Init(GPIOG, &GPIO_InitStructure);

	/* 关闭所有电磁阀 */
	EValve_All_Close();
}



/*
函数功能：关闭所有的气阀
函数形参：无
函数返回值：无
备注：无
*/
void EValve_All_Close( void )
{
	GPIO_ResetBits( GPIOE, GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);			
	GPIO_ResetBits( GPIOF, GPIO_Pin_15 );
	GPIO_ResetBits( GPIOG, GPIO_Pin_0 | GPIO_Pin_1 );
}


