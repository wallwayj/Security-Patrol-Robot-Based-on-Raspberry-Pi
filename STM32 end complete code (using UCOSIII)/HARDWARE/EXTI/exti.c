#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
#include"headfile.h"

//�ⲿ�ж�0�������
void EXTIX_Init(void)
{
 
   	EXTI_InitTypeDef EXTI_InitStructure;
 	  NVIC_InitTypeDef NVIC_InitStructure;
		
    KEY_Init();	 //	�����˿ڳ�ʼ��
		pio();
  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|RCC_APB2Periph_GPIOE |RCC_APB2Periph_GPIOD ,ENABLE);	//ʹ�ܸ��ù���ʱ��

   //GPIOD.0	  �ж����Լ��жϳ�ʼ������  �����ش���	 D0
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource0);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

   //GPIOD.2	  �ж����Լ��жϳ�ʼ������  �����ش���D2
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource2);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line2;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���
	
	  //GPIOD.4	  �ж����Լ��жϳ�ʼ������  �����ش���	D1
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOD,GPIO_PinSource1);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line1;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

   //GPIOE.3	  �ж����Լ��жϳ�ʼ������ �½��ش��� E3
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource3);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line3;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

   //GPIOE.4	  �ж����Լ��жϳ�ʼ������  �½��ش���	E4
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE,GPIO_PinSource4);
  	EXTI_InitStructure.EXTI_Line=EXTI_Line4;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���


   


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//ʹ�ܰ���WK_UP���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//�����ȼ�3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI1_IRQn;			//ʹ�ܰ���KEY0���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
		
		  NVIC_InitStructure.NVIC_IRQChannel = EXTI2_IRQn;			//ʹ�ܰ���KEY0���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
		
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;			//ʹ�ܰ���KEY1���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�1 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���

  	NVIC_InitStructure.NVIC_IRQChannel = EXTI4_IRQn;			//ʹ�ܰ���KEY0���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;					//�����ȼ�0 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
 
}

void EXTI0_IRQHandler(void)
{	
	OSIntEnter();
	delay_ms(10);//����
	if(D0==0)	 //����KEY0
	{

	}		 
	EXTI_ClearITPendingBit(EXTI_Line0);  //���LINE4�ϵ��жϱ�־λ  
	OSIntExit();
}

void EXTI1_IRQHandler(void)
{		OSIntEnter();
	delay_ms(10);//����
	if(D1==1)	 //����KEY0
	{
			beep=0;
	}	
else beep=1;	
	EXTI_ClearITPendingBit(EXTI_Line1);  //���LINE4�ϵ��жϱ�־λ  
	OSIntExit();
}

void EXTI2_IRQHandler(void)
{
	OSIntEnter();	
	delay_ms(10);//����
	if(D2==0)	 //����KEY0
	{

	}		 
	EXTI_ClearITPendingBit(EXTI_Line2);  //���LINE4�ϵ��жϱ�־λ 
	OSIntExit();	
}
 

//�ⲿ�ж�3�������
void EXTI3_IRQHandler(void)
{
	OSIntEnter();
	delay_ms(10);//����
	if(E3==0)	 //����KEY1
	{				 

	}		 
	EXTI_ClearITPendingBit(EXTI_Line3);  //���LINE3�ϵ��жϱ�־λ 
	OSIntExit();	 
}

void EXTI4_IRQHandler(void)
{	
	OSIntEnter();
	delay_ms(10);//����
	if(E4==0)	 //����KEY0
	{

	}		 
	EXTI_ClearITPendingBit(EXTI_Line4);  //���LINE4�ϵ��жϱ�־λ 
	OSIntExit();	
}
 
