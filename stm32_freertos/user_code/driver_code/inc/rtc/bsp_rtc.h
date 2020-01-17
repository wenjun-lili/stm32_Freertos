

#ifndef __RTC_H
#define	__RTC_H


#include "stm32f10x.h"
#include "bsp_date.h"
#include "xy_config.h"



extern __IO uint32_t TimeDisplay;





void RTCAlarmInit(void);

void RTC_CheckAndConfig(struct rtc_time *tm);
void RTC_Configuration(void);
void Time_init(struct rtc_time *tm);
void Time_Display(uint32_t TimeVar,struct rtc_time *tm);
void Time_Get(struct rtc_time *tm);

int rtc_current_year_eclipse_seconds( struct rtc_time datetime );
u8 CompareDateTime(struct rtc_time T1,struct rtc_time T2,int seconds);

void LG_RTCTime_Init(void);
void Upload_Time(void);  //上传服务器要求更新时间
void UpTime_Init(void);//同步更新时间
#endif /* __XXX_H */
