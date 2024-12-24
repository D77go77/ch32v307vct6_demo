/*
 * gpio_driver.h
 *
 *  Created on: 2024年12月21日
 *      Author: 19816
 */

#ifndef MYDRIVER_GPIO_DRIVER_H_
#define MYDRIVER_GPIO_DRIVER_H_

#include "../myApp/common_inc.h"


typedef struct                   //结构体对齐
{
    GPIO_TypeDef *port;          // 4字节或8字节（根据指针大小）- 端口地址放在首位
    uint32_t pin;                // 4字节 - GPIO引脚号
    uint32_t period;             // 4字节 - 闪烁周期
    uint16_t times;              // 2字节 - 预设闪烁总次数
    uint16_t cnt;                // 2字节 - 闪烁控制计数器
    uint16_t times_cnt;          // 2字节 - 记录已闪烁次数
    uint8_t reset;               // 1字节 - 闪烁进程复位标志
    uint8_t end;                 // 1字节 - 闪烁完成标志位
    float light_on_percent;      // 4字节 - 单个周期内点亮时间百分比
} _gpio_control;

extern _gpio_control led0;
extern _gpio_control led1;

void task_led1_proc(void);
void task_led0_proc(void);
void led_setup(uint32_t _period, float _light_on_percent, uint16_t _times);
void GPIOx_INIT(void);

#endif /* MYDRIVER_GPIO_DRIVER_H_ */
