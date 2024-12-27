/*
 * nfreq.c
 *
 *  Created on: 2024年12月26日
 *      Author: 19816
 */
#include <myFreq.h>

 u32 tim_1,tim_2=0;  //周期模式的前两次采集
 u32 flow_count = 0;
 double Index_1=0;                 //测周期模式内部溢出
 volatile double frequency=0;      //待测频率
 double nCount=0;         //测频模式溢出值
 uint8_t modeSelect=1;   //模式选择（0: 测周法, 1: 测频法）
 u8 Index=0;                 //周期模式边沿次数
 u8 flag_capDown=0;               //一次测量完成标志

void TIM1_UP_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
void TIM2_IRQHandler(void) __attribute__((interrupt("WCH-Interrupt-fast")));


/*********************************************************************
 * @fn      TIM2_Cap_Init
 *
 * @brief   配置 TIM2_CH1_ETR 为外部脉冲计数
 *                                  其中配置PA15为脉冲输入引脚
 *
 * @return  none
 */
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
        TIM_TimeBaseStructure.TIM_Period = 3; // TIM2 最大周期
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
/*********************************************************************
 * @fn      TIM1_INIT
 *
 * @brief   配置 TIM1_INIT 为辅助脉冲计数器,采集高频
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
//    TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);//先不开启
//    TIM_Cmd( TIM1, ENABLE );
}
/*********************************************************************
 * @fn      nFreq_init
 *
 * @brief   nFreq_init 计频计初始化
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
 * @brief   定时器1中断函数
 *
 *
 * @return  none
 */

void TIM1_UP_IRQHandler(void)//1s进一次中断
{
    if (TIM_GetITStatus(TIM1, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
        if (modeSelect == 0) // 测周法
        {
            flow_count++;
        }else//测频率法
        {
            nCount = TIM_GetCounter(TIM2);
            TIM_SetCounter(TIM2, 0);
            TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
            frequency = 65535 * Index_1 +nCount;

            printf("freq_High: %.2f \r\n",frequency);
            nCount=0;
            Index_1=0;
            flag_capDown=1;//完成一次采集
        }
    }
}
/*********************************************************************
 * @fn      TIM2_IRQHandler
 *
 * @brief   定时器2更新中断函数
 *
 *
 * @return  none
 */
void TIM2_IRQHandler(void)
{
    // TIM2 捕获中断（测周法）
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
    {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update); // 清除更新中断标志
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
                flag_capDown = 1;//完成一次测量
            }
            Index++;
        }
        else  //测频率法
        {
            Index_1++;
            TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);//开启tim1定时器
            TIM_Cmd( TIM1, ENABLE );
        }
    }
}





