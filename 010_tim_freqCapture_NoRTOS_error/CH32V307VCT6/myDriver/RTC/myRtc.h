/*
 * myRtc.h
 *
 *  Created on: 2024Äê12ÔÂ25ÈÕ
 *      Author: 19816
 */

#ifndef MYDRIVER_RTC_MYRTC_H_
#define MYDRIVER_RTC_MYRTC_H_

#include "../myApp/common_inc.h"

typedef struct
{
    vu16 w_year;
    vu8  w_month;
    vu8  w_date;
    //vu8  week;
    vu8 hour;
    vu8 min;
    vu8 sec;
} _calendar_obj;

extern _calendar_obj calendar;


void task_rtc_proc(void);

u8 nRTC_Init(void);

#endif /* MYDRIVER_RTC_MYRTC_H_ */
