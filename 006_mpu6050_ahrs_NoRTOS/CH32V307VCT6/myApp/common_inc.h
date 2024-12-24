/*
 * common_inc.h
 *
 *  Created on: 2024Äê12ÔÂ21ÈÕ
 *      Author: 19816
 */

#ifndef MYAPP_COMMON_INC_H_
#define MYAPP_COMMON_INC_H_

//include
#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "ch32v30x.h"

//typedef
typedef unsigned char       uint8;
typedef unsigned short      uint16;
typedef unsigned int        uint32;
typedef unsigned long int   uint64;
#define ABS(X)    (((X)>0)?(X):-(X))
#define MAX(a,b)  ((a)>(b)?(a):(b))
#define MIN(a,b)  ((a)>(b)?(b):(a))

//User
#include "../User/config.h"

//myApp
#include "../myApp/scheduler/scheduler.h"

//sensor
#include "wp_math.h"
#include "filter.h"
#include "sensor.h"

//myDriver
#include "../myDriver/System/systick.h"
#include "../myDriver/Gpio/myGpio.h"
#include "../myDriver/Key/myKey.h"
#include <oled.h>
#include "lcd.h"
#include <Mpu6050.h>


#endif /* MYAPP_COMMON_INC_H_ */
