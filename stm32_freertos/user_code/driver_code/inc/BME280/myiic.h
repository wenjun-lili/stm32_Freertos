#ifndef __MYIIC_H
#define __MYIIC_H
#include "sys.h"
#include "utility.h"



//IO��������
#define BME_SDA_IN()  {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=8<<12;}
#define BME_SDA_OUT() {GPIOB->CRH&=0XFFFF0FFF;GPIOB->CRH|=3<<12;}

//IO��������
#define BME_IIC_SCL    PBout(10) //SCL
#define BME_IIC_SDA    PBout(11) //SDA	 
#define BME_READ_SDA   PBin(11)  //����SDA 

//IIC���в�������
void BME_IIC_Init(void);                //��ʼ��IIC��IO��
void BME_IIC_Start(void);				//����IIC��ʼ�ź�
void BME_IIC_Stop(void);	  			//����IICֹͣ�ź�
void BME_IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 BME_IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 BME_IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void BME_IIC_Ack(void);					//IIC����ACK�ź�
void BME_IIC_NAck(void);				//IIC������ACK�ź�

void BME_IIC_Write_One_Byte(u8 daddr,u8 addr,u8 data);
u8 BME_IIC_Read_One_Byte(u8 daddr,u8 addr);
#endif
















