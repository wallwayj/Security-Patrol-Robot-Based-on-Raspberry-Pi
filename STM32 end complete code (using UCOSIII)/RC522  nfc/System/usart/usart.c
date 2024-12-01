//#include "usart.h"
//#include"stdio.h"
//#include "usart.h"	  
//////////////////////////////////////////////////////////////////////////////////// 	 
////如果使用ucos,则包括下面的头文件即可.
//#if SYSTEM_SUPPORT_OS
//#include "includes.h"					//ucos 使用	  
//#endif
//  
//#if 1
//#pragma import(__use_no_semihosting)             
////标准库需要的支持函数                 
//struct __FILE 
//{ 
//	int handle; 

//}; 

//FILE __stdout;       
////定义_sys_exit()以避免使用半主机模式    
//_sys_exit(uint32_t x) 
//{ 
//	x = x; 
//} 
////重定义fputc函数 
//int fputc(uint32_t ch, FILE *f)
//{      
//	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
//    USART1->DR = (u8) ch;      
//	return ch;
//}
//#endif 
///****************************串口1******************************/
///****************************串口1******************************/
///* 配置串口1 优先级 函数 */
//static void NVIC_USART1_configuration(void)
//{
//	NVIC_InitTypeDef NVIC_initStruction;
//	
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);				//组
//	NVIC_initStruction.NVIC_IRQChannel = USART1_IRQn;			//串口1中断
//	NVIC_initStruction.NVIC_IRQChannelPreemptionPriority = 0;   //主优先级
//	NVIC_initStruction.NVIC_IRQChannelSubPriority = 0;			//次优先级
//	NVIC_initStruction.NVIC_IRQChannelCmd = ENABLE;				//使能
//	NVIC_Init(&NVIC_initStruction);
//}

///* 配置串口1 函数*/
//void usart1_init(uint32_t baudRate)
//{	GPIO_InitTypeDef GPIO_initStruction;
//	USART_InitTypeDef USART_initStruction;
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//打开GPIOA时钟
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);	//打开串口1时钟
//	


//	/*配置GPIOA  TX */
//	GPIO_initStruction.GPIO_Pin = USART1_TX; 		// TX
//	GPIO_initStruction.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
//	GPIO_initStruction.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_initStruction);
//	
//	/*配置GPIOA RX */
//	GPIO_initStruction.GPIO_Pin = USART1_RX; 		// RX
//	GPIO_initStruction.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
//	GPIO_Init(GPIOA, &GPIO_initStruction);
//	
//	/*配置USART1 TX和RX */
//	USART_initStruction.USART_BaudRate = baudRate;	//波特率
//	USART_initStruction.USART_WordLength = USART_WordLength_8b; //8位有效数据位
//	USART_initStruction.USART_StopBits = USART_StopBits_1;	//1个停止位
//	USART_initStruction.USART_Parity = USART_Parity_No;		//无奇偶校验位
//	USART_initStruction.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //不硬件控制流
//	USART_initStruction.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; //发送 和 接收
//	USART_Init(USART1, &USART_initStruction);
//	
//	NVIC_USART1_configuration();	//串口1中断优先级配置
//	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//使能接收中断
//	USART_Cmd(USART1, ENABLE); //使能串口1
//}

///****************************串口2******************************/
///****************************串口2******************************/
///* 配置串口2 优先级 函数 */
//static void NVIC_USART2_configuration(void)
//{
//	NVIC_InitTypeDef NVIC_initStruction;
//	
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//组
//	NVIC_initStruction.NVIC_IRQChannel = USART2_IRQn;			//串口2中断
//	NVIC_initStruction.NVIC_IRQChannelPreemptionPriority = 1;   //主优先级  
//	NVIC_initStruction.NVIC_IRQChannelSubPriority = 0;			//次优先级
//	NVIC_initStruction.NVIC_IRQChannelCmd = ENABLE;				//使能	
//	NVIC_Init(&NVIC_initStruction);
//}

///* 配置串口2 函数*/
//void usart2_init(uint32_t baudRate)
//{	GPIO_InitTypeDef GPIO_initStruction;USART_InitTypeDef USART_initStruction;
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//打开GPIOA时钟
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//打开串口2时钟
//	

//	

//	/*配置GPIOA  TX */
//	GPIO_initStruction.GPIO_Pin = USART2_TX; 		// TX
//	GPIO_initStruction.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
//	GPIO_initStruction.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOA, &GPIO_initStruction);
//	
//	/*配置GPIOA RX */
//	GPIO_initStruction.GPIO_Pin = USART2_RX; 		// RX
//	GPIO_initStruction.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
//	GPIO_Init(GPIOA, &GPIO_initStruction);
//	
//	/*配置USART1 TX和RX */
//	USART_initStruction.USART_BaudRate = baudRate;	//波特率
//	USART_initStruction.USART_WordLength = USART_WordLength_8b; //8位有效数据位
//	USART_initStruction.USART_StopBits = USART_StopBits_1;	//1个停止位
//	USART_initStruction.USART_Parity = USART_Parity_No;		//无奇偶校验位
//	USART_initStruction.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //不硬件控制流
//	USART_initStruction.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; //发送 和 接收
//	USART_Init(USART2, &USART_initStruction);
//	
//	NVIC_USART2_configuration();	//串口2中断优先级配置
//	USART_ITConfig(USART2, USART_IT_RXNE, DISABLE);//失去能接收中断
//	USART_Cmd(USART2, ENABLE); //使能串口2
//}

///****************************串口3******************************/
///****************************串口3******************************/

//#if 0
///****************************串口4******************************/
///****************************串口4******************************/
///* 配置串口4 优先级 函数 */
//static void NVIC_UART4_configuration(void)
//{
//	NVIC_InitTypeDef NVIC_initStruction;
//	
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);				//组
//	NVIC_initStruction.NVIC_IRQChannel = UART4_IRQn;			//串口4中断
//	NVIC_initStruction.NVIC_IRQChannelPreemptionPriority = 1;   //主优先级 
//	NVIC_initStruction.NVIC_IRQChannelSubPriority = 2;			//次优先级
//	NVIC_initStruction.NVIC_IRQChannelCmd = ENABLE;				//使能
//	
//	NVIC_Init(&NVIC_initStruction);
//}

///* 配置串口4 函数*/
//void uart4_init(uint32_t baudRate)
//{
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	//打开GPIOC时钟
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);	//打开串口4时钟
//	
//	GPIO_InitTypeDef GPIO_initStruction;
//	USART_InitTypeDef USART_initStruction;

//	/*配置GPIOC  TX */
//	GPIO_initStruction.GPIO_Pin = UART4_TX; 		// TX
//	GPIO_initStruction.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
//	GPIO_initStruction.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOC, &GPIO_initStruction);
//	
//	/*配置GPIOC RX */
//	GPIO_initStruction.GPIO_Pin = UART4_RX; 		// RX
//	GPIO_initStruction.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
//	GPIO_Init(GPIOC, &GPIO_initStruction);
//	
//	/*配置UART4 TX和RX */
//	USART_initStruction.USART_BaudRate = baudRate;	//波特率
//	USART_initStruction.USART_WordLength = USART_WordLength_8b; //8位有效数据位
//	USART_initStruction.USART_StopBits = USART_StopBits_1;	//1个停止位
//	USART_initStruction.USART_Parity = USART_Parity_No;		//无奇偶校验位
//	USART_initStruction.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //不硬件控制流
//	USART_initStruction.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; //发送 和 接收
//	USART_Init(UART4, &USART_initStruction);
//	
//	NVIC_UART4_configuration();	//串口4中断优先级配置
//	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//使能接收中断
//	USART_Cmd(UART4, ENABLE); //使能串口4
//}


///****************************串口5******************************/
///****************************串口5******************************/
///* 配置串口5 优先级 函数 */
//static void NVIC_UART5_configuration(void)
//{
//	NVIC_InitTypeDef NVIC_initStruction;
//	
//	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);				//组
//	NVIC_initStruction.NVIC_IRQChannel = UART5_IRQn;			//串口5中断
//	NVIC_initStruction.NVIC_IRQChannelPreemptionPriority = 1;   //主优先级  
//	NVIC_initStruction.NVIC_IRQChannelSubPriority = 3;			//次优先级	
//	NVIC_initStruction.NVIC_IRQChannelCmd = ENABLE;				//使能
//	
//	NVIC_Init(&NVIC_initStruction);
//}

///* 配置串口5 函数*/
//void uart5_init(uint32_t baudRate)
//{
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	//打开GPIOC时钟
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	//打开GPIOD时钟
//	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);	//打开串口5时钟
//	
//	GPIO_InitTypeDef GPIO_initStruction;
//	USART_InitTypeDef USART_initStruction;

//	/*配置GPIOC  TX */
//	GPIO_initStruction.GPIO_Pin = UART5_TX; 		// TX
//	GPIO_initStruction.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
//	GPIO_initStruction.GPIO_Speed = GPIO_Speed_50MHz;
//	GPIO_Init(GPIOC, &GPIO_initStruction);
//	
//	/*配置GPIOD RX */
//	GPIO_initStruction.GPIO_Pin = UART5_RX; 		// RX
//	GPIO_initStruction.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
//	GPIO_Init(GPIOD, &GPIO_initStruction);
//	
//	/*配置UART4 TX和RX */
//	USART_initStruction.USART_BaudRate = baudRate;	//波特率
//	USART_initStruction.USART_WordLength = USART_WordLength_8b; //8位有效数据位
//	USART_initStruction.USART_StopBits = USART_StopBits_1;	//1个停止位
//	USART_initStruction.USART_Parity = USART_Parity_No;		//无奇偶校验位
//	USART_initStruction.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //不硬件控制流
//	USART_initStruction.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; //发送 和 接收
//	USART_Init(UART5, &USART_initStruction);
//	
//	NVIC_UART5_configuration();	//串口5中断优先级配置
//	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//使能接收中断
//	USART_Cmd(UART5, ENABLE); //使能串口5
//}

//#endif


///*串口 发送1字节 函数*/
//void usart_sendByte(USART_TypeDef* USARTx,uint8_t data)
//{
//	USART_SendData(USARTx, data);
//	while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET); //等待发送寄存器为空 证明发送完
//}

///*串口 发送字符串 函数*/
//void usart_sendString(USART_TypeDef* USARTx,char *str)
//{
//	while(*str != '\0')
//	{
//		usart_sendByte(USARTx,*str);
//		str++;
//	}
//	while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET); //发送完成标志位
//}




///*重定向C库函数 scanf到串口*/
//int fgetc(FILE *f)
//{
//	while(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET); //如果读数据寄存器非空
//	return (int)USART_ReceiveData(USART1);
//}



///*****************************************************************************
//描述: 串口2 发送1字节 函数
//******************************************************************************/
//void USART2_SendData(u8 data)
//{
//	while((USART2->SR & 0X40) == 0);
//	USART2->DR = data;
//}
///*****************************************************************************
//描述: 串口2 发送字符串 函数
//******************************************************************************/
//void USART2_SendString(u8 *DAT, u8 len)
//{
//	u8 i;
//	for(i = 0; i < len; i++)
//	{
//		USART2_SendData(*DAT++);
//	}
//}









