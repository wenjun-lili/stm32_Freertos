#include "myiic.h"

//#include "delay.h"

//��ʼ��IIC
void BME_IIC_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    RCC_APB2PeriphClockCmd(	RCC_APB2Periph_GPIOB, ENABLE );

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP ;   //�������
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_SetBits(GPIOB,GPIO_Pin_10|GPIO_Pin_11); 	//PB10,PB11 �����
}
//����IIC��ʼ�ź�
void BME_IIC_Start(void)
{
    BME_SDA_OUT();     //sda�����
    BME_IIC_SDA=1;
    BME_IIC_SCL=1;
    Delay1us(4);
    BME_IIC_SDA=0;//START:when CLK is high,DATA change form high to low
    Delay1us(4);
    BME_IIC_SCL=0;//ǯסI2C���ߣ�׼�����ͻ��������
}
//����IICֹͣ�ź�
void BME_IIC_Stop(void)
{
    BME_SDA_OUT();//sda�����
    BME_IIC_SCL=0;
    BME_IIC_SDA=0;//STOP:when CLK is high DATA change form low to high
    Delay1us(4);
    BME_IIC_SCL=1;
    BME_IIC_SDA=1;//����I2C���߽����ź�
    Delay1us(4);
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 BME_IIC_Wait_Ack(void)
{
    u8 ucErrTime=0;
    BME_SDA_IN();      //SDA����Ϊ����
    BME_IIC_SDA=1;
    Delay1us(1);
    BME_IIC_SCL=1;
    Delay1us(1);
    while(BME_READ_SDA)
    {
        ucErrTime++;
        if(ucErrTime>250)
        {
            BME_IIC_Stop();
            return 1;
        }
    }
    BME_IIC_SCL=0;//ʱ�����0
    return 0;
}
//����ACKӦ��
void BME_IIC_Ack(void)
{
    BME_IIC_SCL=0;
    BME_SDA_OUT();
    BME_IIC_SDA=0;
    Delay1us(2);
    BME_IIC_SCL=1;
    Delay1us(2);
    BME_IIC_SCL=0;
}
//������ACKӦ��
void BME_IIC_NAck(void)
{
    BME_IIC_SCL=0;
    BME_SDA_OUT();
    BME_IIC_SDA=1;
    Delay1us(2);
    BME_IIC_SCL=1;
    Delay1us(2);
    BME_IIC_SCL=0;
}
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��
void BME_IIC_Send_Byte(u8 txd)
{
    u8 t;
    BME_SDA_OUT();
    BME_IIC_SCL=0;//����ʱ�ӿ�ʼ���ݴ���
    for(t=0; t<8; t++)
    {
        //IIC_SDA=(txd&0x80)>>7;
        if((txd&0x80)>>7)
            BME_IIC_SDA=1;
        else
            BME_IIC_SDA=0;
        txd<<=1;
        Delay1us(2);  //��TEA5767��������ʱ���Ǳ����
        BME_IIC_SCL=1;
        Delay1us(2);
        BME_IIC_SCL=0;
        Delay1us(2);
    }
}
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK
u8 BME_IIC_Read_Byte(unsigned char ack)
{
    unsigned char i,receive=0;
    BME_SDA_IN();//SDA����Ϊ����
    for(i=0; i<8; i++ )
    {
        BME_IIC_SCL=0;
        Delay1us(2);
        BME_IIC_SCL=1;
        receive<<=1;
        if(BME_READ_SDA)receive++;
        Delay1us(1);
    }
    if (!ack)
        BME_IIC_NAck();//����nACK
    else
        BME_IIC_Ack(); //����ACK
    return receive;
}



























