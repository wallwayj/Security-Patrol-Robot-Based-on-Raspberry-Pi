#ifndef __PWM_H
#define __PWM_H
#include "stm32f10x.h"    
               
#include "stm32f10x_tim.h"
void PWM_Init(void);
void PWM_SetCompare2(uint16_t Compare);
void PWM_SetCompare3(uint16_t Compare);
#endif
