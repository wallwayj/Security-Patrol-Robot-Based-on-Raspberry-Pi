//#include "usart.h"
//#include"stdio.h"
//#include "usart.h"	  
//////////////////////////////////////////////////////////////////////////////////// 	 
////���ʹ��ucos,����������ͷ�ļ�����.
//#if SYSTEM_SUPPORT_OS
//#include "includes.h"					//ucos ʹ��	  
//#endif
//  
//#if 1
//#pragma import(__use_no_semihosting)             
////��׼����Ҫ��֧�ֺ���                 
//struct __FILE 
//{ 
//	int handle; 

//}; 

//FILE __stdout;       
////����_sys_exit()�Ա���ʹ�ð�����ģʽ    
//_sys_exit(uint32_t x) 
//{ 
//	x = x; 
//} 
////�ض���fputc���� 
//int fputc(uint32_t ch, FILE *f)
//{      
//	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
//    USART1->DR = (u8) ch;      
//	return ch;
//}
//#endif 
///****************************����1******************************/
///****************************����1******************************/
///* ���ô���1 ���ȼ� ���� */
//static void NVIC_USART1_configuration(void)
//{
//	NVIC_InitTypeDef NVIC_initStruction;
//	
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);				//��
//	NVIC_initStruction.NVIC_IRQChannel = USART1_IRQn;			//����1�ж�
//	NVIC_initStruction.NVIC_IRQChannelPreemptionPriority = 0;   //�����ȼ�
//	NVIC_initStruction.NVIC_IRQChannelSubPriority = 0;			//�����ȼ�
//	NVIC_initStruction.NVIC_IRQChannelCmd = ENABLE;				//ʹ��
//	NVIC_Init(&NVIC_initStruction);
//}

///* ���ô���1 ����*/
//void usart1_init(uint32_t baudRate)
//{	GPIO_InitTypeDef GPIO_initStruction;
//	USART_InitTypeDef USART_initStruction;
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//��GPIOAʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//�򿪴���1ʱ��
//	


//	/*����GPIOA  TX */
//	GPIO_initStruction.GPIO_Pin = USART1_TX; 		// TX
//	GPIO_initStruction.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
//	GPIO_initStruction.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_initStruction);
//	
//	/*����GPIOA RX */
//	GPIO_initStruction.GPIO_Pin = USART1_RX; 		// RX
//	GPIO_initStruction.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
//	GPIO_Init(GPIOA, &GPIO_initStruction);
//	
//	/*����USART1 TX��RX */
//	USART_initStruction.USART_BaudRate = baudRate;	//������
//	USART_initStruction.USART_WordLength = USART_WordLength_8b; //8λ��Ч����λ
//	USART_initStruction.USART_StopBits = USART_StopBits_1;	//1��ֹͣλ
//	USART_initStruction.USART_Parity = USART_Parity_No;		//����żУ��λ
//	USART_initStruction.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //��Ӳ��������
//	USART_initStruction.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; //���� �� ����
//	USART_Init(USART1, &USART_initStruction);
//	
//	NVIC_USART1_configuration();	//����1�ж����ȼ�����
//	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//ʹ�ܽ����ж�
//	USART_Cmd(USART1, ENABLE); //ʹ�ܴ���1
//}

///****************************����2******************************/
///****************************����2******************************/
///* ���ô���2 ���ȼ� ���� */
//static void NVIC_USART2_configuration(void)
//{
//	NVIC_InitTypeDef NVIC_initStruction;
//	
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//��
//	NVIC_initStruction.NVIC_IRQChannel = USART2_IRQn;			//����2�ж�
//	NVIC_initStruction.NVIC_IRQChannelPreemptionPriority = 1;   //�����ȼ�  
//	NVIC_initStruction.NVIC_IRQChannelSubPriority = 0;			//�����ȼ�
//	NVIC_initStruction.NVIC_IRQChannelCmd = ENABLE;				//ʹ��	
//	NVIC_Init(&NVIC_initStruction);
//}

///* ���ô���2 ����*/
//void usart2_init(uint32_t baudRate)
//{	GPIO_InitTypeDef GPIO_initStruction;USART_InitTypeDef USART_initStruction;
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//��GPIOAʱ��
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//�򿪴���2ʱ��
//	

//	

//	/*����GPIOA  TX */
//	GPIO_initStruction.GPIO_Pin = USART2_TX; 		// TX
//	GPIO_initStruction.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
//	GPIO_initStruction.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_initStruction);
//	
//	/*����GPIOA RX */
//	GPIO_initStruction.GPIO_Pin = USART2_RX; 		// RX
//	GPIO_initStruction.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
//	GPIO_Init(GPIOA, &GPIO_initStruction);
//	
//	/*����USART1 TX��RX */
//	USART_initStruction.USART_BaudRate = baudRate;	//������
//	USART_initStruction.USART_WordLength = USART_WordLength_8b; //8λ��Ч����λ
//	USART_initStruction.USART_StopBits = USART_StopBits_1;	//1��ֹͣλ
//	USART_initStruction.USART_Parity = USART_Parity_No;		//����żУ��λ
//	USART_initStruction.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //��Ӳ��������
//	USART_initStruction.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; //���� �� ����
//	USART_Init(USART2, &USART_initStruction);
//	
//	NVIC_USART2_configuration();	//����2�ж����ȼ�����
//	USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);//ʧȥ�ܽ����ж�
//	USART_Cmd(USART2, ENABLE); //ʹ�ܴ���2
//}

///****************************����3******************************/
///****************************����3******************************/

//#if 0
///****************************����4******************************/
///****************************����4******************************/
///* ���ô���4 ���ȼ� ���� */
//static void NVIC_UART4_configuration(void)
//{
//	NVIC_InitTypeDef NVIC_initStruction;
//	
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);				//��
//	NVIC_initStruction.NVIC_IRQChannel = UART4_IRQn;			//����4�ж�
//	NVIC_initStruction.NVIC_IRQChannelPreemptionPriority = 1;   //�����ȼ� 
//	NVIC_initStruction.NVIC_IRQChannelSubPriority = 2;			//�����ȼ�
//	NVIC_initStruction.NVIC_IRQChannelCmd = ENABLE;				//ʹ��
//	
//	NVIC_Init(&NVIC_initStruction);
//}

///* ���ô���4 ����*/
//void uart4_init(uint32_t baudRate)
//{
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	//��GPIOCʱ��
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);	//�򿪴���4ʱ��
//	
//	GPIO_InitTypeDef GPIO_initStruction;
//	USART_InitTypeDef USART_initStruction;

//	/*����GPIOC  TX */
//	GPIO_initStruction.GPIO_Pin = UART4_TX; 		// TX
//	GPIO_initStruction.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
//	GPIO_initStruction.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOC, &GPIO_initStruction);
//	
//	/*����GPIOC RX */
//	GPIO_initStruction.GPIO_Pin = UART4_RX; 		// RX
//	GPIO_initStruction.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
//	GPIO_Init(GPIOC, &GPIO_initStruction);
//	
//	/*����UART4 TX��RX */
//	USART_initStruction.USART_BaudRate = baudRate;	//������
//	USART_initStruction.USART_WordLength = USART_WordLength_8b; //8λ��Ч����λ
//	USART_initStruction.USART_StopBits = USART_StopBits_1;	//1��ֹͣλ
//	USART_initStruction.USART_Parity = USART_Parity_No;		//����żУ��λ
//	USART_initStruction.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //��Ӳ��������
//	USART_initStruction.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; //���� �� ����
//	USART_Init(UART4, &USART_initStruction);
//	
//	NVIC_UART4_configuration();	//����4�ж����ȼ�����
//	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//ʹ�ܽ����ж�
//	USART_Cmd(UART4, ENABLE); //ʹ�ܴ���4
//}


///****************************����5******************************/
///****************************����5******************************/
///* ���ô���5 ���ȼ� ���� */
//static void NVIC_UART5_configuration(void)
//{
//	NVIC_InitTypeDef NVIC_initStruction;
//	
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);				//��
//	NVIC_initStruction.NVIC_IRQChannel = UART5_IRQn;			//����5�ж�
//	NVIC_initStruction.NVIC_IRQChannelPreemptionPriority = 1;   //�����ȼ�  
//	NVIC_initStruction.NVIC_IRQChannelSubPriority = 3;			//�����ȼ�	
//	NVIC_initStruction.NVIC_IRQChannelCmd = ENABLE;				//ʹ��
//	
//	NVIC_Init(&NVIC_initStruction);
//}

///* ���ô���5 ����*/
//void uart5_init(uint32_t baudRate)
//{
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	//��GPIOCʱ��
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	//��GPIODʱ��
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);	//�򿪴���5ʱ��
//	
//	GPIO_InitTypeDef GPIO_initStruction;
//	USART_InitTypeDef USART_initStruction;

//	/*����GPIOC  TX */
//	GPIO_initStruction.GPIO_Pin = UART5_TX; 		// TX
//	GPIO_initStruction.GPIO_Mode = GPIO_Mode_AF_PP; //�����������
//	GPIO_initStruction.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOC, &GPIO_initStruction);
//	
//	/*����GPIOD RX */
//	GPIO_initStruction.GPIO_Pin = UART5_RX; 		// RX
//	GPIO_initStruction.GPIO_Mode = GPIO_Mode_IN_FLOATING; //��������
//	GPIO_Init(GPIOD, &GPIO_initStruction);
//	
//	/*����UART4 TX��RX */
//	USART_initStruction.USART_BaudRate = baudRate;	//������
//	USART_initStruction.USART_WordLength = USART_WordLength_8b; //8λ��Ч����λ
//	USART_initStruction.USART_StopBits = USART_StopBits_1;	//1��ֹͣλ
//	USART_initStruction.USART_Parity = USART_Parity_No;		//����żУ��λ
//	USART_initStruction.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //��Ӳ��������
//	USART_initStruction.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; //���� �� ����
//	USART_Init(UART5, &USART_initStruction);
//	
//	NVIC_UART5_configuration();	//����5�ж����ȼ�����
//	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//ʹ�ܽ����ж�
//	USART_Cmd(UART5, ENABLE); //ʹ�ܴ���5
//}

//#endif


///*���� ����1�ֽ� ����*/
//void usart_sendByte(USART_TypeDef* USARTx,uint8_t data)
//{
//	USART_SendData(USARTx, data);
//	while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET); //�ȴ����ͼĴ���Ϊ�� ֤��������
//}

///*���� �����ַ��� ����*/
//void usart_sendString(USART_TypeDef* USARTx,char *str)
//{
//	while(*str != '\0')
//	{
//		usart_sendByte(USARTx,*str);
//		str++;
//	}
//	while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET); //������ɱ�־λ
//}




///*�ض���C�⺯�� scanf������*/
//int fgetc(FILE *f)
//{
//	while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET); //��������ݼĴ����ǿ�
//	return (int)USART_ReceiveData(USART1);
//}



///*****************************************************************************
//����: ����2 ����1�ֽ� ����
//******************************************************************************/
//void USART2_SendData(u8 data)
//{
//	while((USART2->SR & 0X40) == 0);
//	USART2->DR = data;
//}
///*****************************************************************************
//����: ����2 �����ַ��� ����
//******************************************************************************/
//void USART2_SendString(u8 *DAT, u8 len)
//{
//	u8 i;
//	for(i = 0; i < len; i++)
//	{
//		USART2_SendData(*DAT++);
//	}
//}









