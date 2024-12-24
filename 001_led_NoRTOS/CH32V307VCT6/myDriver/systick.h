/*
 * systick.h
 *
 *  Created on: 2024Äê12ÔÂ21ÈÕ
 *      Author: 19816
 */

#ifndef MYDRIVER_SYSTICK_H_
#define MYDRIVER_SYSTICK_H_

#include "../myApp/common_inc.h"


extern uint32_t tickTime;

void SYSTICK_Init_Config(u_int64_t ticks);


#endif /* MYDRIVER_SYSTICK_H_ */
