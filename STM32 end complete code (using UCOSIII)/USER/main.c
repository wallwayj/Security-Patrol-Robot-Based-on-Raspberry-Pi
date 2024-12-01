#include"headfile.h"
uint8_t cardnumber,KeyNum,tempcard,select=0,flag_scan=1,flag_addcard=0,flag_deletecard=0;
u8 flag_nfc_task=1,flag_fire=0,charge=0;
u16 time_sum=0,cardid;
u8 co2_str[5], tvoc_str[5], lux_str[10], fire_str[2], alt_str[5], temper_str[10], humi_str[10], atmos_str[12], people_str[2];
int co2,tvoc=0,fire=0,alt,people =0;
float lux ,temper,humi ,atmos;
//任务优先级
#define START_TASK_PRIO		3
//任务堆栈大小	
#define START_STK_SIZE 		128
//任务控制块
OS_TCB StartTaskTCB;
//任务堆栈	
CPU_STK START_TASK_STK[START_STK_SIZE];
//任务函数
void start_task(void *p_arg);

//任务优先级
#define nfc_TASK_PRIO		5
//任务堆栈大小	
#define nfc_STK_SIZE 		128
//任务控制块
OS_TCB nfc_TaskTCB;
//任务堆栈	
CPU_STK nfc_TASK_STK[nfc_STK_SIZE];
void nfc_task(void *p_arg);

//任务优先级
#define k210_TASK_PRIO		7
//任务堆栈大小	
#define k210_STK_SIZE 		128
//任务控制块
OS_TCB k210_TaskTCB;
//任务堆栈	
CPU_STK k210_TASK_STK[k210_STK_SIZE];
void k210_task(void *p_arg);

//任务优先级
#define alarm_TASK_PRIO		7
//任务堆栈大小	
#define alarm_STK_SIZE 		128
//任务控制块
OS_TCB alarm_TaskTCB;
//任务堆栈	
CPU_STK alarm_TASK_STK[alarm_STK_SIZE];
void alarm_task(void *p_arg);

 //任务优先级
#define net_TASK_PRIO		2
//任务堆栈大小	
#define net_STK_SIZE 		1024
//任务控制块
OS_TCB net_TaskTCB;
//任务堆栈	
CPU_STK net_TASK_STK[net_STK_SIZE];
void net_task(void *p_arg);

//任务优先级
#define rtc_TASK_PRIO		5
//任务堆栈大小	
#define rtc_STK_SIZE 		128
//任务控制块
OS_TCB rtc_TaskTCB;
//任务堆栈	
CPU_STK rtc_TASK_STK[rtc_STK_SIZE];
void rtc_task(void *p_arg);

////////////////////////////////////////////////////////
OS_TMR 	tmr1;		//定时器1
void tmr1_callback(void *p_tmr, void *p_arg); 	//定时器1回调函数

OS_SEM tsem1;

#define kmsgnum 1//消息队列数量
OS_Q kmsg;//消息队列

#define redmsgnum 1//消息队列数量
OS_Q redmsg;//消息队列

#define u2msgnum 3//消息队列数量
OS_Q u2msg;//消息队列
//LCD刷屏时使用的颜色
int lcd_discolor[14]={	WHITE, RED,   BLUE,  BRED,      
						GRED,  GBLUE, BLACK,   MAGENTA,       	 
						GREEN, CYAN,  YELLOW,BROWN, 			
						BRRED, GRAY };
 
//主函数
int main(void)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	delay_init();  //时钟初始化
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//中断分组配置
	usmart_dev.init(SystemCoreClock/1000000);	//初始化USMART
	uart_init(115200);   //串口初始化
	usart2_init(115200);
	usart3_init(115200);
	uart4_init(115200);
	printf("KKK");
	esp8266_start_trans();//wifi模块初始化
	printf("END");
	Servo_Init();//舵机初始化
	RTC_Init();//时钟模块初始化
	RTC_Set(2024,5,14,12,0,0);//
	beep_init();//蜂鸣器初始化

	OSInit(&err);		    	//初始化UCOSIII
	OS_CRITICAL_ENTER();	//进入临界区			 
	//创建开始任务
	OSTaskCreate((OS_TCB 	* )&StartTaskTCB,		//任务控制块
				 (CPU_CHAR	* )"start task", 		//任务名字
                 (OS_TASK_PTR )start_task, 			//任务函数
                 (void		* )0,					//传递给任务函数的参数
                 (OS_PRIO	  )START_TASK_PRIO,     //任务优先级
                 (CPU_STK   * )&START_TASK_STK[0],	//任务堆栈基地址
                 (CPU_STK_SIZE)START_STK_SIZE/10,	//任务堆栈深度限位
                 (CPU_STK_SIZE)START_STK_SIZE,		//任务堆栈大小
                 (OS_MSG_QTY  )0,					//任务内部消息队列能够接收的最大消息数目,为0时禁止接收消息
                 (OS_TICK	  )0,					//当使能时间片轮转时的时间片长度，为0时为默认长度，
                 (void   	* )0,					//用户补充的存储区
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR, //任务选项
                 (OS_ERR 	* )&err);				//存放该函数错误时的返回值
	OS_CRITICAL_EXIT();	//退出临界区	 
	OSStart(&err);      //开启UCOSIII
}

//开始任务函数
void start_task(void *p_arg)
{
	OS_ERR err;
	CPU_SR_ALLOC();
	p_arg = p_arg;
	
	CPU_Init();
#if OS_CFG_STAT_TASK_EN > 0u
   OSStatTaskCPUUsageInit(&err);  	//统计任务                
#endif
	
#ifdef CPU_CFG_INT_DIS_MEAS_EN		//如果使能了测量中断关闭时间
    CPU_IntDisMeasMaxCurReset();	
#endif
	
#if	OS_CFG_SCHED_ROUND_ROBIN_EN  //当使用时间片轮转的时候
	 //使能时间片轮转调度功能,时间片长度为1个系统时钟节拍，既1*5=5ms
	OSSchedRoundRobinCfg(DEF_ENABLED,1,&err);  
#endif	
OS_CRITICAL_ENTER();	//进入临界区	
	//创建定时器1
	OSTmrCreate((OS_TMR		*)&tmr1,		//定时器1
                (CPU_CHAR	*)"tmr1",		//定时器名字
                (OS_TICK	 )5,			//20*10=200ms
                (OS_TICK	 )50,          //100*10=1000ms
                (OS_OPT		 )OS_OPT_TMR_PERIODIC, //周期模式
                (OS_TMR_CALLBACK_PTR)tmr1_callback,//定时器1回调函数
                (void	    *)0,			//参数为0
                (OS_ERR	    *)&err);		//返回的错误码	
								
//创建NFC任务
	OSTaskCreate((OS_TCB 	* )&nfc_TaskTCB,		
				 (CPU_CHAR	* )"nfc task", 		
                 (OS_TASK_PTR )nfc_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )nfc_TASK_PRIO,     
                 (CPU_STK   * )&nfc_TASK_STK[0],	
                 (CPU_STK_SIZE)nfc_STK_SIZE/10,	
                 (CPU_STK_SIZE)nfc_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);		
 
	////创建rtc任务
	OSTaskCreate((OS_TCB 	* )&rtc_TaskTCB,		
				 (CPU_CHAR	* )"rtc task", 		
                 (OS_TASK_PTR )rtc_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )rtc_TASK_PRIO,     
                 (CPU_STK   * )&rtc_TASK_STK[0],	
                 (CPU_STK_SIZE)rtc_STK_SIZE/10,	
                 (CPU_STK_SIZE)rtc_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);			printf("RTC\r\n");	
								 
//创建net任务
	OSTaskCreate((OS_TCB 	* )&net_TaskTCB,		
				 (CPU_CHAR	* )"net task", 		
                 (OS_TASK_PTR )net_task, 			
                 (void		* )0,					
                 (OS_PRIO	  )net_TASK_PRIO,     
                 (CPU_STK   * )&net_TASK_STK[0],	
                 (CPU_STK_SIZE)net_STK_SIZE/10,	
                 (CPU_STK_SIZE)net_STK_SIZE,		
                 (OS_MSG_QTY  )0,					
                 (OS_TICK	  )0,  					
                 (void   	* )0,					
                 (OS_OPT      )OS_OPT_TASK_STK_CHK|OS_OPT_TASK_STK_CLR,
                 (OS_ERR 	* )&err);		
								 printf("	net");	 
								 
	OS_CRITICAL_EXIT();	//退出临界区
	OSTmrStart(&tmr1,&err);
	OSTaskDel((OS_TCB*)0,&err);	//删除start_task任务自身
}
u8 who=2;
////任务net的任务函数
void net_task(void *p_arg)
{
	printf("netSTART\r\n");
	OS_ERR err;
	u32 old_time_fire=RTC_GetCounter()/60;	 
	u32 old_time_gas=old_time_fire;
	u32 old_time_people=old_time_fire;
	
	printf("nnneeeetttt\r\n");
	while(1)
	{ 
		OSTimeDlyHMSM(0,0,0,500,OS_OPT_TIME_PERIODIC,&err);   //延时		
		printf("who=%d",who);
//		if(people!=0&&RTC_GetCounter()/60-old_time_people>5)
//			send_alarm(1);
 
		switch(who)//数据分批传云
		{
			case 2:
				who++;
				numToString(co2);	
				esp8266_str_data("co2", strValue);
			break;
//////			case 1:	
//////				numToString(tvoc);	
//////				esp8266_str_data("tvoc", strValue);		
//////				if(tvoc>=400&&RTC_GetCounter()/60-old_time_gas>5)
//////					send_alarm(3);
//////				who++;
//////			break;
//////			case 2:
//////				numToString(fire);	
//////				if(fire!=0>5&&RTC_GetCounter()/60-old_time_fire>5)
//////					send_alarm(2);
//////				esp8266_str_data("fire", strValue);		
//////				who++;
//////			break;
			case 3:
				numToString(alt);	
				esp8266_str_data("alt", strValue);	
				who++;			
			break;
			case 4:
				numToString(temper);	
				esp8266_str_data("temp", strValue);		
				who++;
			break;
			case 5:
				numToString(humi);	
				esp8266_str_data("humi", strValue);		
				who++;
			break;
			case 6:
				numToString(atmos);	
				esp8266_str_data("atmos", strValue);	
				who++;			
			break;
			case 7:
				numToString(lux);	
				esp8266_str_data("lux", strValue);	
				who=2;			
			break;
		}
	}
}
////任务nfc的任务函数
void nfc_task(void *p_arg)
{
	printf("NFCSTART\r\n");
//	OS_ERR err;
	u8 KeyNum=0;
	KEY_Init();//按键初始化
	RFID_Init(); //RC522初始化
//	Read_Card();//读写入卡
u8 kk=0,k=0,kkk=0;
	while(1)
	{
		
		if(people!=0&&k==0)//&&RTC_GetCounter()/60-old_time_people>5
		{
			send_alarm(1);k=1;
		}
		if(fire!=0&&kk==0)//&&RTC_GetCounter()/60-old_time_fire>5
		{
			send_alarm(2);kk=1;
		}
		if(tvoc>=400&&kkk==0)//&&RTC_GetCounter()/60-old_time_gas>5
		{
			send_alarm(3);kkk=1;
		}
		KeyNum=KEY_Scan(0);	
		if(KeyNum==1)	//按下1键进入寻卡模式，上电初始化为寻卡模式
		{printf("findcard\r\n");
			flag_scan=1;
			flag_addcard=0;
			flag_deletecard=0;
		}
		else if(KeyNum==2)	//按下2键进入写卡模式
		{
			flag_scan=0;
			flag_addcard=1;
			flag_deletecard=0;
			printf("weitecard\r\n");
		}
		else if(KeyNum==3)	//按下3键进入删卡模式
		{
			flag_scan=0;
			flag_addcard=0;
			flag_deletecard=1;
		}	
		if(flag_scan==1)//寻卡模式
		{		
			
			cardnumber = Rc522Test();	//获取卡编号
			if(cardnumber == 0)			//如果为0，表示“卡片错误”，系统中没有这张卡
			{
				int i_id;cardid=0;
				for(i_id=0;i_id<4;i_id++)
					cardid=cardid*10+UID[i_id];
				POINT_COLOR=RED;
				Buzzer2();
				WaitCardOff();		//等待卡片移开
			}
			else if(cardnumber==1||cardnumber==2||cardnumber==3||cardnumber == 4)			//如果卡编号为1-4，说明是系统中的4张卡
			{	
				int i_id;cardid=0;
				for(i_id=0;i_id<4;i_id++)
					cardid=cardid*10+UID[i_id];
				charge=1;
				Buzzer1();
				printf("cardnumber=%d\r\n",cardnumber);
				WaitCardOff();		//等待卡片移开

			}	
			
		}
		while(flag_addcard==1)	//写卡模式
		{
			KeyNum = KEY_Scan(0);
			
			if(KeyNum==1)		//写卡模式中按下1键进入寻卡模式
			{
				flag_scan=1;
				flag_addcard=0;
				flag_deletecard=0;
			}
			if(KeyNum==3)		//写卡模式中按下3键进入删卡模式
			{
				flag_scan=0;
				flag_addcard=0;
				flag_deletecard=1;
			}
			if (PcdRequest(REQ_ALL, Temp) == MI_OK)
			{
				if (PcdAnticoll(UID) == MI_OK)
				{
					if(UI0[0] == 0xFF && UI0[1] == 0xFF && UI0[2] == 0xFF && UI0[3] == 0xFF) tempcard = 0;	//判断系统各卡数据区是否为空，为空才能写入新卡
					else if(UI1[0] == 0xFF && UI1[1] == 0xFF && UI1[2] == 0xFF && UI1[3] == 0xFF) tempcard = 1;
					else if(UI2[0] == 0xFF && UI2[1] == 0xFF && UI2[2] == 0xFF && UI2[3] == 0xFF) tempcard = 2;
					else if(UI3[0] == 0xFF && UI3[1] == 0xFF && UI3[2] == 0xFF && UI3[3] == 0xFF) tempcard = 3;
					else tempcard = 4;
					
					if(UID[0]==UI0[0] && UID[1]==UI0[1] && UID[2]==UI0[2] && UID[3]==UI0[3])	//判断新卡是否已经录入
					{
						tempcard = 5;
					}
					if(UID[0]==UI1[0] && UID[1]==UI1[1] && UID[2]==UI1[2] && UID[3]==UI1[3])
					{
						tempcard = 5;
					}
					if(UID[0]==UI2[0] && UID[1]==UI2[1] && UID[2]==UI2[2] && UID[3]==UI2[3])
					{
						tempcard = 5;
					}
					if(UID[0]==UI3[0] && UID[1]==UI3[1] && UID[2]==UI3[2] && UID[3]==UI3[3])
					{
						tempcard = 5;
					}
					
					switch(tempcard)
					{
						case 0:
						{
							UI0[0] = UID[0];	//将新卡数据写入UI0[]数组
							UI0[1] = UID[1];
							UI0[2] = UID[2];
							UI0[3] = UID[3];
							printf("Add Card 1 OK\r\n");
							
							Buzzer1();
							WaitCardOff();	//等待卡片移走
						}break;
						case 1:
						{
							UI1[0] = UID[0];
							UI1[1] = UID[1];
							UI1[2] = UID[2];
							UI1[3] = UID[3];
							
							Buzzer1();
							WaitCardOff();
						}break;
						case 2:
						{
							UI2[0] = UID[0];
							UI2[1] = UID[1];
							UI2[2] = UID[2];
							UI2[3] = UID[3];
							 
							Buzzer1();
							WaitCardOff();
						}break;
						case 3:
						{
							UI3[0] = UID[0];
							UI3[1] = UID[1];
							UI3[2] = UID[2];
							UI3[3] = UID[3];
							 printf("Add Card 1 OK\r\n");
							Buzzer1();
							WaitCardOff();
						}break;
						case 4:
						{	
							Buzzer_Alarm();
							WaitCardOff();
						}
						case 5:
						{	
							Buzzer_Alarm();
							WaitCardOff();
						}
						default:break;
					 }
				}
			}
		}
		
		while(flag_deletecard==1)	//删卡模式
		{
			KeyNum = KEY_Scan(0);
			if(KeyNum==4)	//按下4键退出删卡模式，进入寻卡模式
			{
				flag_scan=1;
				flag_addcard=0;
				flag_deletecard=0;
			}
			if(KeyNum==1)	//在删卡模式下按下1键，选择要删除的卡片，卡片序列增加
			{
				select++;
				if(select>=4 || select<1)select=0;
			}
			if(KeyNum==2)	//在删卡模式下按下2键，选择要删除的卡片，卡片序列减少
			{
				select--;
				if(select>=4 || select<1)select=0;
			}
			switch (select)
			{
				case 0:
				{
					if(KeyNum==3)	//在删卡模式下按下3键，删除对应的卡片
					{
						FLASH_Clear(FLASH_ADDR1);	
						UI0[0]=0xFF;
						UI0[1]=0xFF;
						UI0[2]=0xFF;
						UI0[3]=0xFF;
						Buzzer1();	//删除成功后蜂鸣器响一声
						delay_ms(1500);
					}
				}break;
				case 1:
				{
					if(KeyNum==3)
					{
						FLASH_Clear(FLASH_ADDR2);
						UI1[0]=0xFF;
						UI1[1]=0xFF;
						UI1[2]=0xFF;
						UI1[3]=0xFF;
						Buzzer1();
						delay_ms(1500);
					}
				}break;
				case 2:
				{
					if(KeyNum==3)
					{
						FLASH_Clear(FLASH_ADDR3);
						UI2[0]=0xFF;
						UI2[1]=0xFF;
						UI2[2]=0xFF;
						UI2[3]=0xFF;
						Buzzer1();
						delay_ms(1500);;
					}
				}break;
				case 3:
				{
					if(KeyNum==3)
					{
						FLASH_Clear(FLASH_ADDR4);
						UI3[0]=0xFF;
						UI3[1]=0xFF;
						UI3[2]=0xFF;
						UI3[3]=0xFF;
						Buzzer1();
						delay_ms(1500);
					}
				}break;
				default:break;
			}
		}
 
	}

}



float iii=0;
void ui_load()
{
	LCD_Fill(0,160,250,180+190,WHITE);
		LCD_ShowString(0,40,200,16,16,"CO2:");	
		LCD_ShowString(120,40,200,16,16,"ALT:");	
		LCD_ShowString(0,60,200,16,16,"TVOC:");	
		LCD_ShowString(120,60,200,16,16,"TEMP:");	
		LCD_ShowString(0,80,200,16,16,"LUX:");	
		LCD_ShowString(120,80,200,16,16,"HUMI:");	
		LCD_ShowString(0,100,200,16,16,"FIRE:");	
		LCD_ShowString(120,100,200,16,16,"ATMOS:");		
		
}
void Emergency_mode()
{
 u8 keye;
	LCD_Fill(0,160,250,180+190,YELLOW);sim800c_load_keyboard0(0,180);
	while(1)
	{
		keye=sim800c_get_keynum0(0,180);
		if(keye==1)u3_printf("ATD%s;\r\n","15570052607");//拨号
		else if(keye==2)
		{		 
			send_alarm(0);
		}
		else if(keye==3)
		break;

	}
}
//任务rtc的任务函数
void rtc_task(void *p_arg)
{
	printf("rtcSTART\r\n");
//	OS_ERR err; 
	printf("	O\r\n");
	u8 key;float angle=90;
	u8 buf1[11],buf2[11] ;  // 
	LCD_Init();			   		//初始化LCD     
	tp_dev.init();				//初始化触摸屏
	co2=965;tvoc=323;lux=384.8;fire=0;alt=1870;temper=24.18;humi=43.82;atmos=82575.36;
ui_load();
 
	Servo_Init();Servo_SetAngle(angle);
	while(1)
	{
		//delay_ms(10);LCD_ShowxNum(216,4-0,atmos,8,16,1);LCD_ShowNum(80,100,fire,8,16);LCD_ShowxNum(216,40,humi,8,16,1);LCD_ShowxNum(80,80,lux,8,16,1);LCD_ShowNum(40,40,co2,8,16);LCD_ShowNum(216,40,alt,8,16);LCD_ShowNum(80,60,tvoc,8,16);LCD_ShowxNum(216,40,temper,8,16,1);
		sprintf((char*)buf1, "%04d-%02d-%02d",calendar.w_year,calendar.w_month,calendar.w_date); 
		sprintf((char*)buf2,	" %02d:%02d:%02d",calendar.hour,calendar.min,calendar.sec);
		POINT_COLOR=BLUE;
		LCD_ShowString(0,0,200,16,16,buf1);	
		LCD_ShowString(120,0,200,16,16,buf2);		

		LCD_ShowString(40,40,200,16,16,co2_str);	LCD_ShowString(160,40,200,16,16,alt_str);	
		LCD_ShowString(40,60,200,16,16,tvoc_str);	LCD_ShowString(160,60,200,16,16,temper_str);	
		LCD_ShowString(40,80,200,16,16,lux_str);	LCD_ShowString(160,80,200,16,16,humi_str);	
		LCD_ShowString(40,100,200,16,16,fire_str);	LCD_ShowString(170,100,200,16,16,atmos_str);	
	Servo_Init();Servo_SetAngle(angle);
		Servo_SetAngle(angle);		
		angle++;
		if(angle==270)angle=0;
//		sim800c_test(); 	
		sim800c_load_keyboard0(0,180);
		key=sim800c_get_keynum0(0,180);
		if(key)
			{printf("key=%d\r\n",key);
			switch(key)
			{
				case 1:
					sim800c_call_test();//拨号测试
					ui_load();
					break;
				case 2:
					sim800c_sms_send_test();	//短信测试
					ui_load();break;
				case 3:
					Emergency_mode();
					ui_load();break;	
				case 4:
					if(angle==90)
						angle=0;
					else angle=90;
					printf("angle=%.2f\r\n",angle);
					Servo_SetAngle(angle);
					break;
			}
		} 
		
	}
}
 
u8 angle=0,flag_angle=0;
//定时器1的回调函数
void tmr1_callback(void *p_tmr, void *p_arg)
{
////	u8 KeyNum;
////			KeyNum=KEY_Scan(0);	
////		if(KeyNum==3)printf("KeyNum=%d\r\n",KeyNum);
////	printf("co=%d,tvoc=%d,lux=%.2f,fire=%d,alt=%d,temp=%.2f,humi=%.2f,atom=%.2f\r\n",
////		co2, tvoc ,lux ,fire ,alt , temper , humi , atmos);
////	Servo_SetAngle(angle);
////	printf("angle=%d\r\n",angle);
////	if(angle==180)flag_angle=1;
////	else if(angle==0)flag_angle=0;
////	if(flag_angle==0)angle++;
////	else angle--;
}

//void USART1_IRQHandler(void)                	//串口1中断服务程序
//{
//	u8 Res;
//	if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)  //接收中断(接收到的数据必须是0x0d 0x0a结尾)
//	{
//		Res =USART_ReceiveData(USART1);	//读取接收到的数据
//		if(Res==0x01)
//			iii+=10;
//		else iii-=10;
//		PWM_SetCompare2(iii);
//		printf("iii=%.2f\r\n",iii);
//	}
//}
//	


#define MAX_BUFFER_SIZE 1024 // 增加接收缓冲区的大小为512字节
char rx_buffer[MAX_BUFFER_SIZE];
volatile uint16_t rx_index = 0; // 使用 uint16_t 类型来保证索引值不溢出

void UART4_IRQHandler(void) //无线数据接收
{
    if(USART_GetITStatus(UART4, USART_IT_RXNE) == SET) //判断是否发生中断；
    {
        USART_ClearFlag(UART4, USART_IT_RXNE); //清除标志位；
				//printf("4");
        char received_data = USART_ReceiveData(UART4);
				if(rx_index==0&&received_data!='C')
					return ;
        rx_buffer[rx_index++] = received_data;

				if (rx_index >= MAX_BUFFER_SIZE)
				{
					rx_index = 0; // 如果索引超过了缓冲区的大小，重置索引
					return;
        }				
				else 	if(rx_index>54&&received_data=='\n')
				{
//					printf("suc");
					if (sscanf(rx_buffer, "CO2:%[^;];TVOC:%[^;];LUX:%[^;];FIRE:%[^;];ALT:%[^;];TEMPER:%[^;];HUMI:%[^;];ATMOS:%[^;];peo:%[^;];\n",
           co2_str, tvoc_str, lux_str, fire_str, alt_str, temper_str, humi_str, atmos_str,people_str) == 9) 
					{
//						printf("good");
//						LED1=~LED1;
						co2 = atoi((const char *)co2_str);
						tvoc = atoi((const char *)tvoc_str);
						lux = atof((const char *)lux_str);
						fire = atoi((const char *)fire_str);
						alt = atoi((const char *)alt_str);
						temper = atof((const char *)temper_str);
						humi = atof((const char *)humi_str);
						atmos = atof((const char *)atmos_str);
						people = atof((const char *)people_str);
//							printf("%d,%d,%.2f,%d,%d,%.2f,%.2f,%.2f\r\n",co2,tvoc,lux,fire,alt,temper,humi,atmos);
					}
					memset(rx_buffer, 0, MAX_BUFFER_SIZE);
					rx_index = 0;
				}
    }
}


	







