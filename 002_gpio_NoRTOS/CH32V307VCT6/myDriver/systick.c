/*
 * systick.c
 *
 *  Created on: 2024Äê12ÔÂ21ÈÕ
 *      Author: 19816
 */

#include "systick.h"

uint32_t tickTime = 0;
/*********************************************************************
 * @fn      SYSTICK_Init_Config
 *
 * @brief   SYSTICK_Init_Config.
 *
 * @return  none
 */
void SYSTICK_Init_Config(u_int64_t ticks)
{
    SysTick->SR &= ~(1 << 0);//clear State flag
    SysTick->CMP = ticks;
    SysTick->CNT = 0;
    SysTick->CTLR = 0xF;

    NVIC_SetPriority(SysTicK_IRQn, 15);
    NVIC_EnableIRQ(SysTicK_IRQn);
}


void SysTick_Handler(void) __attribute__((interrupt("WCH-Interrupt-fast")));
/*********************************************************************
 * @fn      SysTick_Handler
 *
 * @brief   SysTick_Handler.
 *
 * @return  none
 */
void SysTick_Handler(void)
{
    if(SysTick->SR == 1)//10ms
    {
        SysTick->SR = 0;//clear State flag
        tickTime++;//systim_time
        //printf("hello\r\n");
    }
}
