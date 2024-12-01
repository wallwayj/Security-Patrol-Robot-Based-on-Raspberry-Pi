#ifndef __USART_H
#define __USART_H
#include "stm32f10x.h"
#include "stdio.h"

#define USART1_TX	GPIO_Pin_9
#define USART1_RX	GPIO_Pin_10

#define USART2_TX	GPIO_Pin_2
#define USART2_RX	GPIO_Pin_3

#define USART3_TX	GPIO_Pin_10
#define USART3_RX	GPIO_Pin_11

#define UART4_TX	GPIO_Pin_10
#define UART4_RX	GPIO_Pin_11

#define UART5_TX	GPIO_Pin_12
#define UART5_RX	GPIO_Pin_2


#define OPEN_USART1_RECEIVE		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE)	//使能接收中断
#define CLOSE_USART1_RECEIVE	USART_ITConfig(USART1, USART_IT_RXNE, DISABLE)	//关闭接收中断


#define OPEN_USART2_RECEIVE		USART_ITConfig(USART2, USART_IT_RXNE, ENABLE)	//使能接收中断
#define CLOSE_USART2_RECEIVE	USART_ITConfig(USART2, USART_IT_RXNE, DISABLE)	//关闭接收中断


#define OPEN_USART3_RECEIVE		USART_ITConfig(USART3, USART_IT_RXNE, ENABLE)	//使能接收中断
#define CLOSE_USART3_RECEIVE	USART_ITConfig(USART3, USART_IT_RXNE, DISABLE)	//关闭接收中断



void usart1_init(uint32_t baudRate);
void usart2_init(uint32_t baudRate);
void usart3_init(uint32_t baudRate);
#if 0
void uart4_init(uint32_t baudRate);
void uart5_init(uint32_t baudRate);
#endif
void usart_sendByte(USART_TypeDef* USARTx,uint8_t data);
void usart_sendString(USART_TypeDef* USARTx,char *str);


void USART2_SendData(u8 data);
void USART2_SendString(u8 *DAT, u8 len);
#endif


