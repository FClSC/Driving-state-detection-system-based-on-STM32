#ifndef __LED_H
#define __LED_H

#include "sys.h"

#define LED1 PCout(13)// PC13
void LED_Init(void);
void LED1_On(void);
void LED1_Off(void);

extern void Init_LEDpin(void);


#endif


