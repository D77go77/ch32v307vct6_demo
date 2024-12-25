/*
 * config.h
 *
 *  Created on: 2024Äê12ÔÂ22ÈÕ
 *      Author: 19816
 */

#ifndef USER_CONFIG_H_
#define USER_CONFIG_H_

#include "../myApp/common_inc.h"

//led
#define GPIO_PORT_LED0  GPIOA
#define GPIO_PIN_LED0   GPIO_Pin_0
#define GPIO_PORT_LED1  GPIOA
#define GPIO_PIN_LED1   GPIO_Pin_1

//key
#define GPIO_PORT_keyUser  GPIOA
#define GPIO_PIN_keyUser   GPIO_Pin_2

//oled
#define GPIO_PORT_OLED_SCL   GPIOB
#define GPIO_PIN_OLED_SCL    GPIO_Pin_10
#define GPIO_PORT_OLED_SDA   GPIOB
#define GPIO_PIN_OLED_SDA    GPIO_Pin_11

//mpu6050 correction coefficient
#define EULER_OFFICIENT 1.24138

void debug_usart1(void);

#endif /* USER_CONFIG_H_ */
