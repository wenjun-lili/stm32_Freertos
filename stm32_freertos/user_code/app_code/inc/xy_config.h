#ifndef __XY_CONFIG_H__
#define __XY_CONFIG_H__

// 这个文件是定义一些全局变量。 或者总配置的文件。
/*************************  system file  ***************************/
#include <stdio.h>
#include "stm32f10x.h"
#include "cmsis_os.h"
#include "FreeRTOS.h"
/********************************   END       **********************/



/*************************  user driver file ***********************/
#include "systick.h"
#include "xy_key.h"
#include "xy_usart.h"
#include "xy_EleValve.h"									//电磁阀文件
#include "bsp_rtc.h"
#include "myiic.h"
/********************************   END       **********************/



/*************************  user app flie  **************************/
#include "xy_usart1_task.h"
#include "BME280.h"
/********************************   END       **********************/




/********************************   DEBUG MODE **********************/
#define OPEN   			  1
#define CLOSE			  0
#define XY_DEBUG_MODE     OPEN

#if XY_DEBUG_MODE
	#define XY_DEBUG(format,...)  printf("[FILE: "__FILE__", LINE: %d]: "format, __LINE__, ##__VA_ARGS__)
#else
	#define XY_DEBUG(format,...)
#endif
/********************************   END       **********************/



/**********************************类型定义**************************/
typedef unsigned int  	uint32_t;
typedef int  			int32_t;
typedef unsigned char  	uint8_t;
/*******************************   END *******************************/


/******************************   全局变量 **************************/
extern struct rtc_time systmtime;										//RTC时钟
/********************************************************************/




/********************************   END *****************************/






/**********************************   全局变量定义 ***************************************/
						//串口1传输数据信息。


/***************************************************************************************/
void XY_driver_init(void);								//系统外设初始化

void Get_System_clock_freequency(void);					//打印系统运行的时钟速率





#endif
