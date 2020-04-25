#include "test.h"
#include "stm32l4xx_hal.h"
#include <stdio.h>
#include "lcd.h"
#include "usart.h"
#include "rtc.h"
#include <stdbool.h>
#include "ssd1306_fonts.h"
#include "ssd1306.h"
static RTC_TimeTypeDef sTime;
static RTC_DateTypeDef sDate;

/** @brief project, the main program
@author  Daniel Gripenstedt*/
void project()
{
	/*initiate stuff*/
	BSP_LCD_GLASS_Init();
	BSP_LED_Init(LED4);
	BSP_LED_Init(LED5);
	ssd1306_Init();

	connect_WIFI();	//connect esp to router via wifi

	/*set up the time*/
	HAL_RTC_GetTime(&hrtc,&sTime,RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc,&sDate,RTC_FORMAT_BIN);
	/*uint8_t hour = sTime.Hours;
	uint8_t minute = sTime.Minutes;
	uint8_t second = sTime.Seconds;*/

	uint8_t prev_second;

	uint8_t second_count = 0;	//counter varible for how many seconds has pasted since the last message

	while(1) //super loop
	{
		if (message_timer(sTime.Seconds, prev_second) == true)	//if a second has passed, increment second_count
		{
			second_count++;
		}

		if (second_count >= 5)	//if 5 or more seconds has passed, request a new message and display it on the OLED
		{
			esp_as_TCP();
			second_count = 0;

			if (esp_ok() == false)
			{
				esp_error_handler();	//handle esp error
			}
		}

		prev_second = sTime.Seconds;
		HAL_RTC_GetTime(&hrtc,&sTime,RTC_FORMAT_BIN);
		HAL_RTC_GetDate(&hrtc,&sDate,RTC_FORMAT_BIN);

	}
}/*End of function project*/
