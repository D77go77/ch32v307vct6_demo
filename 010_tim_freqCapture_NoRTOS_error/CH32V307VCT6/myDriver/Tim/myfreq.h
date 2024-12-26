/*
 * nfreq.h
 *
 *  Created on: 2024年12月26日
 *      Author: 19816
 */

#ifndef MYDRIVER_TIM_MYFREQ_H_
#define MYDRIVER_TIM_MYFREQ_H_

#include "common_inc.h"

// typedef struct{
//     u32 first_cap,second_cap;      //周期模式的前两次采集
//     u32 flowCount;                 //测周期模式内部溢出
//     volatile float frequency;               //待测频率
//     volatile double overflow_value;         //测频模式溢出值
//     volatile double nCount;                 //测评模式未溢出值个数
//     volatile u8 modeSelect;                 //模式选择（0: 测周法, 1: 测频法）
//     u8 Edge_index;                 //周期模式边沿次数
//     u8 flag_capDown;               //一次测量完成标志
// }freq_capture;
//
// extern freq_capture freq;

extern volatile double frequency;
void task_freq_task(void);
void nFreq_init(void);


/* MYDRIVER_TIM_MYFREQ_H_ */
#endif
