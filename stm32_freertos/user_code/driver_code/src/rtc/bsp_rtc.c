#include "bsp_rtc.h"




/* 秒中断标志，进入秒中断时置1，当时间被刷新之后清0 */
__IO uint32_t TimeDisplay = 0;

void RTCAlarmInit(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	EXTI_InitTypeDef EXTI_InitStructure;	
	
	//-*************配置RTC闹钟中断****************
	NVIC_InitStructure.NVIC_IRQChannel = RTCAlarm_IRQn;  //配置NVIC的秒钟
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line17;					//初始化外部中断
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; //线17上升沿触发
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	
	//修改时间，必须先使能电源接口时钟和备份接口时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, ENABLE);
	
	//Allow access to BKP Domain 允许修改rtc和后备寄存器
	PWR_BackupAccessCmd(ENABLE);
	
	RTC_WaitForLastTask();
	RTC_ITConfig(RTC_IT_ALR, ENABLE);
	RTC_WaitForLastTask();

	/* RTC闹钟寄存器复位值为0xFFFFFFFF，所以这里可以不用配置闹钟寄存器，到后面去配置 */
	
	//-************关闭对应的时钟*************
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, DISABLE);
	PWR_BackupAccessCmd(DISABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,DISABLE);
}


/*
 * 函数名：RTC_CheckAndConfig
 * 描述  ：检查并配置RTC
 * 输入  ：用于读取RTC时间的结构体指针
 * 输出  ：无
 * 调用  ：外部调用
 */
void RTC_CheckAndConfig(struct rtc_time *tm)
{
	NVIC_InitTypeDef NVIC_InitStructure;
  /* Configure one bit for preemption priority */
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
  //配置RTC秒中断的主中断优先级为1，次优先级为0
   /* Enable the RTC Interrupt */
	NVIC_InitStructure.NVIC_IRQChannel = RTC_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;  //1,0改为3,0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
  
  	/*在启动时检查备份寄存器BKP_DR1，如果内容不是0xA5A5,
	  则需重新配置时间并询问用户调整时间*/
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
	  /*启动无需设置新时钟*/
		/*********************************************************
		//检查是否掉电重启
		if (RCC_GetFlagStatus(RCC_FLAG_PORRST) != RESET)
		{
		    printf("\r\n\r\n Power On Reset occurred....");
		}
		//检查是否Reset复位
		else if (RCC_GetFlagStatus(RCC_FLAG_PINRST) != RESET)
		{
			printf("\r\n\r\n External Reset occurred....");
		}
	
		printf("\r\n No need to configure RTC....");
		************************************************************/
		/*等待寄存器同步*/
		RTC_WaitForSynchro();
		/*允许RTC秒中断*/
		RTC_ITConfig(RTC_IT_SEC, ENABLE);
		/*等待上次RTC寄存器写操作完成*/
		RTC_WaitForLastTask();
	}	
	  /* Clear reset flags */
	  RCC_ClearFlag();
    
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR | RCC_APB1Periph_BKP, DISABLE); //关闭对应的时钟
	  PWR_BackupAccessCmd(DISABLE);
	
    Time_Display( RTC_GetCounter(),tm); //读取时间
}




/*
 * 函数名：RTC_Configuration
 * 描述  ：配置RTC
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
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
	 * 因为RTC时钟是低速的，内环时钟是高速的，所以要同步
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
 * 函数名：Time_Get
 * 描述  ：在获取当前时间值
 * 输入  ：无
 * 输出  ：无
 * 调用  ：外部调用
 **************************************************************************************/ 
//void Time_Get(struct rtc_time *tm)
//{
//	//static u8 min_chang_s=0;  //秒计数
//	
//	    /* 每过1s */
//	    if (1==TimeDisplay)
//	    {
//				/* Display current time */
//	      Time_Display( RTC_GetCounter(),tm); 		  
//	      TimeDisplay = 0;
//	      
//	    }
//}


/*
 * 函数名：Time_init
 * 描述  ：时间调节
 * 输入  ：用于读取RTC时间的结构体指针
 * 输出  ：无
 * 调用  ：外部调用
 */
void Time_init(struct rtc_time *tm)
{
	  /* Wait until last write operation on RTC registers has finished */
    RTC_WaitForLastTask();
	  //初始化时间结构体
	  tm->tm_year = 2017;  //年
	  tm->tm_mon  = 6;     //月
	  tm->tm_mday = 26;     //日
	  tm->tm_hour = 12;    //时
	  tm->tm_min  = 0;     //分
	  tm->tm_sec  = 0;     //秒
	  
	  /* Get wday */
	  //GregorianDay(tm); //这里不用到星期这个函数

	  /* 修改当前RTC计数寄存器内容 */
	  RTC_SetCounter(mktimev(tm));
	  /* Wait until last write operation on RTC registers has finished */
	  RTC_WaitForLastTask();
}

/*
 * 函数名：Time_Display
 * 描述  ：显示当前时间值
 * 输入  ：-TimeVar RTC计数值，单位为 s
 * 输出  ：无
 * 调用  ：内部调用
 */	
void Time_Display(uint32_t TimeVar,struct rtc_time *tm)
{
	   uint32_t BJ_TimeVar;	

	   /*  把标准时间转换为北京时间*/
	   BJ_TimeVar =TimeVar + 8*60*60;
	   to_tm(BJ_TimeVar, tm);/*把定时器的值转换为北京时间*/	
	   /***********************debug，测试用显示时间**********************/
	   printf("当前时间为：%d年 %d月 %d日 %0.2d:%0.2d:%0.2d\r\n",systmtime.tm_year,systmtime.tm_mon,
				       systmtime.tm_mday,systmtime.tm_hour,systmtime.tm_min,systmtime.tm_sec);
	  /***/
}






/************************END OF FILE***************************************/
