/*
 * myWave.c
 *
 *  Created on: 2024年12月27日
 *      Author: 19816
 */


#include "myWave.h"

#define SAVE_MAX 256
u16 TxBuf[SAVE_MAX];//DMA缓存区
u16 save_ad[SAVE_MAX];//采集电压值

struct wavepro {
    u16 mid;  // 中值
    u16 max;  // 最大值
    u16 min;  // 最小值
};
struct wavepro wave;

/*********************************************************************
 * @fn      task_adc_proc
 * time     100ms
 * @brief   ADC 初始化和配置
 *
 * @return  none
 */
void task_adc_proc(void)
{
    static u8 waveType = 0;
    //ADC波形采集
	Capture_save();
    Calculate_mid();
    waveType = Waveform_Recognition();

    switch (waveType)
    {
    case 1:printf("三角波\r\n");break;
    case 2:printf("正弦波\r\n");break;
    case 3:printf("方波\r\n");break;
    default:
        //printf("未识别\r\n");
        break;
    }
}


/*********************************************************************
 * @fn      TIM1_Int_Init
 *
 * @brief   定时器1输出PWM控制adc—dma采样率初始化和配置
 *
 * @return  none
 */
void TIM1_Int_Init(void)
{
    TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;
    TIM_OCInitTypeDef         TIM_OCInitStructure;
 
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
 
    /* Time Base configuration */
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); 
    TIM_TimeBaseStructure.TIM_Period = 0xffff;     //1098HZc采样率     
    TIM_TimeBaseStructure.TIM_Prescaler = 0;       
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;    
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
    TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
 
    /* TIM1 channel1 configuration in PWM mode */
    TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;                
    TIM_OCInitStructure.TIM_Pulse = 0xffff; 
    TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;         
    TIM_OC1Init(TIM1, &TIM_OCInitStructure);
 
    TIM_CtrlPWMOutputs(TIM1, ENABLE);
    TIM_Cmd(TIM1, ENABLE);
}
/*********************************************************************
 * @fn      nAdc_init
 *
 * @brief   ADC DMA采样初始化和配置
 *
 * @return  none
 */
void nAdc_init(void)
{
    ADC_Function_Init();
    TIM1_Int_Init();
    DMA_Adc_Tx_Init( DMA1_Channel1, (u32)&ADC1->RDATAR, (u32)TxBuf, SAVE_MAX );      //缓存区选择
    DMA_Cmd( DMA1_Channel1, ENABLE );
    ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_239Cycles5 );//通道选择搬运
    //ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    ADC_ExternalTrigConvCmd(ADC1, ENABLE);  //启动ADC转换
}
/*********************************************************************
 * @fn      ADC_Function_Init
 *
 * @brief   ADC 初始化和配置
 *
 * @return  none
 */
void ADC_Function_Init(void)
{
    ADC_InitTypeDef ADC_InitStructure={0};
    GPIO_InitTypeDef GPIO_InitStructure={0};

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE );
    RCC_ADCCLKConfig(RCC_PCLK2_Div8);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;           //PA5
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    ADC_DeInit(ADC1);
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;                       //单通道
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;                  //连续转换
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;//Timer1触发转换开启(定时器T1的CC1通道，控制采样频率)      
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfChannel = 1;                             //只有一个通道
    ADC_Init(ADC1, &ADC_InitStructure);

    ADC_DMACmd(ADC1, ENABLE);       //启用 ADC 和 DMA
    ADC_Cmd(ADC1, ENABLE);

    ADC_BufferCmd(ADC1, DISABLE);   //disable buffer

    ADC_ResetCalibration(ADC1);     //启动校准
    while(ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while(ADC_GetCalibrationStatus(ADC1));
}


/*********************************************************************
 * @fn      Get_ADC_Val
 *
 * @brief   单次 ADC 转换//普通adc采样//使用DMA传输不需要此函数
 *
 * @param   ch - ADC channel.
 *            ADC_Channel_0 - ADC Channel0 selected.
 *            ADC_Channel_1 - ADC Channel1 selected.
 *            ADC_Channel_2 - ADC Channel2 selected.
 *            ADC_Channel_3 - ADC Channel3 selected.
 *            ADC_Channel_4 - ADC Channel4 selected.
 *            ADC_Channel_5 - ADC Channel5 selected.
 *            ADC_Channel_6 - ADC Channel6 selected.
 *            ADC_Channel_7 - ADC Channel7 selected.
 *            ADC_Channel_8 - ADC Channel8 selected.
 *            ADC_Channel_9 - ADC Channel9 selected.
 *            ADC_Channel_10 - ADC Channel10 selected.
 *            ADC_Channel_11 - ADC Channel11 selected.
 *            ADC_Channel_12 - ADC Channel12 selected.
 *            ADC_Channel_13 - ADC Channel13 selected.
 *            ADC_Channel_14 - ADC Channel14 selected.
 *            ADC_Channel_15 - ADC Channel15 selected.
 *            ADC_Channel_16 - ADC Channel16 selected.
 *            ADC_Channel_17 - ADC Channel17 selected.
 *
 * @return  none
 */
u16 Get_ADC_Val(u8 ch)
{
    u16 val;

    ADC_RegularChannelConfig(ADC1, ch, 1, ADC_SampleTime_239Cycles5 );
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC ));
    val = ADC_GetConversionValue(ADC1);
    return val;
}

/*********************************************************************
 * @fn      DMA_Adc_Tx_Init
 *
 * @brief   DMA 初始化
 *
 * @param   DMA_CHx - x can be 1 to 7.
 *          ppadr - Peripheral base address.
 *          memadr - Memory base address.
 *          bufsize - DMA channel buffer size.
 *
 * @return  none
 */
void DMA_Adc_Tx_Init( DMA_Channel_TypeDef* DMA_CHx, u32 ppadr, u32 memadr, u16 bufsize)
{
    
    DMA_InitTypeDef DMA_InitStructure={0};
    RCC_AHBPeriphClockCmd( RCC_AHBPeriph_DMA1, ENABLE );
    DMA_DeInit(DMA_CHx);
    DMA_InitStructure.DMA_PeripheralBaseAddr = ppadr;
    DMA_InitStructure.DMA_MemoryBaseAddr = memadr;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
    DMA_InitStructure.DMA_BufferSize = bufsize;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_Priority = DMA_Priority_VeryHigh;
    DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
    DMA_Init( DMA_CHx, &DMA_InitStructure );
}



//采集预判定计算中指
void Calculate_mid(void)
{
    u16 i;
    wave.max = save_ad[0];
    wave.min = save_ad[0];
    for (i = 1; i < SAVE_MAX; i++)
    {
        if (wave.min > save_ad[i]) wave.min = save_ad[i];
        if (wave.max < save_ad[i]) wave.max = save_ad[i];
    }
    wave.mid = (wave.max + wave.min) / 2;  // 计算中值
}


//ADC1采样程序
void Capture_save(void)
{
    u16 i;

    for (i = 0; i < SAVE_MAX; i++)
    {
		save_ad[i] = TxBuf[i];
    }
}


#define T_N 14        // 判别循环次数
#define ERR_A 0xffff  // 错误代码A255
#define ERR_B 0xfffe  // 错误代码B254
#define UNFOUND 0xfffd // 起点或终点未找到253

#define MIN_PERIOD_SAMPLES 14  // 假设信号频率最高为 50Hz，每周期至少需要 20 点
#define MAX_NOISE_THRESHOLD 1  // 噪声阈值，防止小振幅误判

u16 Waveform_Recognition(void) 
{
    u16 i, a = 0, b = 0;
    u32 sum = 0;
    u16 s = 0;
    static u16 s_cnt = 0;
    static u8 ss[4];
    static u16 pre_s;

    // 查找起点 a
    for (i = 0; i < SAVE_MAX; i++) 
    {
        if (save_ad[i] > wave.mid && save_ad[i + 3] > wave.mid) {
            a = i;
            break;
        }
    }

    // 查找终点 b
    if(a == 0) return UNFOUND;
    for (i = a + 1; i < SAVE_MAX; i++) {
        if ((save_ad[i] > save_ad[i + 2]) &&
            ((fabs(save_ad[i] - wave.mid) <= (wave.max - wave.min) * 3 / 100) ||
             (save_ad[i] - save_ad[i + 3]) >= ((wave.max - wave.min) / 2))) {
            b = i;
            break;
        }
    }

    if(b == 0) return UNFOUND;
    // 计算面积 sum
    for (i = a; i < b; i++) {
        sum += fabs(save_ad[i] - wave.mid);
    }
    // 计算系数 s
    s = 1.0 * (wave.max - wave.min) * (b - a + 1) * 100 / sum;
    //printf("s:%d\r\n", s);

    // 波形判别逻辑
    if (s > 360 && s < 400) 
    {
        ss[1]++;  //正弦波
    } else if (s > 310 && s <= 360) 
    {
        ss[2]++;  //  三角波
    } else if (s > 0 && s <= 310) 
    {
        ss[3]++;  // 方波
    } else {
        ss[0]++;  // 未识别
    }
    s_cnt++;

    if (s_cnt == T_N) 
    {
        s_cnt = 0;
        s = ss[0];
        pre_s = 4;
        for (i = 1; i < 4; i++) 
        {
            if (s < ss[i]) 
            {
                s = ss[i];
                pre_s = i;
            }
        }
        for (i = 0; i < 4; i++) ss[i] = 0;
        return pre_s;
    } else {
        return UNFOUND;
    }
}













