/*
 * myAdc.c
 *
 *  Created on: 2024年12月23日
 *      Author: 19816
 */
#include "myAdc.h"

u16 TxBuf[1024];
float Calibrattion_Val = 0;
float voltage = 0;

low_voltage vbat={
    .enable=no_voltage_enable_default,
    .value=0,
    .upper=no_voltage_upper_default,
    .lower=no_voltage_lower_default,
    .low_flag=0
};
/*********************************************************************
 * @fn      task_adc_proc
 * time     100ms
 * @brief   ADC 初始化和配置
 *
 * @return  none
 */
void task_adc_proc(void)
{

    static u16 index = 0;
    if (++index>=1024) index=0;
    vbat.value = Get_ConversionVal(TxBuf[index]);
    battery_voltage_detection();//电池检测
}


void nAdc_init(void)
{
    ADC_Function_Init();
    DMA_Adc_Tx_Init( DMA1_Channel1, (u32)&ADC1->RDATAR, (u32)TxBuf, 1024 );      //缓存区选择
    DMA_Cmd( DMA1_Channel1, ENABLE );
    ADC_RegularChannelConfig(ADC1, ADC_Channel_5, 1, ADC_SampleTime_239Cycles5 );//通道选择搬运
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}
/*********************************************************************
 * @fn      void battery_voltage_detection(void)
 *
 * @brief   电池电压监测 需要设定电压阈值
 *
 * @return  none
 */
void battery_voltage_detection(void)
{
    static uint16_t _cnt=0;

    if(++_cnt>=10)//每1S检测一次 100*10==1s
    {
        _cnt=0;
        if(vbat.value<=vbat.lower)   vbat.low_vbat_cnt++;
        else vbat.low_vbat_cnt/=4;

        if(vbat.low_vbat_cnt>=5)//持续5s满足
        {
            vbat.low_vbat_cnt=0;
            if(vbat.enable==1)
            {
                vbat.low_flag=1;//强断标志位
                led0_setup(40,0.5,100);//低电量指示灯，可选择蜂鸣器
            }
        }
    }
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
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;                  //连续转换
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
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
    Calibrattion_Val = Get_CalibrationValue(ADC1);

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

/*********************************************************************
 * @fn      Get_ConversionVal
 *
 * @brief   采样值校准
 *          测量电池电压，默认分压比为11，故测量电压不要超过3.3V*11=36.6V，若想测更大的电压，调整板子上分压电阻阻值即可
 * @param   val - Sampling value
 *
 * @return  val+Calibrattion_Val - Conversion Value.
 */
float Get_ConversionVal(s16 val)
{
    float voltage;
    if ((val + Calibrattion_Val) < 0)
        val = 0;
    else if ((val + Calibrattion_Val) > 4095 || val == 4095)
        val = 4095;
    else
        val = val + Calibrattion_Val;
    voltage = (val * 3.3f) / 4095.0f;
    return voltage;
}


