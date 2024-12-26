/********************************** (C) COPYRIGHT *******************************
* File Name          : main.c
* Author             : WCH
* Version            : V1.0.0
* Date               : 2021/06/06
* Description        : Main program body.
*********************************************************************************
* Copyright (c) 2021 Nanjing Qinheng Microelectronics Co., Ltd.
* Attention: This software (modified or not) and binary are used for 
* microcontroller manufactured by Nanjing Qinheng Microelectronics.
*******************************************************************************/

/*
 *@Note
Input capture routine:
 TIM1_CH1(PA8)
 This example demonstrates the TIM_CH1(PA8) pin floating input, which detects an edge
  transition to trigger a TIM1 capture interrupt,
 The rising edge triggers the TIM_IT_CC1 interrupt, and the falling edge triggers the
  TIM_IT_CC2 interrupt.
 
*/

#include "debug.h"
     u32 tim_1,tim_2=0;  //周期模式的前两次采集
     u32 flow_count = 0;
     double Index_1=0;                 //测周期模式内部溢出
     volatile double frequency=1;      //待测频率
     double nCount=0;         //测频模式溢出值
     uint8_t modeSelect=1;   //模式选择（0: 测周法, 1: 测频法）
     u8 Index=0;                 //周期模式边沿次数
     u8 flag_capDown=0;               //一次测量完成标志

void TIM1_UP_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

void TIM2_Cap_Init(void)      //配置 TIM2_CH1_ETR 为外部脉冲计数
{
    GPIO_InitTypeDef GPIO_InitStructure;
    NVIC_InitTypeDef  NVIC_InitStructure;
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

    GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_15;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOA,GPIO_Pin_15);
    // 重映射 TIM2_CH1_ETR 到 PA15
    GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE); // 全重映射 TIM2

    TIM_TimeBaseStructure.TIM_Period = 1;
    TIM_TimeBaseStructure.TIM_Prescaler =1;//1Mh时钟
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0);
    // 配置 TIM2 中断
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; // TIM2 全局中断
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // 设置优先级
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // 开启 TIM2 的更新中断和捕获中断
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    TIM_SetCounter(TIM2, 0);
    TIM_Cmd(TIM2,ENABLE );

    if (modeSelect == 0)
    {
        // 测周法配置
        TIM_TimeBaseStructure.TIM_Period = 2; // TIM2 最大周期
        TIM_TimeBaseStructure.TIM_Prescaler = 0;       // TIM2 无分频
        TIM_TimeBaseStructure.TIM_ClockDivision = 0;
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
        TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

        TIM_TimeBaseStructure.TIM_Period = 0xFFFF - 1; // TIM1 最大周期
        TIM_TimeBaseStructure.TIM_Prescaler = 1;     // TIM1 分频 144MHz -> 1MHz
        TIM_TimeBaseStructure.TIM_ClockDivision = 0;
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
        TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
    }
    else if (modeSelect == 1)
    {
        // 测频法配置
        TIM_TimeBaseStructure.TIM_Period = 0xFFFF - 1; // TIM2 最大周期
        TIM_TimeBaseStructure.TIM_Prescaler = 1;       // TIM2 无分频
        TIM_TimeBaseStructure.TIM_ClockDivision = 0;
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
        TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

        TIM_TimeBaseStructure.TIM_Period = 4000;
        TIM_TimeBaseStructure.TIM_Prescaler = 36000-1;
        TIM_TimeBaseStructure.TIM_ClockDivision = 0;
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
        TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
    }
}

void TIM1_INIT(void)
{
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    NVIC_InitTypeDef  NVIC_InitStructure;

    RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_TIM1, ENABLE );

    TIM_TimeBaseInitStructure.TIM_Period = 0xffff-1 ;
    TIM_TimeBaseInitStructure.TIM_Prescaler = 1;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit( TIM1, &TIM_TimeBaseInitStructure);

    NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

//    TIM_ARRPreloadConfig( TIM1, ENABLE );

//    TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);//先不开启
//    TIM_Cmd( TIM1, ENABLE );
}


void TIM1_UP_IRQHandler(void)//1s进一次中断
{
    if (TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)
    {
        if (modeSelect == 0) // 测周法
        {
            flow_count++;
        }else//测频率法
        {
            nCount = TIM_GetCounter(TIM2);
            TIM_SetCounter(TIM2, 0);
            TIM_ITConfig(TIM2,TIM_IT_Update,DISABLE);
            frequency = 65535 * Index_1 +nCount;
            TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
            printf("freq_High: %.2f \r\n",frequency);
            nCount=0;
            Index_1=0;
            flag_capDown=1;//完成一次采集
        }

        TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
    }
}

void TIM2_IRQHandler(void)
{
    // TIM2 捕获中断（测周法）
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
    {
        if (modeSelect == 0) // 测周法
        {
            TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);//开启tim1定时器
            TIM_Cmd( TIM1, ENABLE );

            if(Index == 1)
            {
                tim_1 = flow_count *65535 + TIM_GetCounter(TIM1);
            }
            else if(Index == 2)
            {
                tim_2 = flow_count *65535 + TIM_GetCounter(TIM1);
                TIM_SetCounter(TIM1,0);
                Index = 0;
                flow_count = 0;
                frequency = (2.0*SystemCoreClock)/(tim_2-tim_1);
                printf("freq_Low: %.2f \r\n",frequency);
                flag_capDown = 1;//完成一次测量
            }
            Index++;
        }
        else  //测频率法
        {
            nCount++;
            TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);//开启tim1定时器
            TIM_Cmd( TIM1, ENABLE );
        }
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update); // 清除更新中断标志
    }
}

/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{


	USART_Printf_Init(115200);
	SystemCoreClockUpdate();	
	printf("SystemClk:%d\r\n",SystemCoreClock);
	printf( "ChipID:%08x\r\n", DBGMCU_GetCHIPID() );

	TIM1_INIT();
	TIM2_Cap_Init();
	while(1){
//        if (frequency < 10000.0) // 判断频率范围
//        {
//            modeSelect = 0; // 低频，使用测周法
//            printf("Frequency (Period Method): %.2f Hz\r\n", frequency);
//        }
//        else
//        {
//            modeSelect = 1; // 高频，使用测频法
//            printf("Frequency (Count Method): %.2f Hz\r\n", frequency);
//        }


	}
}
