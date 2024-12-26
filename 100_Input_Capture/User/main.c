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
     u32 tim_1,tim_2=0;  //����ģʽ��ǰ���βɼ�
     u32 flow_count = 0;
     double Index_1=0;                 //������ģʽ�ڲ����
     volatile double frequency=1;      //����Ƶ��
     double nCount=0;         //��Ƶģʽ���ֵ
     uint8_t modeSelect=1;   //ģʽѡ��0: ���ܷ�, 1: ��Ƶ����
     u8 Index=0;                 //����ģʽ���ش���
     u8 flag_capDown=0;               //һ�β�����ɱ�־

void TIM1_UP_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));

void TIM2_Cap_Init(void)      //���� TIM2_CH1_ETR Ϊ�ⲿ�������
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
    // ��ӳ�� TIM2_CH1_ETR �� PA15
    GPIO_PinRemapConfig(GPIO_FullRemap_TIM2, ENABLE); // ȫ��ӳ�� TIM2

    TIM_TimeBaseStructure.TIM_Period = 1;
    TIM_TimeBaseStructure.TIM_Prescaler =1;//1Mhʱ��
    TIM_TimeBaseStructure.TIM_ClockDivision = 0;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    TIM_ETRClockMode2Config(TIM2, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0);
    // ���� TIM2 �ж�
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn; // TIM2 ȫ���ж�
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // �������ȼ�
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // ���� TIM2 �ĸ����жϺͲ����ж�
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    TIM_SetCounter(TIM2, 0);
    TIM_Cmd(TIM2,ENABLE );

    if (modeSelect == 0)
    {
        // ���ܷ�����
        TIM_TimeBaseStructure.TIM_Period = 2; // TIM2 �������
        TIM_TimeBaseStructure.TIM_Prescaler = 0;       // TIM2 �޷�Ƶ
        TIM_TimeBaseStructure.TIM_ClockDivision = 0;
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
        TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

        TIM_TimeBaseStructure.TIM_Period = 0xFFFF - 1; // TIM1 �������
        TIM_TimeBaseStructure.TIM_Prescaler = 1;     // TIM1 ��Ƶ 144MHz -> 1MHz
        TIM_TimeBaseStructure.TIM_ClockDivision = 0;
        TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
        TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
    }
    else if (modeSelect == 1)
    {
        // ��Ƶ������
        TIM_TimeBaseStructure.TIM_Period = 0xFFFF - 1; // TIM2 �������
        TIM_TimeBaseStructure.TIM_Prescaler = 1;       // TIM2 �޷�Ƶ
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

//    TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);//�Ȳ�����
//    TIM_Cmd( TIM1, ENABLE );
}


void TIM1_UP_IRQHandler(void)//1s��һ���ж�
{
    if (TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)
    {
        if (modeSelect == 0) // ���ܷ�
        {
            flow_count++;
        }else//��Ƶ�ʷ�
        {
            nCount = TIM_GetCounter(TIM2);
            TIM_SetCounter(TIM2, 0);
            TIM_ITConfig(TIM2,TIM_IT_Update,DISABLE);
            frequency = 65535 * Index_1 +nCount;
            TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
            printf("freq_High: %.2f \r\n",frequency);
            nCount=0;
            Index_1=0;
            flag_capDown=1;//���һ�βɼ�
        }

        TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
    }
}

void TIM2_IRQHandler(void)
{
    // TIM2 �����жϣ����ܷ���
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
    {
        if (modeSelect == 0) // ���ܷ�
        {
            TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);//����tim1��ʱ��
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
                flag_capDown = 1;//���һ�β���
            }
            Index++;
        }
        else  //��Ƶ�ʷ�
        {
            nCount++;
            TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);//����tim1��ʱ��
            TIM_Cmd( TIM1, ENABLE );
        }
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update); // ��������жϱ�־
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
//        if (frequency < 10000.0) // �ж�Ƶ�ʷ�Χ
//        {
//            modeSelect = 0; // ��Ƶ��ʹ�ò��ܷ�
//            printf("Frequency (Period Method): %.2f Hz\r\n", frequency);
//        }
//        else
//        {
//            modeSelect = 1; // ��Ƶ��ʹ�ò�Ƶ��
//            printf("Frequency (Count Method): %.2f Hz\r\n", frequency);
//        }


	}
}
