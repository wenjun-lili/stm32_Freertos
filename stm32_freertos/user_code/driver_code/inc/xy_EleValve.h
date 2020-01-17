
#ifndef __XY_ELEVALVE_H__
#define __XY_ELEVALVE_H__

#include "stm32f10x.h"

#define Close_VO1() GPIO_ResetBits( GPIOF, GPIO_Pin_15 )//PF15
#define Close_VO2() GPIO_ResetBits( GPIOG, GPIO_Pin_0 ) //PG0
#define Close_VO3() GPIO_ResetBits( GPIOG, GPIO_Pin_1 ) //PG1
#define Close_VO4() GPIO_ResetBits( GPIOE, GPIO_Pin_11 )//PE11
#define Close_VO5() GPIO_ResetBits( GPIOE, GPIO_Pin_12 )//pE12
#define Close_VO6() GPIO_ResetBits( GPIOE, GPIO_Pin_13 )//PE13
#define Close_VO7() GPIO_ResetBits( GPIOE, GPIO_Pin_14 )//PE14
 

#define OPEN_VO1() GPIO_SetBits( GPIOF, GPIO_Pin_15 )
#define OPEN_VO2() GPIO_SetBits( GPIOG, GPIO_Pin_0 )
#define OPEN_VO3() GPIO_SetBits( GPIOG, GPIO_Pin_1 )
#define OPEN_VO4() GPIO_SetBits( GPIOE, GPIO_Pin_11 )
#define OPEN_VO5() GPIO_SetBits( GPIOE, GPIO_Pin_12 )
#define OPEN_VO6() GPIO_SetBits( GPIOE, GPIO_Pin_13 )
#define OPEN_VO7() GPIO_SetBits( GPIOE, GPIO_Pin_14 )
 

void EValve_GPIO_Config(void);
void EValve_All_Close( void );




#endif	/* __EVALVE_H */
