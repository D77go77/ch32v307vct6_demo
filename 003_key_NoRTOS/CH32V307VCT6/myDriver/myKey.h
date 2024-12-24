/*
 * key.h
 *
 *  Created on: 2024��12��21��
 *      Author: 19816
 */

#ifndef MYDRIVER_MYKEY_H_
#define MYDRIVER_MYKEY_H_

#include "../myApp/common_inc.h"

typedef enum {
    USER=0,
    KEY_NUM                            // ������ӹ���
}KEY;

typedef enum
{
    NO_PRESS=0,
    SHORT_PRESS,
    LONG_PRESS,
    IN_PRESS,
    KEEP_LONG_PRESS,
}press_state;

typedef struct {
    press_state    press;            // ��ǰ����״̬
    uint8_t        value;            // ��ǰ����ֵ
    uint8_t        last_value;       // ��һ�ΰ���ֵ
    uint16_t       padding1;         // ���ڶ��뵽 4�ֽڱ߽�
    GPIO_TypeDef  *port;             // ���� GPIO �˿�
    uint32_t       pin;              // ���� GPIO ���ź�
    uint32_t       press_time;       // ����ʱ���
    uint32_t       release_time;     // �ɿ�ʱ���
    uint32_t       in_time;          // ��ס����ʱ��
    uint32_t       in_press_cnt;     // ��ס����
    uint32_t       state_lock_time;  // ״̬����ʱ��
} key_state;

typedef struct
{
    key_state state[KEY_NUM];          // ��󰴼�λ
}my_key;

#define LONG_PRESS_LIMIT        1000 //1000ms
#define IN_PRESS_LIMIT          200  //250ms
#define KEEP_LONG_PRESS_LIMIT   5000 //��������5S

void nKey_init(void);
void task_key_gets(void);
void key_proc(void);

extern my_key key;

#endif /* MYDRIVER_MYKEY_H_ */
