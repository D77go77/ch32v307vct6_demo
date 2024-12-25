/*
 * myAdc.h
 *
 *  Created on: 2024��12��23��
 *      Author: 19816
 */

#ifndef MYDRIVER_ADC_MYADC_H_
#define MYDRIVER_ADC_MYADC_H_

#include "common_inc.h"

typedef struct
{
    float value;           // 4 �ֽ�
    float upper;           // 4 �ֽ�
    float lower;           // 4 �ֽ�
    uint16_t low_vbat_cnt; // 2 �ֽ�
    uint8_t enable;        // 1 �ֽ�
    u8 low_flag;           // 1 �ֽ�
}low_voltage;
extern low_voltage vbat;

void task_adc_proc(void);
void nAdc_init(void);
void ADC_Function_Init(void);
u16 Get_ADC_Val(u8 ch);
void DMA_Adc_Tx_Init( DMA_Channel_TypeDef* DMA_CHx, u32 ppadr, u32 memadr, u16 bufsize);
float Get_ConversionVal(s16 val);
void battery_voltage_detection(void);

#endif /* MYDRIVER_ADC_MYADC_H_ */
