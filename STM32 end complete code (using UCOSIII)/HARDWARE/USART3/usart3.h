#ifndef __USART3_H
#define __USART3_H	 
#include "sys.h"  
 
#define USART3_MAX_RECV_LEN		600					//�����ջ����ֽ���
#define USART3_MAX_SEND_LEN		600					//����ͻ����ֽ���
#define USART3_RX_EN 			1					//0,������;1,����.


#define USART2_MAX_RECV_LEN		1024					//�����ջ����ֽ���
#define USART2_MAX_SEND_LEN		1024					//����ͻ����ֽ���
#define USART2_RX_EN 			1					//0,������;1,����.


extern u8  USART3_RX_BUF[USART3_MAX_RECV_LEN]; 		//���ջ���,���USART3_MAX_RECV_LEN�ֽ�
extern u8  USART3_TX_BUF[USART3_MAX_SEND_LEN]; 		//���ͻ���,���USART3_MAX_SEND_LEN�ֽ�
extern vu16 USART3_RX_STA;   						//��������״̬


extern u8  USART2_RX_BUF[USART2_MAX_RECV_LEN]; 		//���ջ���,���USART2_MAX_RECV_LEN�ֽ�
extern u8  USART2_TX_BUF[USART2_MAX_SEND_LEN]; 		//���ͻ���,���USART2_MAX_SEND_LEN�ֽ�
extern vu16 USART2_RX_STA;   						//��������״̬

#define OPEN_USART2_RECEIVE		USART_ITConfig(USART2, USART_IT_RXNE, ENABLE)	//ʹ�ܽ����ж�
#define CLOSE_USART2_RECEIVE	USART_ITConfig(USART2, USART_IT_RXNE, DISABLE)	//�رս����ж�
#define USART2_TX	GPIO_Pin_2
#define USART2_RX	GPIO_Pin_3
void usart2_init(uint32_t baudRate);
void u2_printf(char* fmt,...);
void Uart2_SendStr(u8* SendBuf,u8 len);
void usart3_init(u32 bound);				//����2��ʼ�� 
void u3_printf(char* fmt,...);
#endif













