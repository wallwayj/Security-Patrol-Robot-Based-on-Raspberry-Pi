#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
#include"headfile.h"

//外部中断0服务程序
void EXTIX_Init(void)
{
 
   	EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;
		
    KEY_Init();	 //	按键端口初始化
		pio();
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOE |RCC_APB2Periph_GPIOD ,ENABLE);	//使能复用功能时钟

   //GPIOD.0	  中断线以及中断初始化配置  上升沿触发	 D0
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource0);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

   //GPIOD.2	  中断线以及中断初始化配置  上升沿触发D2
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource2);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line2;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器
	
	  //GPIOD.4	  中断线以及中断初始化配置  上升沿触发	D1
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource1);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

   //GPIOE.3	  中断线以及中断初始化配置 下降沿触发 E3
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器

   //GPIOE.4	  中断线以及中断初始化配置  下降沿触发	E4
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
  	EXTI_Init(&EXTI_InitStructure);	  	//根据EXTI_InitStruct中指定的参数初始化外设EXTI寄存器


   


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//使能按键WK_UP所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2， 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//子优先级3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure); 

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//使能按键KEY0所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
		
		  NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//使能按键KEY0所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
		
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//使能按键KEY1所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//子优先级1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//使能按键KEY0所在的外部中断通道
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//抢占优先级2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//子优先级0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//使能外部中断通道
  	NVIC_Init(&NVIC_InitStructure);  	  //根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器
 
}

void EXTI0_IRQHandler(void)
{	
	OSIntEnter();
	delay_ms(10);//消抖
	if(D0==0)	 //按键KEY0
	{

	}		 
	EXTI_ClearITPendingBit(EXTI_Line0);  //清除LINE4上的中断标志位  
	OSIntExit();
}

void EXTI1_IRQHandler(void)
{		OSIntEnter();
	delay_ms(10);//消抖
	if(D1==1)	 //按键KEY0
	{
			beep=0;
	}	
else beep=1;	
	EXTI_ClearITPendingBit(EXTI_Line1);  //清除LINE4上的中断标志位  
	OSIntExit();
}

void EXTI2_IRQHandler(void)
{
	OSIntEnter();	
	delay_ms(10);//消抖
	if(D2==0)	 //按键KEY0
	{

	}		 
	EXTI_ClearITPendingBit(EXTI_Line2);  //清除LINE4上的中断标志位 
	OSIntExit();	
}
 

//外部中断3服务程序
void EXTI3_IRQHandler(void)
{
	OSIntEnter();
	delay_ms(10);//消抖
	if(E3==0)	 //按键KEY1
	{				 

	}		 
	EXTI_ClearITPendingBit(EXTI_Line3);  //清除LINE3上的中断标志位 
	OSIntExit();	 
}

void EXTI4_IRQHandler(void)
{	
	OSIntEnter();
	delay_ms(10);//消抖
	if(E4==0)	 //按键KEY0
	{

	}		 
	EXTI_ClearITPendingBit(EXTI_Line4);  //清除LINE4上的中断标志位 
	OSIntExit();	
}
 
