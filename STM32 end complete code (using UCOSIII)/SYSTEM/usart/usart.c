#include "sys.h"
#include "usart.h"	  
////////////////////////////////////////////////////////////////////////////////// 	 
//���ʹ��os,����������ͷ�ļ�����.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//os ʹ��	  
#endif

//////////////////////////////////////////////////////////////////
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

/*ʹ��microLib�ķ���*/
 /* 
int fputc(int ch, FILE *f)
{
	USART_SendData(USART1, (uint8_t) ch);

	while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET) {}	
   
    return ch;
}
int GetKey (void)  { 

    while (!(USART1->SR & USART_FLAG_RXNE));

    return ((int)(USART1->DR & 0x1FF));
}
*/
 
#if EN_USART1_RX   //���ʹ���˽���
//����1�жϷ������
//ע��,��ȡUSARTx->SR�ܱ���Ī������Ĵ���   	
u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
//����״̬
//bit15��	������ɱ�־
//bit14��	���յ�0x0d
//bit13~0��	���յ�����Ч�ֽ���Ŀ
u16 USART_RX_STA=0;       //����״̬���	  

//��ʼ��IO ����1 
//bound:������
void uart_init(u32 bound){
    //GPIO�˿�����
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//ʹ��USART1��GPIOAʱ��
 	USART_DeInit(USART1);  //��λ����1
	 //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//�����������
    GPIO_Init(GPIOA, &GPIO_InitStructure); //��ʼ��PA9
   
    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//��������
    GPIO_Init(GPIOA, &GPIO_InitStructure);  //��ʼ��PA10

   //Usart1 NVIC ����

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//��ռ���ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//�����ȼ�3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
  
   //USART ��ʼ������
	USART_InitStructure.USART_BaudRate = bound;//һ������Ϊ9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//�ֳ�Ϊ8λ���ݸ�ʽ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//һ��ֹͣλ
	USART_InitStructure.USART_Parity = USART_Parity_No;//����żУ��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//��Ӳ������������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//�շ�ģʽ

    USART_Init(USART1, &USART_InitStructure); //��ʼ������
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//�����ж�
    USART_Cmd(USART1, ENABLE);                    //ʹ�ܴ��� 

}


#endif	


/****************************����2******************************/
/****************************����2******************************/
/* ���ô���2 ���ȼ� ���� */





/****************************����3******************************/
/****************************����3******************************/


/****************************����4******************************/
/****************************����4******************************/
/* ���ô���4 ���ȼ� ���� */
static void NVIC_UART4_configuration(void)
{
	NVIC_InitTypeDef NVIC_initStruction;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);				//��
	NVIC_initStruction.NVIC_IRQChannel = UART4_IRQn;			//����4�ж�
	NVIC_initStruction.NVIC_IRQChannelPreemptionPriority = 1;   //�����ȼ� 
	NVIC_initStruction.NVIC_IRQChannelSubPriority = 2;			//�����ȼ�
	NVIC_initStruction.NVIC_IRQChannelCmd = ENABLE;				//ʹ��
	
	NVIC_Init(&NVIC_initStruction);
}

/* ���ô���4 ����*/
void uart4_init(uint32_t baudRate)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	//��GPIOCʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);	//�򿪴���4ʱ��
	
	GPIO_InitTypeDef GPIO_initStruction;
	USART_InitTypeDef USART_initStruction;

	/*����GPIOC  TX */
	GPIO_initStruction.GPIO_Pin = UART4_TX; 		// TX
	GPIO_initStruction.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
	GPIO_initStruction.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_initStruction);
	
	/*����GPIOC RX */
	GPIO_initStruction.GPIO_Pin = UART4_RX; 		// RX
	GPIO_initStruction.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
	GPIO_Init(GPIOC, &GPIO_initStruction);
	
	/*����UART4 TX��RX */
	USART_initStruction.USART_BaudRate = baudRate;	//������
	USART_initStruction.USART_WordLength = USART_WordLength_8b; //8λ��Ч����λ
	USART_initStruction.USART_StopBits = USART_StopBits_1;	//1��ֹͣλ
	USART_initStruction.USART_Parity = USART_Parity_No;		//����żУ��λ
	USART_initStruction.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //��Ӳ��������
	USART_initStruction.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; //���� �� ����
	USART_Init(UART4, &USART_initStruction);
	
	NVIC_UART4_configuration();	//����4�ж����ȼ�����
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//ʹ�ܽ����ж�
	USART_Cmd(UART4, ENABLE); //ʹ�ܴ���4
}


/****************************����5******************************/
/****************************����5******************************/
/* ���ô���5 ���ȼ� ���� */
static void NVIC_UART5_configuration(void)
{
	NVIC_InitTypeDef NVIC_initStruction;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);				//��
	NVIC_initStruction.NVIC_IRQChannel = UART5_IRQn;			//����5�ж�
	NVIC_initStruction.NVIC_IRQChannelPreemptionPriority = 1;   //�����ȼ�  
	NVIC_initStruction.NVIC_IRQChannelSubPriority = 3;			//�����ȼ�	
	NVIC_initStruction.NVIC_IRQChannelCmd = ENABLE;				//ʹ��
	
	NVIC_Init(&NVIC_initStruction);
}

/* ���ô���5 ����*/
void uart5_init(uint32_t baudRate)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	//��GPIOCʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	//��GPIODʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);	//�򿪴���5ʱ��
	
	GPIO_InitTypeDef GPIO_initStruction;
	USART_InitTypeDef USART_initStruction;

	/*����GPIOC  TX */
	GPIO_initStruction.GPIO_Pin = UART5_TX; 		// TX
	GPIO_initStruction.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
	GPIO_initStruction.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_initStruction);
	
	/*����GPIOD RX */
	GPIO_initStruction.GPIO_Pin = UART5_RX; 		// RX
	GPIO_initStruction.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
	GPIO_Init(GPIOD, &GPIO_initStruction);
	
	/*����UART4 TX��RX */
	USART_initStruction.USART_BaudRate = baudRate;	//������
	USART_initStruction.USART_WordLength = USART_WordLength_8b; //8λ��Ч����λ
	USART_initStruction.USART_StopBits = USART_StopBits_1;	//1��ֹͣλ
	USART_initStruction.USART_Parity = USART_Parity_No;		//����żУ��λ
	USART_initStruction.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //��Ӳ��������
	USART_initStruction.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; //���� �� ����
	USART_Init(UART5, &USART_initStruction);
	
	NVIC_UART5_configuration();	//����5�ж����ȼ�����
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//ʹ�ܽ����ж�
	USART_Cmd(UART5, ENABLE); //ʹ�ܴ���5
}



/*���� ����1�ֽ� ����*/
void usart_sendByte(USART_TypeDef* USARTx,uint8_t data)
{
	USART_SendData(USARTx, data);
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET); //�ȴ����ͼĴ���Ϊ�� ֤��������
}

/*���� �����ַ��� ����*/
void usart_sendString(USART_TypeDef* USARTx,char *str)
{
	while(*str != '\0')
	{
		usart_sendByte(USARTx,*str);
		str++;
	}
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET); //������ɱ�־λ
}


/*****************************************************************************
����: ����2 ����1�ֽ� ����
******************************************************************************/
void USART2_SendData(u8 data)
{
	while((USART2->SR & 0X40) == 0);
	USART2->DR = data;
}
/*****************************************************************************
����: ����2 �����ַ��� ����
******************************************************************************/
void USART2_SendString(u8 *DAT, u8 len)
{
	u8 i;
	for(i = 0; i < len; i++)
	{
		USART2_SendData(*DAT++);
	}
}

