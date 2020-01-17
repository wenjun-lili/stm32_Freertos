#include "xy_config.h"

//��ŷ���GPIO�ڶ���


/*
�������ܣ���ŷ���GPIO��ʼ��
�����β�: ��
��������ֵ����
��ע��
		 PF15  E1_CON				CO����
		 PG0   E2_CON				CO2����
		 PG1   E3_CON				��������
		 PE11  E4_CON				������������
		 PE12  E5_CON				������������
		 PE13  E6_CON				������������
		 PE14  E7_CON				����
		 
	��ʼ������Ҫ�ر����е�����������ÿ�εĲ����ȣ����ȵ�һ������Ҫ�ر�������ȷ������һ��ʼ�ǹر�״̬��
*/
void EValve_GPIO_Config( void )
{
	/*����һ��GPIO_InitTypeDef���͵Ľṹ��*/
	GPIO_InitTypeDef GPIO_InitStructure;

	/*����GPIOB��GPIOF������ʱ��*/
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOE | RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG, ENABLE);
	
	
	/*��������ģʽΪͨ���������*/
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;   //�������
	/*������������Ϊ50MHz */   
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 	
	/* ��ʼ��GPIOE���� 11 12 13 14 */
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 ;
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	/* ???GPIOF?? 15 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	/* ��ʼ��GPIOG���� 0 1 */                
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
	GPIO_Init(GPIOG, &GPIO_InitStructure);

	/* �ر����е�ŷ� */
	EValve_All_Close();
}



/*
�������ܣ��ر����е�����
�����βΣ���
��������ֵ����
��ע����
*/
void EValve_All_Close( void )
{
	GPIO_ResetBits( GPIOE, GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14);			
	GPIO_ResetBits( GPIOF, GPIO_Pin_15 );
	GPIO_ResetBits( GPIOG, GPIO_Pin_0 | GPIO_Pin_1 );
}


