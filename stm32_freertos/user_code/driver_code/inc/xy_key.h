#ifndef _XY_KEY_H__
#define	_XY_KEY_H__

#include "stm32f10x.h"
#include "xy_config.h"


/*************************************************************************************************/
#define  Key1_Activate        PAin(8)
#define  Key2_Activate        PCin(8)
#define  Key3_Activate        PCin(9)
#define  Key4_Activate        PCin(7)
/*************************************************************************************************/

extern u8 BtnPressedFlag ;
typedef enum                                        //配置的状态
{
  /*********************按键按下的标志********************************/
	BTN_FLAG_CLR = 0,   			//清除按键值
	BTN_FLAG_RUN_KEY,				//测量按键  （input按键）
	BTN_FLAG_SET_KEY,				//设置按键
	BTN_FLAG_UP_KEY,				//上键
	BTN_FLAG_DOWN_KEY,				//下键
	BTN_FLAG_LEFT_KEY,				//左键
	BTN_FLAG_RIGHT_KEY				//右键
	
}
BTNStatusTypedef;
/*************************************************************************************************/
void Key_EXTI_Config(void);
void Key_GPIO_Config(void);



void Clean_Key_status(void);
/*************************************************************************************************/
#endif 
