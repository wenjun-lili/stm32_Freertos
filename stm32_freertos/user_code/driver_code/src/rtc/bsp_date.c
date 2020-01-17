#include "bsp_date.h"

#define FEBRUARY		2
#define	STARTOFTIME		1970
#define SECDAY			86400L           /*  一天有多少s */
#define SECYR			(SECDAY * 365)
#define	leapyear(year)		((year) % 4 == 0)
#define	days_in_year(a) 	(leapyear(a) ? 366 : 365)
#define	days_in_month(a) 	(month_days[(a) - 1])

u8 month_days[12] = {	31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

/*
 *ADD by fire：本函数在工程中的输入参数为北京时间，
 所以在转换成时间戳时最后要从北京时间转换为标准时间的时间戳
 */
u32 mktimev(struct rtc_time *tm)
{
	if (0 >= (int) (tm->tm_mon -= 2)) {	/* 1..12 -> 11,12,1..10 */
		tm->tm_mon += 12;		/* Puts Feb last since it has leap day */
		tm->tm_year -= 1;
	}

	return (((
		(u32) (tm->tm_year/4 - tm->tm_year/100 + tm->tm_year/400 + 367*tm->tm_mon/12 + tm->tm_mday) +
			tm->tm_year*365 - 719499
	    )*24 + tm->tm_hour /* now have hours */
	  )*60 + tm->tm_min /* now have minutes */
	)*60 + tm->tm_sec-8*60*60; /* finally seconds */
	/*Add by fire: -8*60*60 把输入的北京时间转换为标准时间，
	再写入计时器中，确保计时器的数据为标准的UNIX时间戳*/ 
	 
}



void to_tm(u32 tim, struct rtc_time * tm)
{
	register u32    i;
	register long   hms, day;

	day = tim / SECDAY;			/* 有多少天 */
	hms = tim % SECDAY;			/* 今天的时间，单位s */

	/* Hours, minutes, seconds are easy */
	tm->tm_hour = hms / 3600;
	tm->tm_min = (hms % 3600) / 60;
	tm->tm_sec = (hms % 3600) % 60;

	/* Number of years in days */ /*算出当前年份，起始的计数年份为1970年*/
	for (i = STARTOFTIME; day >= days_in_year(i); i++) {
		day -= days_in_year(i);
	}
	tm->tm_year = i;

	/* Number of months in days left */ /*计算当前的月份*/
	if (leapyear(tm->tm_year)) {
		days_in_month(FEBRUARY) = 29;
	}
	for (i = 1; day >= days_in_month(i); i++) {
		day -= days_in_month(i);
	}
	days_in_month(FEBRUARY) = 28;
	tm->tm_mon = i;

	/* Days are what is left over (+1) from all that. *//*计算当前日期*/
	tm->tm_mday = day + 1;

	/*
	 * Determine the day of week
	 */
	//GregorianDay(tm);  //不用转换成星期
	
}

