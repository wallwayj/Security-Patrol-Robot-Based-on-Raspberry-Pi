#ifndef __usartt_H
#define __usartt_H


#include <stdarg.h>
#include <stdio.h>	 	 
#include <string.h>	 
#include "sys.h"
#include "usart.h"
#include "delay.h"
//////////// #define USART1_TX	GPIO_Pin_A9
////////////#define USART1_RX	GPIO_Pin_A10

////////////#define USART2_TX	GPIO_Pin_A2
////////////#define USART2_RX	GPIO_Pin_A3

////////////#define USART3_TX	GPIO_Pin_B10
////////////#define USART3_RX	GPIO_Pin_B11

////////////#define UART4_TX	GPIO_Pin_C10
////////////#define UART4_RX	GPIO_Pin_C11

////////////#define UART5_TX	GPIO_Pin_C12
////////////#define UART5_RX	GPIO_Pin_D2

void uart2_init(u32 hz);
#define USART3_MAX_RECV_LEN 1024
#define USART3_MAX_SEND_LEN 1024

extern vu16 USART3_RX_STA;         		//接收状态标记
extern u8 USART3_RX_BUF[USART3_MAX_RECV_LEN]; 		//接收缓冲,最大USART3_MAX_RECV_LEN个字节.
extern u8 USART3_TX_BUF[USART3_MAX_SEND_LEN]; 		//发送缓冲,最大USART3_MAX_SEND_LEN字节

void uart3_init(u32 bound);
void u3_printf(char* fmt,...);
void Uart3_SendStr(u8* SendBuf,u8 len);

void usart4_init(u32 btl);
void UART4_Send_Byte(u8 Data); //发送一个字节；;
void UART4_Send_String(u8 *Data) ;//发送字符串；
void UART4_IRQHandler(void); //中断处理函数；

void usart5_init(u32 btl);
void UART5_Send_Byte(u8 Data) ;
void UART5_Send_String(u8 *Data);
void UART5_IRQHandler(void);




#endif
