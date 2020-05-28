#include "test.h"
#include "stm32l4xx_hal.h"
#include <stdio.h>
#include "lcd.h"
#include "usart.h"
#include "rtc.h"
#include <stdbool.h>
#include "ssd1306_fonts.h"
#include "ssd1306.h"

/** @brief project, the main program, get a message from
* a TCP server every minute and print it on a display
* a button will show a QR-code that leads to a website
* where messages can be left
@author  Daniel Gripenstedt*/
void project()
{
	/*initiate stuff*/
	BSP_LCD_GLASS_Init();
	BSP_LED_Init(LED4);
	BSP_LED_Init(LED5);
	ssd1306_Init();
	HAL_Delay(1000);
	uint8_t TX_IP_OF [] = "AT+CIFSR\r\n";	//ip adress of esp
	static RTC_TimeTypeDef sTime;
	static RTC_DateTypeDef sDate;
	uint8_t prev_second;
	uint8_t second_count = 60;	//counter varible for how many seconds has pasted since the last message
	const uint8_t TIME_INTERVAL = 60;
	const uint8_t QR_DELAY = 10;
	uint8_t value = 0xff;

	HAL_Delay(1000);
	//if (esp_find_ok(&TX_IP_OF, sizeof(TX_IP_OF)) == false)
	if (esp_ok() == false)
	{
		esp_error_handler();	//handle esp error
	}
	//connect_WIFI();	//connect esp to router via wifi, remove comment if the ESP is not already connected. The ESP will remember the network

	/*set up the time*/
	HAL_RTC_GetTime(&hrtc,&sTime,RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc,&sDate,RTC_FORMAT_BIN);

	while(1) //super loop
	{
		if (message_timer(sTime.Seconds, prev_second) == true)	//if a second has passed, increment second_count
		{
			second_count++;
		}

		if (second_count >= TIME_INTERVAL)	//if 5 or more seconds has passed, request a new message and display it on the OLED
		{
			if (esp_ok() == false)
			{
				esp_error_handler();	//handle esp error
			}

			second_count = 0;
			esp_as_TCP();
		}

		prev_second = sTime.Seconds;
		HAL_RTC_GetTime(&hrtc,&sTime,RTC_FORMAT_BIN);
		HAL_RTC_GetDate(&hrtc,&sDate,RTC_FORMAT_BIN);

		if (HAL_GPIO_ReadPin (GPIOA, GPIO_PIN_3) == 1)
		{
			second_count = 0;
			HAL_Delay(300);
			menu_QR();
			while(1)
				{
				value = value - 4;
				ssd1306_WriteCommand(0x81);
				ssd1306_WriteCommand(value);
				HAL_Delay(100);
					if (HAL_GPIO_ReadPin (GPIOA, GPIO_PIN_3) == 1) {
						value = 0xff;
					ssd1306_WriteCommand(0x81);
					ssd1306_WriteCommand(value);
					break;
					}
					if (message_timer(sTime.Seconds, prev_second) == true)	//if a second has passed, increment second_count
							{
								second_count++;
							}

							if (second_count >= QR_DELAY )	//if 5 or more seconds has passed, request a new message and display it on the OLED
							{
								value = 0xff;
								ssd1306_WriteCommand(0x81);
								ssd1306_WriteCommand(value);
								break;
							}

					prev_second = sTime.Seconds;
					HAL_RTC_GetTime(&hrtc,&sTime,RTC_FORMAT_BIN);
					HAL_RTC_GetDate(&hrtc,&sDate,RTC_FORMAT_BIN);
				}
			if (esp_ok() == false)
			{
				esp_error_handler();	//handle esp error
			}
			ssd1306_Fill(Black); //reset screen
			ssd1306_SetCursor(2, 12);
			ssd1306_WriteString("Loading old" , Font_7x10, White);
			ssd1306_SetCursor(2, 22);
			ssd1306_WriteString("message" , Font_7x10, White);
			ssd1306_UpdateScreen();
			second_count = 0;
			esp_as_TCP();
		}
	}
}/*End of function project*/
