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


//myApp
#include "../myApp/scheduler.h"


//myDriver
#include "../myDriver/gpio_driver.h"
#include "../myDriver/systick.h"



#endif /* MYAPP_COMMON_INC_H_ */
