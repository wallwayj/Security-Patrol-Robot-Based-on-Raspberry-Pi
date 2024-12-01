#include"stm32f10x.h"
#include"beep.h"
#include"delay.h"
void beep_init(void)
{
	GPIO_InitTypeDef be;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	be.GPIO_Mode=GPIO_Mode_Out_PP;
	be.GPIO_Pin=GPIO_Pin_8;
	be.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&be);
}
void Buzzer_ON()
{
	beep=1;
}

void Buzzer_OFF()
{
	beep=0;
}

void Buzzer1()	//·äÃùÆ÷ÏìÒ»Éù
{
	Buzzer_ON();
	delay_ms(300);
	Buzzer_OFF();
}

void Buzzer2()	//·äÃùÆ÷ÏìÁ½Éù
{
	Buzzer_ON();
	delay_ms(100);
	Buzzer_OFF();
	delay_ms(100);
	Buzzer_ON();
	delay_ms(100);
	Buzzer_OFF();
}

void Buzzer_Alarm()	//·äÃùÆ÷·¢³ö¾¯±¨
{
	Buzzer_ON();
	delay_ms(50);
	Buzzer_OFF();
	delay_ms(50);
	Buzzer_ON();
	delay_ms(50);
	Buzzer_OFF();
	delay_ms(50);
	Buzzer_ON();
	delay_ms(50);
	Buzzer_OFF();
	delay_ms(50);
	Buzzer_ON();
	delay_ms(50);
	Buzzer_OFF();
}
