#ifndef __USART1_H
#define	__USART1_H

#include "stm32f10x.h"
#include <stdio.h>


void USART1_Config(int bpr);
void USART1_Timeout_UserCallback(void);

#if 0

extern int fputc(int ch, FILE *f);
extern int fgetc(FILE *f);

#endif
#endif /* __USART1_H */


 
 
