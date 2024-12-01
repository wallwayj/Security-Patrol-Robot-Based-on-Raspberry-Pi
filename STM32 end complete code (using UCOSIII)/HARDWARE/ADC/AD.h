#ifndef __AD_H
#define __AD_H
#include "stm32f10x.h"                  // Device header
#include "stm32f10x_adc.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x_dma.h"
extern uint16_t AD_Value[4];

void AD_Init(void);

#endif
