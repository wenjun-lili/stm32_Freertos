#ifndef __XY_CONFIG_H__
#define __XY_CONFIG_H__

// ����ļ��Ƕ���һЩȫ�ֱ����� ���������õ��ļ���
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
#include "xy_EleValve.h"									//��ŷ��ļ�
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



/**********************************���Ͷ���**************************/
typedef unsigned int  	uint32_t;
typedef int  			int32_t;
typedef unsigned char  	uint8_t;
/*******************************   END *******************************/


/******************************   ȫ�ֱ��� **************************/
extern struct rtc_time systmtime;										//RTCʱ��
/********************************************************************/




/********************************   END *****************************/






/**********************************   ȫ�ֱ������� ***************************************/
						//����1����������Ϣ��


/***************************************************************************************/
void XY_driver_init(void);								//ϵͳ�����ʼ��

void Get_System_clock_freequency(void);					//��ӡϵͳ���е�ʱ������





#endif
