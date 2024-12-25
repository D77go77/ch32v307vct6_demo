/*
 * config.c
 *
 *  Created on: 2024年12月22日
 *      Author: 19816
 */
#include "config.h"

//#define  GPIO_PORT        (GPIOD)
//#define  GPIO_PIN         (GPIO_Pin_3)
//#define  GPIO_SET         (GPIO_SetBits(GPIO_PORT, GPIO_PIN))   //输出高电平
//#define  GPIO_RESET       (GPIO_ResetBits(GPIO_PORT, GPIO_PIN)) //输出低电平
//#define  GPIO_INPUT       (GPIO_ReadOutputDataBit(GPIO_PORT, GPIO_PIN)) //获取输入电平
//#define  GPIO_TOGGLE      (GPIO_WriteBit(GPIO_PORT, GPIO_PIN, 1-GPIO_INPUT)) //输出翻转
//#define  GPIO_RCC_ENADLE  (RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE)) //打开时钟线

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
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);       //启动GPIO的时钟线,让时钟进去以驱动其GPIO
    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_LED0;                   //pin PA0
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;            //推挽输出(最大驱动能力输出)
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;           //频率越高,切换GPIO高低电平时间越短
    GPIO_Init(GPIO_PORT_LED0, &GPIO_InitStructure);
    //led1
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);       //启动GPIO的时钟线,让时钟进去以驱动其GPIO
    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_LED1;                   //pin PA1
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;            //推挽输出(最大驱动能力输出)
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;           //频率越高,切换GPIO高低电平时间越短
    GPIO_Init(GPIO_PORT_LED1, &GPIO_InitStructure);
    //key_user
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);       //启动GPIO的时钟线,让时钟进去以驱动其GPIO
    GPIO_InitStructure.GPIO_Pin = GPIO_PIN_keyUser;                //pin PA2
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;               //弱上拉输入
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



