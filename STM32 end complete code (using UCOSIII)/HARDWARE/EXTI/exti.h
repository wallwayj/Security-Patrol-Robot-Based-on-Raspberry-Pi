#ifndef __EXTI_H
#define __EXIT_H	 
#include "sys.h"
#include "stm32f10x_exti.h"

#define D0  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0)//��ȡ����0
#define D1  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1)//��ȡ����0
#define D2  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)//��ȡ����0
#define E3  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//��ȡ����0
#define E4  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//��ȡ����0

void EXTIX_Init(void);//�ⲿ�жϳ�ʼ��		 					    
#endif

