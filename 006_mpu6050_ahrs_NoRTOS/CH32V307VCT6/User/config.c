/*
 * config.c
 *
 *  Created on: 2024��12��22��
 *      Author: 19816
 */
#include "config.h"

//#define  GPIO_PORT        (GPIOD)
//#define  GPIO_PIN         (GPIO_Pin_3)
//#define  GPIO_SET         (GPIO_SetBits(GPIO_PORT, GPIO_PIN))   //����ߵ�ƽ
//#define  GPIO_RESET       (GPIO_ResetBits(GPIO_PORT, GPIO_PIN)) //����͵�ƽ
//#define  GPIO_INPUT       (GPIO_ReadOutputDataBit(GPIO_PORT, GPIO_PIN)) //��ȡ�����ƽ
//#define  GPIO_TOGGLE      (GPIO_WriteBit(GPIO_PORT, GPIO_PIN, 1-GPIO_INPUT)) //�����ת
//#define  GPIO_RCC_ENADLE  (RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE)) //��ʱ����

/*********************************************************************
 * @fn      GPIOA_INIT
 *
 * @brief   Initializes GPIOA0_A1
 *
 * @return  none
 */
void GPIOx_INIT(void)
{
    GPIO_InitTypeDef GPIO_InitStructure = {0};

    //led0
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);       //����GPIO��ʱ����,��ʱ�ӽ�ȥ��������GPIO
    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_LED0;                   //pin PA0
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;            //�������(��������������)
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;           //Ƶ��Խ��,�л�GPIO�ߵ͵�ƽʱ��Խ��
    GPIO_Init(GPIO_PORT_LED0, &GPIO_InitStructure);
    //led1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);       //����GPIO��ʱ����,��ʱ�ӽ�ȥ��������GPIO
    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_LED1;                   //pin PA1
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;            //�������(��������������)
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;           //Ƶ��Խ��,�л�GPIO�ߵ͵�ƽʱ��Խ��
    GPIO_Init(GPIO_PORT_LED1, &GPIO_InitStructure);
    //key_user
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);       //����GPIO��ʱ����,��ʱ�ӽ�ȥ��������GPIO
    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_keyUser;                //pin PA2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;               //����������
    GPIO_Init(GPIO_PORT_keyUser, &GPIO_InitStructure);
//    //oled
//    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
//    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_OLED_SCL | GPIO_PIN_OLED_SDA;
//    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
//    GPIO_Init(GPIO_PORT_OLED_SCL, &GPIO_InitStructure);

}

void debug_usart1(void)
{
    printf("%.2f--%.2f--%.2f \r\n",smartcar_imu.rpy_deg[ROL],smartcar_imu.rpy_deg[PIT],smartcar_imu.rpy_deg[YAW]);
    printf("yaw:%f\n",smartcar_imu.rpy_deg[YAW]);
}



