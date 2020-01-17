#include "bsp_rtc.h"




/* ���жϱ�־���������ж�ʱ��1����ʱ�䱻ˢ��֮����0 */
__IO uint32_t TimeDisplay = 0;

void RTCAlarmInit(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;	
	
	//-*************����RTC�����ж�****************
	NVIC_InitStructure.NVIC_IRQChannel = RTCAlarm_IRQn;  //����NVIC������
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line17;					//��ʼ���ⲿ�ж�
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //��17�����ش���
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	
	//�޸�ʱ�䣬������ʹ�ܵ�Դ�ӿ�ʱ�Ӻͱ��ݽӿ�ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
	
	//Allow access to BKP Domain �����޸�rtc�ͺ󱸼Ĵ���
	PWR_BackupAccessCmd(ENABLE);
	
	RTC_WaitForLastTask();
	RTC_ITConfig(RTC_IT_ALR, ENABLE);
	RTC_WaitForLastTask();

	/* RTC���ӼĴ�����λֵΪ0xFFFFFFFF������������Բ����������ӼĴ�����������ȥ���� */
	
	//-************�رն�Ӧ��ʱ��*************
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, DISABLE);
	PWR_BackupAccessCmd(DISABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,DISABLE);
}


/*
 * ��������RTC_CheckAndConfig
 * ����  ����鲢����RTC
 * ����  �����ڶ�ȡRTCʱ��Ľṹ��ָ��
 * ���  ����
 * ����  ���ⲿ����
 */
void RTC_CheckAndConfig(struct rtc_time *tm)
{
	NVIC_InitTypeDef NVIC_InitStructure;
  /* Configure one bit for preemption priority */
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  //����RTC���жϵ����ж����ȼ�Ϊ1�������ȼ�Ϊ0
   /* Enable the RTC Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  //1,0��Ϊ3,0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
  
  	/*������ʱ��鱸�ݼĴ���BKP_DR1��������ݲ���0xA5A5,
	  ������������ʱ�䲢ѯ���û�����ʱ��*/
	if (BKP_ReadBackupRegister(BKP_DR1) != 0xA5A5)
	{
		/* RTC Configuration */
		RTC_Configuration();

		/* Adjust time by users typed on the hyperterminal */
		Time_init(tm);

		BKP_WriteBackupRegister(BKP_DR1, 0xA5A5);
	}
	else
	{
	  /*��������������ʱ��*/
		/*********************************************************
		//����Ƿ��������
		if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)
		{
		    printf("\r\n\r\n Power On Reset occurred....");
		}
		//����Ƿ�Reset��λ
		else if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET)
		{
			printf("\r\n\r\n External Reset occurred....");
		}
	
		printf("\r\n No need to configure RTC....");
		************************************************************/
		/*�ȴ��Ĵ���ͬ��*/
		RTC_WaitForSynchro();
		/*����RTC���ж�*/
		RTC_ITConfig(RTC_IT_SEC, ENABLE);
		/*�ȴ��ϴ�RTC�Ĵ���д�������*/
		RTC_WaitForLastTask();
	}	
	  /* Clear reset flags */
	  RCC_ClearFlag();
    
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, DISABLE); //�رն�Ӧ��ʱ��
	  PWR_BackupAccessCmd(DISABLE);
	
    Time_Display( RTC_GetCounter(),tm); //��ȡʱ��
}




/*
 * ��������RTC_Configuration
 * ����  ������RTC
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
 */
void RTC_Configuration(void)
{
	/* Enable PWR and BKP clocks */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
	
	/* Allow access to BKP Domain */
	PWR_BackupAccessCmd(ENABLE);
	
	/* Reset Backup Domain */
	BKP_DeInit();
	
	/* Enable LSE */
	RCC_LSEConfig(RCC_LSE_ON);
	
	/* Wait till LSE is ready */
	while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
	{}
	
	/* Select LSE as RTC Clock Source */
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
	
	/* Enable RTC Clock */
	RCC_RTCCLKCmd(ENABLE);
	
	/* Wait for RTC registers synchronization 
	 * ��ΪRTCʱ���ǵ��ٵģ��ڻ�ʱ���Ǹ��ٵģ�����Ҫͬ��
	 */
	RTC_WaitForSynchro();
	
	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();
	
	/* Enable the RTC Second */
	RTC_ITConfig(RTC_IT_SEC, ENABLE);
	
	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();
	
	/* Set RTC prescaler: set RTC period to 1sec */
	RTC_SetPrescaler(32767); /* RTC period = RTCCLK/RTC_PR = (32.768 KHz)/(32767+1) = 1HZ */
	
	/* Wait until last write operation on RTC registers has finished */
	RTC_WaitForLastTask();
}


/**************************************************************************************
 * ��������Time_Get
 * ����  ���ڻ�ȡ��ǰʱ��ֵ
 * ����  ����
 * ���  ����
 * ����  ���ⲿ����
 **************************************************************************************/ 
//void Time_Get(struct rtc_time *tm)
//{
//	//static u8 min_chang_s=0;  //�����
//	
//	    /* ÿ��1s */
//	    if (1==TimeDisplay)
//	    {
//				/* Display current time */
//	      Time_Display( RTC_GetCounter(),tm); 		  
//	      TimeDisplay = 0;
//	      
//	    }
//}


/*
 * ��������Time_init
 * ����  ��ʱ�����
 * ����  �����ڶ�ȡRTCʱ��Ľṹ��ָ��
 * ���  ����
 * ����  ���ⲿ����
 */
void Time_init(struct rtc_time *tm)
{
	  /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
	  //��ʼ��ʱ��ṹ��
	  tm->tm_year = 2017;  //��
	  tm->tm_mon  = 6;     //��
	  tm->tm_mday = 26;     //��
	  tm->tm_hour = 12;    //ʱ
	  tm->tm_min  = 0;     //��
	  tm->tm_sec  = 0;     //��
	  
	  /* Get wday */
	  //GregorianDay(tm); //���ﲻ�õ������������

	  /* �޸ĵ�ǰRTC�����Ĵ������� */
	  RTC_SetCounter(mktimev(tm));
	  /* Wait until last write operation on RTC registers has finished */
	  RTC_WaitForLastTask();
}

/*
 * ��������Time_Display
 * ����  ����ʾ��ǰʱ��ֵ
 * ����  ��-TimeVar RTC����ֵ����λΪ s
 * ���  ����
 * ����  ���ڲ�����
 */	
void Time_Display(uint32_t TimeVar,struct rtc_time *tm)
{
	   uint32_t BJ_TimeVar;	

	   /*  �ѱ�׼ʱ��ת��Ϊ����ʱ��*/
	   BJ_TimeVar =TimeVar + 8*60*60;
	   to_tm(BJ_TimeVar, tm);/*�Ѷ�ʱ����ֵת��Ϊ����ʱ��*/	
	   /***********************debug����������ʾʱ��**********************/
	   printf("��ǰʱ��Ϊ��%d�� %d�� %d�� %0.2d:%0.2d:%0.2d\r\n",systmtime.tm_year,systmtime.tm_mon,
				       systmtime.tm_mday,systmtime.tm_hour,systmtime.tm_min,systmtime.tm_sec);
	  /***/
}






/************************END OF FILE***************************************/
