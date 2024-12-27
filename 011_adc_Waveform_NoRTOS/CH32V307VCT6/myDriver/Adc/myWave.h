/*
 * myWave.h
 *
 *  Created on: 2024年12月27日
 *      Author: 19816
 */

#ifndef MYDRIVER_ADC_MYWAVE_H_
#define MYDRIVER_ADC_MYWAVE_H_

#include "common_inc.h"

void task_adc_proc(void);

void Calculate_mid(void);//计算中值
void Capture_save(void);//保存采样值
u16 Waveform_Recognition(void);


void DMA_Adc_Tx_Init( DMA_Channel_TypeDef* DMA_CHx, u32 ppadr, u32 memadr, u16 bufsize);
void ADC_Function_Init(void);
void nAdc_init(void);

#endif /* MYDRIVER_ADC_MYWAVE_H_ */
