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
typedef enum                                        //���õ�״̬
{
  /*********************�������µı�־********************************/
	BTN_FLAG_CLR = 0,   			//�������ֵ
	BTN_FLAG_RUN_KEY,				//��������  ��input������
	BTN_FLAG_SET_KEY,				//���ð���
	BTN_FLAG_UP_KEY,				//�ϼ�
	BTN_FLAG_DOWN_KEY,				//�¼�
	BTN_FLAG_LEFT_KEY,				//���
	BTN_FLAG_RIGHT_KEY				//�Ҽ�
	
}
BTNStatusTypedef;
/*************************************************************************************************/
void Key_EXTI_Config(void);
void Key_GPIO_Config(void);



void Clean_Key_status(void);
/*************************************************************************************************/
#endif 
