#ifndef __USART3_H
#define __USART3_H	 
#include "sys.h"  
 
#define USART3_MAX_RECV_LEN		600					//最大接收缓存字节数
#define USART3_MAX_SEND_LEN		600					//最大发送缓存字节数
#define USART3_RX_EN 			1					//0,不接收;1,接收.


#define USART2_MAX_RECV_LEN		1024					//最大接收缓存字节数
#define USART2_MAX_SEND_LEN		1024					//最大发送缓存字节数
#define USART2_RX_EN 			1					//0,不接收;1,接收.


extern u8  USART3_RX_BUF[USART3_MAX_RECV_LEN]; 		//接收缓冲,最大USART3_MAX_RECV_LEN字节
extern u8  USART3_TX_BUF[USART3_MAX_SEND_LEN]; 		//发送缓冲,最大USART3_MAX_SEND_LEN字节
extern vu16 USART3_RX_STA;   						//接收数据状态


extern u8  USART2_RX_BUF[USART2_MAX_RECV_LEN]; 		//接收缓冲,最大USART2_MAX_RECV_LEN字节
extern u8  USART2_TX_BUF[USART2_MAX_SEND_LEN]; 		//发送缓冲,最大USART2_MAX_SEND_LEN字节
extern vu16 USART2_RX_STA;   						//接收数据状态

#define OPEN_USART2_RECEIVE		USART_ITConfig(USART2, USART_IT_RXNE, ENABLE)	//使能接收中断
#define CLOSE_USART2_RECEIVE	USART_ITConfig(USART2, USART_IT_RXNE, DISABLE)	//关闭接收中断
#define USART2_TX	GPIO_Pin_2
#define USART2_RX	GPIO_Pin_3
void usart2_init(uint32_t baudRate);
void u2_printf(char* fmt,...);
void Uart2_SendStr(u8* SendBuf,u8 len);
void usart3_init(u32 bound);				//串口2初始化 
void u3_printf(char* fmt,...);
#endif













