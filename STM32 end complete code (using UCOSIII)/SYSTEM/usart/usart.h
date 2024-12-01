#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//Mini STM32开发板
//串口1初始化		   
//正点原子@ALIENTEK
//技术论坛:www.openedv.csom
//修改日期:2011/6/14
//版本：V1.4
//版权所有，盗版必究。
//Copyright(C) 正点原子 2009-2019
//All rights reserved
//********************************************************************************
//V1.3修改说明 
//支持适应不同频率下的串口波特率设置.
//加入了对printf的支持
//增加了串口接收命令功能.
//修正了printf第一个字符丢失的bug
//V1.4修改说明
//1,修改串口初始化IO的bug
//2,修改了USART_RX_STA,使得串口最大接收字节数为2的14次方
//3,增加了USART_REC_LEN,用于定义串口最大允许接收的字节数(不大于2的14次方)
//4,修改了EN_USART1_RX的使能方式
////////////////////////////////////////////////////////////////////////////////// 	
#define USART_REC_LEN  			200  	//定义最大接收字节数 200
#define EN_USART1_RX 			1		//使能（1）/禁止（0）串口1接收
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节.末字节为换行符 
extern u16 USART_RX_STA;         		//接收状态标记	
//如果想串口中断接收，请不要注释以下宏定义
void uart_init(u32 bound);

#define USART1_TX	GPIO_Pin_9
#define USART1_RX	GPIO_Pin_10



#define USART3_TX	GPIO_Pin_10
#define USART3_RX	GPIO_Pin_11

#define UART4_TX	GPIO_Pin_10
#define UART4_RX	GPIO_Pin_11

#define UART5_TX	GPIO_Pin_12
#define UART5_RX	GPIO_Pin_2


#define OPEN_USART1_RECEIVE		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE)	//使能接收中断
#define CLOSE_USART1_RECEIVE	USART_ITConfig(USART1, USART_IT_RXNE, DISABLE)	//关闭接收中断



#define OPEN_USART3_RECEIVE		USART_ITConfig(USART3, USART_IT_RXNE, ENABLE)	//使能接收中断
#define CLOSE_USART3_RECEIVE	USART_ITConfig(USART3, USART_IT_RXNE, DISABLE)	//关闭接收中断


 
 
void uart4_init(uint32_t baudRate);
void uart5_init(uint32_t baudRate);
 
void usart_sendByte(USART_TypeDef* USARTx,uint8_t data);
void usart_sendString(USART_TypeDef* USARTx,char *str);


void USART2_SendData(u8 data);
void USART2_SendString(u8 *DAT, u8 len);
#endif


