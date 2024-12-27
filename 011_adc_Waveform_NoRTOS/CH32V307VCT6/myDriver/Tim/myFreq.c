/*
 * nfreq.c
 *
 *  Created on: 2024��12��26��
 *      Author: 19816
 */
#include <myFreq.h>

 u32 tim_1,tim_2=0;  //����ģʽ��ǰ���βɼ�
 u32 flow_count = 0;
 double Index_1=0;                 //������ģʽ�ڲ����
 volatile double frequency=0;      //����Ƶ��
 double nCount=0;         //��Ƶģʽ���ֵ
 uint8_t modeSelect=1;   //ģʽѡ��0: ���ܷ�, 1: ��Ƶ����
 u8 Index=0;                 //����ģʽ���ش���
 u8 flag_capDown=0;               //һ�β�����ɱ�־

void TIM1_UP_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));


/*********************************************************************
 * @fn      TIM2_Cap_Init
 *
 * @brief   ���� TIM2_CH1_ETR Ϊ�ⲿ�������
 *                                  ��������PA15Ϊ������������
 *
 * @return  none
 */
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
        TIM_TimeBaseStructure.TIM_Period = 3; // TIM2 �������
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
/*********************************************************************
 * @fn      TIM1_INIT
 *
 * @brief   ���� TIM1_INIT Ϊ�������������,�ɼ���Ƶ
 *
 *
 * @return  none
 */
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
/*********************************************************************
 * @fn      nFreq_init
 *
 * @brief   nFreq_init ��Ƶ�Ƴ�ʼ��
 *
 *
 * @return  none
 */
void nFreq_init(void)
{
    TIM1_INIT();
    TIM2_Cap_Init();
}
/*********************************************************************
 * @fn      TIM1_UP_IRQHandler
 *
 * @brief   ��ʱ��1�жϺ���
 *
 *
 * @return  none
 */

void TIM1_UP_IRQHandler(void)//1s��һ���ж�
{
    if (TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
        if (modeSelect == 0) // ���ܷ�
        {
            flow_count++;
        }else//��Ƶ�ʷ�
        {
            nCount = TIM_GetCounter(TIM2);
            TIM_SetCounter(TIM2, 0);
            TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
            frequency = 65535 * Index_1 +nCount;

            printf("freq_High: %.2f \r\n",frequency);
            nCount=0;
            Index_1=0;
            flag_capDown=1;//���һ�βɼ�
        }
    }
}
/*********************************************************************
 * @fn      TIM2_IRQHandler
 *
 * @brief   ��ʱ��2�����жϺ���
 *
 *
 * @return  none
 */
void TIM2_IRQHandler(void)
{
    // TIM2 �����жϣ����ܷ���
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update); // ��������жϱ�־
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
                flag_capDown = 1;//���һ�β���
            }
            Index++;
        }
        else  //��Ƶ�ʷ�
        {
            Index_1++;
            TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);//����tim1��ʱ��
            TIM_Cmd( TIM1, ENABLE );
        }
    }
}





