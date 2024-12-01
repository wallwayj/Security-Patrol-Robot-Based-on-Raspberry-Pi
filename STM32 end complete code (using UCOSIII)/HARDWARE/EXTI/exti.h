#ifndef __EXTI_H
#define __EXIT_H	 
#include "sys.h"
#include "stm32f10x_exti.h"

#define D0  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0)//读取按键0
#define D1  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1)//读取按键0
#define D2  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)//读取按键0
#define E3  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//读取按键0
#define E4  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//读取按键0

void EXTIX_Init(void);//外部中断初始化		 					    
#endif

