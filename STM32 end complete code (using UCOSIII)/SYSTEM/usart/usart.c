#include "sys.h"
#include "usart.h"	  
////////////////////////////////////////////////////////////////////////////////// 	 
//如果使用os,则包括下面的头文件即可.
#if SYSTEM_SUPPORT_OS
#include "includes.h"					//os 使用	  
#endif

//////////////////////////////////////////////////////////////////
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 

}; 

FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
    USART1->DR = (u8) ch;      
	return ch;
}
#endif 

/*使用microLib的方法*/
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
 
#if EN_USART1_RX   //如果使能了接收
//串口1中断服务程序
//注意,读取USARTx->SR能避免莫名其妙的错误   	
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
//接收状态
//bit15，	接收完成标志
//bit14，	接收到0x0d
//bit13~0，	接收到的有效字节数目
u16 USART_RX_STA=0;       //接收状态标记	  

//初始化IO 串口1 
//bound:波特率
void uart_init(u32 bound){
    //GPIO端口设置
    GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1|RCC_APB2Periph_GPIOA, ENABLE);	//使能USART1，GPIOA时钟
 	USART_DeInit(USART1);  //复位串口1
	 //USART1_TX   PA.9
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9; //PA.9
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化PA9
   
    //USART1_RX	  PA.10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化PA10

   //Usart1 NVIC 配置

    NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
  
   //USART 初始化设置
	USART_InitStructure.USART_BaudRate = bound;//一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;//字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;//一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;//无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	//收发模式

    USART_Init(USART1, &USART_InitStructure); //初始化串口
    USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);//开启中断
    USART_Cmd(USART1, ENABLE);                    //使能串口 

}


#endif	


/****************************串口2******************************/
/****************************串口2******************************/
/* 配置串口2 优先级 函数 */





/****************************串口3******************************/
/****************************串口3******************************/


/****************************串口4******************************/
/****************************串口4******************************/
/* 配置串口4 优先级 函数 */
static void NVIC_UART4_configuration(void)
{
	NVIC_InitTypeDef NVIC_initStruction;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);				//组
	NVIC_initStruction.NVIC_IRQChannel = UART4_IRQn;			//串口4中断
	NVIC_initStruction.NVIC_IRQChannelPreemptionPriority = 1;   //主优先级 
	NVIC_initStruction.NVIC_IRQChannelSubPriority = 2;			//次优先级
	NVIC_initStruction.NVIC_IRQChannelCmd = ENABLE;				//使能
	
	NVIC_Init(&NVIC_initStruction);
}

/* 配置串口4 函数*/
void uart4_init(uint32_t baudRate)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	//打开GPIOC时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);	//打开串口4时钟
	
	GPIO_InitTypeDef GPIO_initStruction;
	USART_InitTypeDef USART_initStruction;

	/*配置GPIOC  TX */
	GPIO_initStruction.GPIO_Pin = UART4_TX; 		// TX
	GPIO_initStruction.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
	GPIO_initStruction.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_initStruction);
	
	/*配置GPIOC RX */
	GPIO_initStruction.GPIO_Pin = UART4_RX; 		// RX
	GPIO_initStruction.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
	GPIO_Init(GPIOC, &GPIO_initStruction);
	
	/*配置UART4 TX和RX */
	USART_initStruction.USART_BaudRate = baudRate;	//波特率
	USART_initStruction.USART_WordLength = USART_WordLength_8b; //8位有效数据位
	USART_initStruction.USART_StopBits = USART_StopBits_1;	//1个停止位
	USART_initStruction.USART_Parity = USART_Parity_No;		//无奇偶校验位
	USART_initStruction.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //不硬件控制流
	USART_initStruction.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; //发送 和 接收
	USART_Init(UART4, &USART_initStruction);
	
	NVIC_UART4_configuration();	//串口4中断优先级配置
	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);//使能接收中断
	USART_Cmd(UART4, ENABLE); //使能串口4
}


/****************************串口5******************************/
/****************************串口5******************************/
/* 配置串口5 优先级 函数 */
static void NVIC_UART5_configuration(void)
{
	NVIC_InitTypeDef NVIC_initStruction;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);				//组
	NVIC_initStruction.NVIC_IRQChannel = UART5_IRQn;			//串口5中断
	NVIC_initStruction.NVIC_IRQChannelPreemptionPriority = 1;   //主优先级  
	NVIC_initStruction.NVIC_IRQChannelSubPriority = 3;			//次优先级	
	NVIC_initStruction.NVIC_IRQChannelCmd = ENABLE;				//使能
	
	NVIC_Init(&NVIC_initStruction);
}

/* 配置串口5 函数*/
void uart5_init(uint32_t baudRate)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	//打开GPIOC时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	//打开GPIOD时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);	//打开串口5时钟
	
	GPIO_InitTypeDef GPIO_initStruction;
	USART_InitTypeDef USART_initStruction;

	/*配置GPIOC  TX */
	GPIO_initStruction.GPIO_Pin = UART5_TX; 		// TX
	GPIO_initStruction.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
	GPIO_initStruction.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_initStruction);
	
	/*配置GPIOD RX */
	GPIO_initStruction.GPIO_Pin = UART5_RX; 		// RX
	GPIO_initStruction.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
	GPIO_Init(GPIOD, &GPIO_initStruction);
	
	/*配置UART4 TX和RX */
	USART_initStruction.USART_BaudRate = baudRate;	//波特率
	USART_initStruction.USART_WordLength = USART_WordLength_8b; //8位有效数据位
	USART_initStruction.USART_StopBits = USART_StopBits_1;	//1个停止位
	USART_initStruction.USART_Parity = USART_Parity_No;		//无奇偶校验位
	USART_initStruction.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //不硬件控制流
	USART_initStruction.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; //发送 和 接收
	USART_Init(UART5, &USART_initStruction);
	
	NVIC_UART5_configuration();	//串口5中断优先级配置
	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);//使能接收中断
	USART_Cmd(UART5, ENABLE); //使能串口5
}



/*串口 发送1字节 函数*/
void usart_sendByte(USART_TypeDef* USARTx,uint8_t data)
{
	USART_SendData(USARTx, data);
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET); //等待发送寄存器为空 证明发送完
}

/*串口 发送字符串 函数*/
void usart_sendString(USART_TypeDef* USARTx,char *str)
{
	while(*str != '\0')
	{
		usart_sendByte(USARTx,*str);
		str++;
	}
	while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET); //发送完成标志位
}


/*****************************************************************************
描述: 串口2 发送1字节 函数
******************************************************************************/
void USART2_SendData(u8 data)
{
	while((USART2->SR & 0X40) == 0);
	USART2->DR = data;
}
/*****************************************************************************
描述: 串口2 发送字符串 函数
******************************************************************************/
void USART2_SendString(u8 *DAT, u8 len)
{
	u8 i;
	for(i = 0; i < len; i++)
	{
		USART2_SendData(*DAT++);
	}
}

