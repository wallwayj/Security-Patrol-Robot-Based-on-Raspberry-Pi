#include"sys.h"
c
 
void usart4_init(u32 btl)
{

	GPIO_InitTypeDef GPIO_InitStructure;

	USART_InitTypeDef USART_InitStructure;

	NVIC_InitTypeDef NVIC_InitStructure;        

	 

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE );

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE );

	 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //UART4 TX��

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�������������

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOC, &GPIO_InitStructure); //�˿�C��

			

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //UART4 RX��

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //�������룻

	GPIO_Init(GPIOC, &GPIO_InitStructure); //�˿�C��

	 

	USART_InitStructure.USART_BaudRate = btl; //�����ʣ�

	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //����λ8λ��

	USART_InitStructure.USART_StopBits = USART_StopBits_1; //ֹͣλ1λ��

	USART_InitStructure.USART_Parity = USART_Parity_No ; //��У��λ��

	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

	//��Ӳ�����أ�

	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	//�շ�ģʽ��

	USART_Init(UART4, &USART_InitStructure);//���ô��ڲ�����

	 

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //�����ж��飬4λ��ռ���ȼ���4λ��Ӧ���ȼ���

	 

	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn; //�жϺţ�

	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //��ռ���ȼ���

	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //��Ӧ���ȼ���

	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStructure);

	 

	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);

	USART_Cmd(UART4, ENABLE); //ʹ�ܴ��ڣ�

}

 

void UART4_Send_Byte(u8 Data) //����һ���ֽڣ�

{

	USART_SendData(UART4,Data);

	while( USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET );

}

 

void UART4_Send_String(u8 *Data) //�����ַ�����

{

	while(*Data)

	UART4_Send_Byte(*Data++);

}

 

//void UART4_IRQHandler(void) //�жϴ�������

//{

//u8 res;    

//if(USART_GetITStatus(UART4, USART_IT_RXNE) == SET) //�ж��Ƿ����жϣ�

//{

//USART_ClearFlag(UART4, USART_IT_RXNE); //�����־λ��

//res=USART_ReceiveData(UART4); //�������ݣ�

//UART4_Send_Byte(res); //�û��Զ��壻

//}  

//} 
 





void usart5_init(u32 btl)

{

GPIO_InitTypeDef GPIO_InitStructure;

USART_InitTypeDef USART_InitStructure;

NVIC_InitTypeDef NVIC_InitStructure;        

 

RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE );

RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE );

 

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; //UART5 TX��

GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //�������������

GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

GPIO_Init(GPIOC, &GPIO_InitStructure); //�˿�C��

    

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //UART4 RX��

GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //�������룻

GPIO_Init(GPIOD, &GPIO_InitStructure); //�˿�D��

 

USART_InitStructure.USART_BaudRate = btl; //�����ʣ�

USART_InitStructure.USART_WordLength = USART_WordLength_8b; //����λ8λ��

USART_InitStructure.USART_StopBits = USART_StopBits_1; //ֹͣλ1λ��

USART_InitStructure.USART_Parity = USART_Parity_No ; //��У��λ��

USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

//��Ӳ�����أ�

USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

//�շ�ģʽ��

USART_Init(UART5, &USART_InitStructure);//���ô��ڲ�����

 

NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //�����ж��飬4λ��ռ���ȼ���4λ��Ӧ���ȼ���

 

NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn; //�жϺţ�

NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //��ռ���ȼ���

NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //��Ӧ���ȼ���

NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

NVIC_Init(&NVIC_InitStructure);

 

USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);

USART_Cmd(UART5, ENABLE); //ʹ�ܴ��ڣ�

}

 

void UART5_Send_Byte(u8 Data) //����һ���ֽڣ�

{

USART_SendData(UART5,Data);

while( USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET );

}

 

void UART5_Send_String(u8 *Data) //�����ַ�����

{

while(*Data)

UART5_Send_Byte(*Data++);

}

 

//void UART5_IRQHandler(void) //�жϴ�������

//{

//u8 res;    

//if(USART_GetITStatus(UART5, USART_IT_RXNE) == SET) //�ж��Ƿ����жϣ�

//{

//USART_ClearFlag(UART5, USART_IT_RXNE); //�����־λ��

//res=USART_ReceiveData(UART5); //�������ݣ�

//UART5_Send_Byte(res); //�û��Զ��壻

//}  

//} 



