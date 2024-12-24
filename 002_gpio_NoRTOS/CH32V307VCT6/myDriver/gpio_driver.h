/*
 * gpio_driver.h
 *
 *  Created on: 2024��12��21��
 *      Author: 19816
 */

#ifndef MYDRIVER_GPIO_DRIVER_H_
#define MYDRIVER_GPIO_DRIVER_H_

#include "../myApp/common_inc.h"


typedef struct                   //�ṹ�����
{
    GPIO_TypeDef *port;          // 4�ֽڻ�8�ֽڣ�����ָ���С��- �˿ڵ�ַ������λ
    uint32_t pin;                // 4�ֽ� - GPIO���ź�
    uint32_t period;             // 4�ֽ� - ��˸����
    uint16_t times;              // 2�ֽ� - Ԥ����˸�ܴ���
    uint16_t cnt;                // 2�ֽ� - ��˸���Ƽ�����
    uint16_t times_cnt;          // 2�ֽ� - ��¼����˸����
    uint8_t reset;               // 1�ֽ� - ��˸���̸�λ��־
    uint8_t end;                 // 1�ֽ� - ��˸��ɱ�־λ
    float light_on_percent;      // 4�ֽ� - ���������ڵ���ʱ��ٷֱ�
} _gpio_control;

extern _gpio_control led0;
extern _gpio_control led1;

void task_led1_proc(void);
void task_led0_proc(void);
void led_setup(uint32_t _period, float _light_on_percent, uint16_t _times);
void GPIOx_INIT(void);

#endif /* MYDRIVER_GPIO_DRIVER_H_ */
