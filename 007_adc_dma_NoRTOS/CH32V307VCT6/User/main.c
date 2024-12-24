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
 USART Print debugging routine:
 USART1_Tx(PA9).
 This example demonstrates using USART1(PA9) as a print debug port output.

*/

#include "debug.h"
#include "../myApp/common_inc.h"


/* Global typedef */

/* Global define */

/* Global Variable */


/*********************************************************************
 * @fn      main
 *
 * @brief   Main program.
 *
 * @return  none
 */
int main(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);     //Nvic_init
	SystemCoreClockUpdate();                            //systim_init
	Delay_Init();                                       //delay_init
	USART_Printf_Init(115200);	                        //usart_init
    printf("SystemClk:%d\r\n",SystemCoreClock);         //usart_test
    printf( "ChipID:%08x\r\n", DBGMCU_GetCHIPID() );    //usart_test
    GPIOx_INIT();                                       //gpio_init
    /* my_init start */
    nGpio_init();                                       //led_init
    nKey_init();                                        //key_init
    nMpu6050_init();                                    //mpu6050_init
    nAdc_init();                                        //adc_dma_init
    //OLED_Init();                                        //oled_init
    LCD_Init();                                         //lcd_init
    /* my_init end */
    SYSTICK_Init_Config(SystemCoreClock/1000-1);        //systim_interrupt_init//1ms
    scheduler_init();                                   //scheduler_init
	while(1)
    {
	    scheduler_run();
	}
}












