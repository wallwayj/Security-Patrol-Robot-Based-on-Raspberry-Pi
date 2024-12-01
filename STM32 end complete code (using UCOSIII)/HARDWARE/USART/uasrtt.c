#include"sys.h"
c
 
void usart4_init(u32 btl)
{

	GPIO_InitTypeDef GPIO_InitStructure;

	USART_InitTypeDef USART_InitStructure;

	NVIC_InitTypeDef NVIC_InitStructure;        

	 

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE );

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE );

	 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10; //UART4 TX；

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出；

	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_Init(GPIOC, &GPIO_InitStructure); //端口C；

			

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11; //UART4 RX；

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入；

	GPIO_Init(GPIOC, &GPIO_InitStructure); //端口C；

	 

	USART_InitStructure.USART_BaudRate = btl; //波特率；

	USART_InitStructure.USART_WordLength = USART_WordLength_8b; //数据位8位；

	USART_InitStructure.USART_StopBits = USART_StopBits_1; //停止位1位；

	USART_InitStructure.USART_Parity = USART_Parity_No ; //无校验位；

	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

	//无硬件流控；

	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	//收发模式；

	USART_Init(UART4, &USART_InitStructure);//配置串口参数；

	 

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置中断组，4位抢占优先级，4位响应优先级；

	 

	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn; //中断号；

	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //抢占优先级；

	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //响应优先级；

	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&NVIC_InitStructure);

	 

	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);

	USART_Cmd(UART4, ENABLE); //使能串口；

}

 

void UART4_Send_Byte(u8 Data) //发送一个字节；

{

	USART_SendData(UART4,Data);

	while( USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET );

}

 

void UART4_Send_String(u8 *Data) //发送字符串；

{

	while(*Data)

	UART4_Send_Byte(*Data++);

}

 

//void UART4_IRQHandler(void) //中断处理函数；

//{

//u8 res;    

//if(USART_GetITStatus(UART4, USART_IT_RXNE) == SET) //判断是否发生中断；

//{

//USART_ClearFlag(UART4, USART_IT_RXNE); //清除标志位；

//res=USART_ReceiveData(UART4); //接收数据；

//UART4_Send_Byte(res); //用户自定义；

//}  

//} 
 





void usart5_init(u32 btl)

{

GPIO_InitTypeDef GPIO_InitStructure;

USART_InitTypeDef USART_InitStructure;

NVIC_InitTypeDef NVIC_InitStructure;        

 

RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_GPIOD, ENABLE );

RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE );

 

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12; //UART5 TX；

GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出；

GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

GPIO_Init(GPIOC, &GPIO_InitStructure); //端口C；

    

GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //UART4 RX；

GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入；

GPIO_Init(GPIOD, &GPIO_InitStructure); //端口D；

 

USART_InitStructure.USART_BaudRate = btl; //波特率；

USART_InitStructure.USART_WordLength = USART_WordLength_8b; //数据位8位；

USART_InitStructure.USART_StopBits = USART_StopBits_1; //停止位1位；

USART_InitStructure.USART_Parity = USART_Parity_No ; //无校验位；

USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;

//无硬件流控；

USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

//收发模式；

USART_Init(UART5, &USART_InitStructure);//配置串口参数；

 

NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //设置中断组，4位抢占优先级，4位响应优先级；

 

NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn; //中断号；

NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0; //抢占优先级；

NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; //响应优先级；

NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;

NVIC_Init(&NVIC_InitStructure);

 

USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);

USART_Cmd(UART5, ENABLE); //使能串口；

}

 

void UART5_Send_Byte(u8 Data) //发送一个字节；

{

USART_SendData(UART5,Data);

while( USART_GetFlagStatus(UART5, USART_FLAG_TC) == RESET );

}

 

void UART5_Send_String(u8 *Data) //发送字符串；

{

while(*Data)

UART5_Send_Byte(*Data++);

}

 

//void UART5_IRQHandler(void) //中断处理函数；

//{

//u8 res;    

//if(USART_GetITStatus(UART5, USART_IT_RXNE) == SET) //判断是否发生中断；

//{

//USART_ClearFlag(UART5, USART_IT_RXNE); //清除标志位；

//res=USART_ReceiveData(UART5); //接收数据；

//UART5_Send_Byte(res); //用户自定义；

//}  

//} 



