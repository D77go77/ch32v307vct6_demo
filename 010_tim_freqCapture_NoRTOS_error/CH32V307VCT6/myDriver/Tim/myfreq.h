/*
 * nfreq.h
 *
 *  Created on: 2024��12��26��
 *      Author: 19816
 */

#ifndef MYDRIVER_TIM_MYFREQ_H_
#define MYDRIVER_TIM_MYFREQ_H_

#include "common_inc.h"

// typedef struct{
//     u32 first_cap,second_cap;      //����ģʽ��ǰ���βɼ�
//     u32 flowCount;                 //������ģʽ�ڲ����
//     volatile float frequency;               //����Ƶ��
//     volatile double overflow_value;         //��Ƶģʽ���ֵ
//     volatile double nCount;                 //����ģʽδ���ֵ����
//     volatile u8 modeSelect;                 //ģʽѡ��0: ���ܷ�, 1: ��Ƶ����
//     u8 Edge_index;                 //����ģʽ���ش���
//     u8 flag_capDown;               //һ�β�����ɱ�־
// }freq_capture;
//
// extern freq_capture freq;

extern volatile double frequency;
void task_freq_task(void);
void nFreq_init(void);


/* MYDRIVER_TIM_MYFREQ_H_ */
#endif
