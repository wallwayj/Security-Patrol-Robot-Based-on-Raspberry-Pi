#include "delay.h"
#include "usart3.h"
#include "stdarg.h"	 	 
#include "stdio.h"	 	 
#include "string.h"	 
#include "timer.h"
#include "usart.h"
#define USART3_RXBUF_LEN 15
//串口接收缓存区 	
u8 USART3_RX_BUF[USART3_MAX_RECV_LEN]; 				//接收缓冲,最大USART3_MAX_RECV_LEN个字节.
u8  USART3_TX_BUF[USART3_MAX_SEND_LEN]; 			//发送缓冲,最大USART3_MAX_SEND_LEN字节


u8 USART2_RX_BUF[USART2_MAX_RECV_LEN]; 				//接收缓冲,最大USART2_MAX_RECV_LEN个字节.
u8  USART2_TX_BUF[USART2_MAX_SEND_LEN]; 			//发送缓冲,最大USART2_MAX_SEND_LEN字节
vu16 USART2_RX_STA=0;   	

//蓝牙扫描下：   timer=1S
//非蓝牙扫描下： timer=10ms
//通过判断接收连续2个字符之间的时间差不大于timer来决定是不是一次连续的数据.
//如果2个字符接收间隔超过timer,则认为不是1次连续数据.也就是超过timer没有接收到
//任何数据,则表示此次接收完毕.
//接收到的数据状态
//[15]:0,没有接收到数据;1,接收到了一批数据.
//[14:0]:接收到的数据长度
vu16 USART3_RX_STA=0;   	


void USART3_IRQHandler(void)
{
	u8 res;	      
	if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)//接收到数据
	{	 
		res =USART_ReceiveData(USART3);		 
		if((USART3_RX_STA&(1<<15))==0)//接收完的一批数据,还没有被处理,则不再接收其他数据
		{ 
			if(USART3_RX_STA<USART3_MAX_RECV_LEN)	//还可以接收数据
			{
				TIM_SetCounter(TIM7,0);             //计数器清空          				
				if(USART3_RX_STA==0) 				//使能定时器7的中断 
				{
					TIM_Cmd(TIM7,ENABLE);           //使能定时器7
				}
				USART3_RX_BUF[USART3_RX_STA++]=res;	//记录接收到的值	 
			}else 
			{
				USART3_RX_STA|=1<<15;				//强制标记接收完成
			} 
		}
	}  				 											 
}   


//初始化IO 串口3
//pclk1:PCLK1时钟频率(Mhz)
//bound:波特率	  
void usart3_init(u32 bound)
{  

	NVIC_InitTypeDef NVIC_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	                       //GPIOB时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);                          //串口3时钟使能

 	USART_DeInit(USART3);  //复位串口3
		 //USART3_TX   PB10
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;                                     //PB10
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	                               //复用推挽输出
    GPIO_Init(GPIOB, &GPIO_InitStructure);                                         //初始化PB10
   
    //USART3_RX	  PB11
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;                          //浮空输入
    GPIO_Init(GPIOB, &GPIO_InitStructure);                                         //初始化PB11
	
	USART_InitStructure.USART_BaudRate = bound;                                    //波特率一般设置为9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;                    //字长为8位数据格式
	USART_InitStructure.USART_StopBits = USART_StopBits_1;                         //一个停止位
	USART_InitStructure.USART_Parity = USART_Parity_No;                            //无奇偶校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;//无硬件数据流控制
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;	               //收发模式
  
	USART_Init(USART3, &USART_InitStructure);       //初始化串口3
  

	USART_Cmd(USART3, ENABLE);                      //使能串口 
	
	//使能接收中断
    USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);  //开启中断   
	
	//设置中断优先级
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
	
	
	TIM7_Int_Init(99,7199);		//10ms中断
	USART3_RX_STA=0;		    //清零
	TIM_Cmd(TIM7,DISABLE);		//关闭定时器7

}

//串口3,printf 函数
//确保一次发送数据不超过USART3_MAX_SEND_LEN字节
void u3_printf(char* fmt,...)  
{  
	u16 i,j; 
	va_list ap; 
	va_start(ap,fmt);
	vsprintf((char*)USART3_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART3_TX_BUF);		//此次发送数据的长度
	for(j=0;j<i;j++)							//循环发送数据
	{
	  while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET); //循环发送,直到发送完毕   
		USART_SendData(USART3,USART3_TX_BUF[j]); 
	} 
}

 


static void NVIC_USART2_configuration(void)
{
	NVIC_InitTypeDef NVIC_initStruction;
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//组
	NVIC_initStruction.NVIC_IRQChannel = USART2_IRQn;			//串口2中断
	NVIC_initStruction.NVIC_IRQChannelPreemptionPriority = 1;   //主优先级  
	NVIC_initStruction.NVIC_IRQChannelSubPriority = 0;			//次优先级
	NVIC_initStruction.NVIC_IRQChannelCmd = ENABLE;				//使能	
	NVIC_Init(&NVIC_initStruction);
}

/* 配置串口2 函数*/
void usart2_init(uint32_t baudRate)
{	GPIO_InitTypeDef GPIO_initStruction;USART_InitTypeDef USART_initStruction;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	//打开GPIOA时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);	//打开串口2时钟

	/*配置GPIOA  TX */
	GPIO_initStruction.GPIO_Pin = USART2_TX; 		// TX
	GPIO_initStruction.GPIO_Mode = GPIO_Mode_AF_PP; //复用推挽输出
	GPIO_initStruction.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_initStruction);
	
	/*配置GPIOA RX */
	GPIO_initStruction.GPIO_Pin = USART2_RX; 		// RX
	GPIO_initStruction.GPIO_Mode = GPIO_Mode_IN_FLOATING; //浮空输入
	GPIO_Init(GPIOA, &GPIO_initStruction);
	
	/*配置USART1 TX和RX */
	USART_initStruction.USART_BaudRate = baudRate;	//波特率
	USART_initStruction.USART_WordLength = USART_WordLength_8b; //8位有效数据位
	USART_initStruction.USART_StopBits = USART_StopBits_1;	//1个停止位
	USART_initStruction.USART_Parity = USART_Parity_No;		//无奇偶校验位
	USART_initStruction.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //不硬件控制流
	USART_initStruction.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; //发送 和 接收
	USART_Init(USART2, &USART_initStruction);
	
	NVIC_USART2_configuration();	//串口2中断优先级配置
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//
	USART_Cmd(USART2, ENABLE); //使能串口2
	
		
	TIM4_Int_Init(1000-1,7200-1);		//10ms中断
	USART2_RX_STA=0;		    //清零
	TIM_Cmd(TIM4,DISABLE);		//关闭定时器7
}

void USART2_IRQHandler(void)
{
	u8 res;	      
	if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)//接收到数据
	{	 
		res =USART_ReceiveData(USART2);		 
		if((USART2_RX_STA&(1<<15))==0)//接收完的一批数据,还没有被处理,则不再接收其他数据
		{ 
			if(USART2_RX_STA<USART2_MAX_RECV_LEN)	//还可以接收数据
			{
				TIM_SetCounter(TIM4,0);             //计数器清空          				
				if(USART2_RX_STA==0) 				//使能定时器7的中断 
				{
					TIM_Cmd(TIM4,ENABLE);           //使能定时器7
				}
				USART2_RX_BUF[USART2_RX_STA++]=res;	//记录接收到的值	 
			}else 
			{
				USART2_RX_STA|=1<<15;				//强制标记接收完成
			} 
		}
	}  				 											 
}   
void Uart2_SendStr(u8* SendBuf,u8 len)
{
	int t;
//	len=SendBuf&0x3fff;//得到此次接收到的数据长度
	for(t=0;t<len;t++)
	{
		USART_SendData(USART2, SendBuf[t]);//向串口1发送数据
		while(USART_GetFlagStatus(USART2,USART_FLAG_TC)!=SET);//等待发送结束
	}
	printf("\r\n\r\n");//插入换行
}
//串口2,printf 函数
//确保一次发送数据不超过USART2_MAX_SEND_LEN字节
void u2_printf(char* fmt,...)  
{  
	u16 i,j; 
	va_list ap; 
	va_start(ap,fmt);
	vsprintf((char*)USART2_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART2_TX_BUF);		//此次发送数据的长度
	for(j=0;j<i;j++)							//循环发送数据
	{
	  while(USART_GetFlagStatus(USART2,USART_FLAG_TC)==RESET); //循环发送,直到发送完毕   
		USART_SendData(USART2,USART2_TX_BUF[j]); 
	} 
	memset(USART2_TX_BUF, 0, USART2_MAX_SEND_LEN); 
}


















