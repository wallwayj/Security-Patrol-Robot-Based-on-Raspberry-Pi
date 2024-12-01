#include "delay.h"
#include "usart3.h"
#include "stdarg.h"	 	 
#include "stdio.h"	 	 
#include "string.h"	 
#include "timer.h"
#include "usart.h"
#define USART3_RXBUF_LEN 15
//���ڽ��ջ����� 	
u8 USART3_RX_BUF[USART3_MAX_RECV_LEN]; 				//���ջ���,���USART3_MAX_RECV_LEN���ֽ�.
u8  USART3_TX_BUF[USART3_MAX_SEND_LEN]; 			//���ͻ���,���USART3_MAX_SEND_LEN�ֽ�


u8 USART2_RX_BUF[USART2_MAX_RECV_LEN]; 				//���ջ���,���USART2_MAX_RECV_LEN���ֽ�.
u8  USART2_TX_BUF[USART2_MAX_SEND_LEN]; 			//���ͻ���,���USART2_MAX_SEND_LEN�ֽ�
vu16 USART2_RX_STA=0;   	

//����ɨ���£�   timer=1S
//������ɨ���£� timer=10ms
//ͨ���жϽ�������2���ַ�֮���ʱ������timer�������ǲ���һ������������.
//���2���ַ����ռ������timer,����Ϊ����1����������.Ҳ���ǳ���timerû�н��յ�
//�κ�����,���ʾ�˴ν������.
//���յ�������״̬
//[15]:0,û�н��յ�����;1,���յ���һ������.
//[14:0]:���յ������ݳ���
vu16 USART3_RX_STA=0;   	


void USART3_IRQHandler(void)
{
	u8 res;	      
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)//���յ�����
	{	 
		res =USART_ReceiveData(USART3);		 
		if((USART3_RX_STA&(1<<15))==0)//�������һ������,��û�б�����,���ٽ�����������
		{ 
			if(USART3_RX_STA<USART3_MAX_RECV_LEN)	//�����Խ�������
			{
				TIM_SetCounter(TIM7,0);             //���������          				
				if(USART3_RX_STA==0) 				//ʹ�ܶ�ʱ��7���ж� 
				{
					TIM_Cmd(TIM7,ENABLE);           //ʹ�ܶ�ʱ��7
				}
				USART3_RX_BUF[USART3_RX_STA++]=res;	//��¼���յ���ֵ	 
			}else 
			{
				USART3_RX_STA|=1<<15;				//ǿ�Ʊ�ǽ������
			} 
		}
	}  				 											 
}   


//��ʼ��IO ����3
//pclk1:PCLK1ʱ��Ƶ��(Mhz)
//bound:������	  
void usart3_init(u32 bound)
{  

	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	                       //GPIOBʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);                          //����3ʱ��ʹ��

 	USART_DeInit(USART3);  //��λ����3
		 //USART3_TX   PB10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;                                     //PB10
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	                               //�����������
    GPIO_Init(GPIOB, &GPIO_InitStructure);                                         //��ʼ��PB10
   
    //USART3_RX	  PB11
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;                          //��������
    GPIO_Init(GPIOB, &GPIO_InitStructure);                                         //��ʼ��PB11
	
	USART_InitStructure.USART_BaudRate = bound;                                    //������һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                    //�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                         //һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;                            //����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	               //�շ�ģʽ
  
	USART_Init(USART3, &USART_InitStructure);       //��ʼ������3
  

	USART_Cmd(USART3, ENABLE);                      //ʹ�ܴ��� 
	
	//ʹ�ܽ����ж�
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);  //�����ж�   
	
	//�����ж����ȼ�
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	
	
	TIM7_Int_Init(99,7199);		//10ms�ж�
	USART3_RX_STA=0;		    //����
	TIM_Cmd(TIM7,DISABLE);		//�رն�ʱ��7

}

//����3,printf ����
//ȷ��һ�η������ݲ�����USART3_MAX_SEND_LEN�ֽ�
void u3_printf(char* fmt,...)  
{  
	u16 i,j; 
	va_list ap; 
	va_start(ap,fmt);
	vsprintf((char*)USART3_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART3_TX_BUF);		//�˴η������ݵĳ���
	for(j=0;j<i;j++)							//ѭ����������
	{
	  while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET); //ѭ������,ֱ���������   
		USART_SendData(USART3,USART3_TX_BUF[j]); 
	} 
}

 


static void NVIC_USART2_configuration(void)
{
	NVIC_InitTypeDef NVIC_initStruction;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//��
	NVIC_initStruction.NVIC_IRQChannel = USART2_IRQn;			//����2�ж�
	NVIC_initStruction.NVIC_IRQChannelPreemptionPriority = 1;   //�����ȼ�  
	NVIC_initStruction.NVIC_IRQChannelSubPriority = 0;			//�����ȼ�
	NVIC_initStruction.NVIC_IRQChannelCmd = ENABLE;				//ʹ��	
	NVIC_Init(&NVIC_initStruction);
}

/* ���ô���2 ����*/
void usart2_init(uint32_t baudRate)
{	GPIO_InitTypeDef GPIO_initStruction;USART_InitTypeDef USART_initStruction;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//��GPIOAʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//�򿪴���2ʱ��

	/*����GPIOA  TX */
	GPIO_initStruction.GPIO_Pin = USART2_TX; 		// TX
	GPIO_initStruction.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
	GPIO_initStruction.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_initStruction);
	
	/*����GPIOA RX */
	GPIO_initStruction.GPIO_Pin = USART2_RX; 		// RX
	GPIO_initStruction.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
	GPIO_Init(GPIOA, &GPIO_initStruction);
	
	/*����USART1 TX��RX */
	USART_initStruction.USART_BaudRate = baudRate;	//������
	USART_initStruction.USART_WordLength = USART_WordLength_8b; //8λ��Ч����λ
	USART_initStruction.USART_StopBits = USART_StopBits_1;	//1��ֹͣλ
	USART_initStruction.USART_Parity = USART_Parity_No;		//����żУ��λ
	USART_initStruction.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //��Ӳ��������
	USART_initStruction.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; //���� �� ����
	USART_Init(USART2, &USART_initStruction);
	
	NVIC_USART2_configuration();	//����2�ж����ȼ�����
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//
	USART_Cmd(USART2, ENABLE); //ʹ�ܴ���2
	
		
	TIM4_Int_Init(1000-1,7200-1);		//10ms�ж�
	USART2_RX_STA=0;		    //����
	TIM_Cmd(TIM4,DISABLE);		//�رն�ʱ��7
}

void USART2_IRQHandler(void)
{
	u8 res;	      
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)//���յ�����
	{	 
		res =USART_ReceiveData(USART2);		 
		if((USART2_RX_STA&(1<<15))==0)//�������һ������,��û�б�����,���ٽ�����������
		{ 
			if(USART2_RX_STA<USART2_MAX_RECV_LEN)	//�����Խ�������
			{
				TIM_SetCounter(TIM4,0);             //���������          				
				if(USART2_RX_STA==0) 				//ʹ�ܶ�ʱ��7���ж� 
				{
					TIM_Cmd(TIM4,ENABLE);           //ʹ�ܶ�ʱ��7
				}
				USART2_RX_BUF[USART2_RX_STA++]=res;	//��¼���յ���ֵ	 
			}else 
			{
				USART2_RX_STA|=1<<15;				//ǿ�Ʊ�ǽ������
			} 
		}
	}  				 											 
}   
void Uart2_SendStr(u8* SendBuf,u8 len)
{
	int t;
//	len=SendBuf&0x3fff;//�õ��˴ν��յ������ݳ���
	for(t=0;t<len;t++)
	{
		USART_SendData(USART2, SendBuf[t]);//�򴮿�1��������
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//�ȴ����ͽ���
	}
	printf("\r\n\r\n");//���뻻��
}
//����2,printf ����
//ȷ��һ�η������ݲ�����USART2_MAX_SEND_LEN�ֽ�
void u2_printf(char* fmt,...)  
{  
	u16 i,j; 
	va_list ap; 
	va_start(ap,fmt);
	vsprintf((char*)USART2_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART2_TX_BUF);		//�˴η������ݵĳ���
	for(j=0;j<i;j++)							//ѭ����������
	{
	  while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET); //ѭ������,ֱ���������   
		USART_SendData(USART2,USART2_TX_BUF[j]); 
	} 
	memset(USART2_TX_BUF, 0, USART2_MAX_SEND_LEN); 
}


















