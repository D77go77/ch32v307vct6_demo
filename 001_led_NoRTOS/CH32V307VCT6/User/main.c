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
    SystemCoreClockUpdate();                            //systim_init
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);     //Nvic_init
	USART_Printf_Init(115200);	                        //usart_init
    printf("SystemClk:%d\r\n",SystemCoreClock);         //usart_test
    printf( "ChipID:%08x\r\n", DBGMCU_GetCHIPID() );    //usart_test
    GPIO_Toggle_INIT();                                 //gpio_init
    Delay_Init();                                       //delay_init
    SYSTICK_Init_Config((SystemCoreClock-1)/100);       //systim_interrupt_init
    scheduler_init();                                   //scheduler_init
	while(1)
    {
	    scheduler_run();
	}
}

