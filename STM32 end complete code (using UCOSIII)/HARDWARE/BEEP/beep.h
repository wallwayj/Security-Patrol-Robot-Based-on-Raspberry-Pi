#ifndef __beep_h
#define __beep_h
#include"sys.h"
#include"delay.h"
#define beep PBout(8)
void beep_init(void);
void Buzzer_ON(void);
void Buzzer_OFF(void);
void Buzzer1(void);
void Buzzer2(void);
void Buzzer_Alarm(void);


#endif 
