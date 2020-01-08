#include "stm32f10x.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
#include "xy_usart.h"
#include "systick.h"




void NVIC_Config(void)
{
    NVIC_InitTypeDef NVIC_InitStructure;
   
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);
    NVIC_Init(&NVIC_InitStructure);
}

int main(void)
{
	int a = 5;

	NVIC_Config();

	bsp_InitTimer();
	USART1_Config();
	
	MX_FREERTOS_Init();

  
	osKernelStart();
	
	while(1);

}





