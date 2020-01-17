#ifndef __XY_MEASURE_H__
#define __XY_MEASURE_H__
#include "xy_config.h"


typedef struct {
	u16 XB;										//血红蛋白浓度
	u8 	sex;									//性别
	u8 	GasType;								//收集气体的样本类型   (吹气和采气"自动呼气采集仪器")
}Measure_Message;						//测量出入参数结构体


#endif


