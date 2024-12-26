/*
 * ui.c
 *
 *  Created on: 2024年12月26日
 *      Author: 19816
 */
#include "lcd.h"
void LcdSprintf(uint8_t Line, uint32_t fColour,uint32_t BColour,char *format,...);
/*********************************************************************
 * @fn      task_lcd_proc
 *
 * @brief   LCD任务函数
 *
 * @return  none
 */
u8 page_number = 1;
void task_lcd_proc(void)
{

    switch(page_number)
    {
        case 1:
        {
            LcdSprintf(0,BLUE,BLACK,"Digital Freq Meter");
            LcdSprintf(1,GREEN,BLACK,"Frequency  Is  :");
            LcdSprintf(2,GREEN,BLACK,"HZ: %.1f ",frequency);
            LcdSprintf(7,YELLOW,BLACK,"page_num :      %d",page_number);
        }break;
        case 2:
        {
            LcdSprintf(0,BLUE,BLACK,"  RTC-time  ");
            LcdSprintf(1,GREEN,BLACK,"Year  : %02d",calendar.w_year);
            LcdSprintf(2,GREEN,BLACK,"Month : %02d",calendar.w_month);
            LcdSprintf(3,GREEN,BLACK,"Date  : %02d",calendar.w_date);
            LcdSprintf(4,GREEN,BLACK,"Hour  : %02d",calendar.hour);
            LcdSprintf(5,GREEN,BLACK,"Min   : %02d",calendar.min);
            LcdSprintf(6,GREEN,BLACK,"Sec   : %02d",calendar.sec);
            LcdSprintf(7,YELLOW,BLACK,"page_num :      %d",page_number);
        }break;
        case 3:
        {
            LcdSprintf(0,BLUE,BLACK,"Digital Freq Meter");
            LcdSprintf(1,GREEN,BLACK,"Frequency  Is  :");
            LcdSprintf(2,GREEN,BLACK,"HZ: %.1f ",frequency);
            LcdSprintf(7,YELLOW,BLACK,"page_num :      %d",page_number);
        }break;
        case 4:
        {
            LcdSprintf(0,BLUE,BLACK,"  CH32V307VCT6  ");
            LcdSprintf(1,BLUE,BLACK,"  MPU6050  ");
//            LcdSprintf(2,GREEN,BLACK,"ROL : %5.3f",smartcar_imu.rpy_deg[ROL]);
//            LcdSprintf(3,GREEN,BLACK,"PIT : %5.3f",smartcar_imu.rpy_deg[PIT]);
//            LcdSprintf(4,GREEN,BLACK,"YAW : %5.3f",smartcar_imu.rpy_deg[YAW]);
//            LcdSprintf(5,GREEN,BLACK,"TEM : %5.3f",smartcar_imu.temperature_filter);
            LcdSprintf(6,GREEN,BLACK,"ADC : %5.2f",vbat.value);
            LcdSprintf(7,YELLOW,BLACK,"page_num :      %d",page_number);
        }break;
    }
    //LCD_Fill(0,0,LCD_W,LCD_H,BLACK);//rest lcd
}
