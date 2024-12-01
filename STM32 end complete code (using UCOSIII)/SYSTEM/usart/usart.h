#ifndef __USART_H
#define __USART_H
#include "stdio.h"	
#include "sys.h" 
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//Mini STM32������
//����1��ʼ��		   
//����ԭ��@ALIENTEK
//������̳:www.openedv.csom
//�޸�����:2011/6/14
//�汾��V1.4
//��Ȩ���У�����ؾ���
//Copyright(C) ����ԭ�� 2009-2019
//All rights reserved
//********************************************************************************
//V1.3�޸�˵�� 
//֧����Ӧ��ͬƵ���µĴ��ڲ���������.
//�����˶�printf��֧��
//�����˴��ڽ��������.
//������printf��һ���ַ���ʧ��bug
//V1.4�޸�˵��
//1,�޸Ĵ��ڳ�ʼ��IO��bug
//2,�޸���USART_RX_STA,ʹ�ô����������ֽ���Ϊ2��14�η�
//3,������USART_REC_LEN,���ڶ��崮�����������յ��ֽ���(������2��14�η�)
//4,�޸���EN_USART1_RX��ʹ�ܷ�ʽ
////////////////////////////////////////////////////////////////////////////////// 	
#define USART_REC_LEN  			200  	//�����������ֽ��� 200
#define EN_USART1_RX 			1		//ʹ�ܣ�1��/��ֹ��0������1����
	  	
extern u8  USART_RX_BUF[USART_REC_LEN]; //���ջ���,���USART_REC_LEN���ֽ�.ĩ�ֽ�Ϊ���з� 
extern u16 USART_RX_STA;         		//����״̬���	
//����봮���жϽ��գ��벻Ҫע�����º궨��
void uart_init(u32 bound);

#define USART1_TX	GPIO_Pin_9
#define USART1_RX	GPIO_Pin_10



#define USART3_TX	GPIO_Pin_10
#define USART3_RX	GPIO_Pin_11

#define UART4_TX	GPIO_Pin_10
#define UART4_RX	GPIO_Pin_11

#define UART5_TX	GPIO_Pin_12
#define UART5_RX	GPIO_Pin_2


#define OPEN_USART1_RECEIVE		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE)	//ʹ�ܽ����ж�
#define CLOSE_USART1_RECEIVE	USART_ITConfig(USART1, USART_IT_RXNE, DISABLE)	//�رս����ж�



#define OPEN_USART3_RECEIVE		USART_ITConfig(USART3, USART_IT_RXNE, ENABLE)	//ʹ�ܽ����ж�
#define CLOSE_USART3_RECEIVE	USART_ITConfig(USART3, USART_IT_RXNE, DISABLE)	//�رս����ж�


 
 
void uart4_init(uint32_t baudRate);
void uart5_init(uint32_t baudRate);
 
void usart_sendByte(USART_TypeDef* USARTx,uint8_t data);
void usart_sendString(USART_TypeDef* USARTx,char *str);


void USART2_SendData(u8 data);
void USART2_SendString(u8 *DAT, u8 len);
#endif


