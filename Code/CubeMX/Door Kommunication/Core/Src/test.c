/*******************************************************************************
  * @file           : test.c
  * @brief          : Test program for the main program. This code will test
  * 				  the different program functions. Selecting one function
  * 				  is done by commenting out the others.
  ******************************************************************************
  * @author	Daniel Gripenstedt
  ******************************************************************************
  */

#include "test.h"
#include "stm32l4xx_hal.h"
#include <stdio.h>
#include "lcd.h"
#include "usart.h"
#include "rtc.h"
#include "ssd1306_fonts.h"
#include "ssd1306.h"
#include <stdbool.h>
#include "display_test.h"
#include "functions_menu.h"
static RTC_TimeTypeDef sTime;
static RTC_DateTypeDef sDate;
/** @brief Test_program, test functions to be used in the project
 * and some extra functions to better understand how different commands
 * and hardware works.
@author  Daniel Gripenstedt
@return void */
void Test_program(void)
{
	//test_led();
	//test_LCD();
	//test_UART();
	//test_wifi();
	//test_tcp();
	//test_clock();
	//test_print_oled_message();
	//test_esp_ok();
	//test_oled();
	//test_message_timer();
	//test_systemReset();
	//test_esp_error_handler();
	//test_menu();
	test_button();
}/*End of function Test_program*/


/** @brief test_led, turn on LED4 and LED5
@author  Daniel Gripenstedt
@return void */
void test_led()
{
	BSP_LED_Init(LED4);
	BSP_LED_Init(LED5);
	while(1)
	{
		/* HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_SET);	//turn on LED4
		 HAL_Delay(500);
		 HAL_GPIO_WritePin(GPIOB, GPIO_PIN_2, GPIO_PIN_RESET);	//turn off LED4
		 HAL_Delay(500);*/

		BSP_LED_Toggle(LED4);
		HAL_Delay(250);
		BSP_LED_Toggle(LED5);

	}
}/*End of function test_led*/

/** @brief test_LCD, display something on the LCD
@author  Daniel Gripenstedt
@return void */
void test_LCD()
{
	char buffer[50];
	sprintf(buffer, "DANNE IS EPIC ");
	char buffer2[50];
	sprintf(buffer2, "Yao");
	BSP_LCD_GLASS_Init();

	BSP_LCD_GLASS_DisplayBar(LCD_BAR_0);
	HAL_Delay(300);
	BSP_LCD_GLASS_ClearBar(LCD_BAR_0);
	BSP_LCD_GLASS_DisplayBar(LCD_BAR_1);
	HAL_Delay(300);
	BSP_LCD_GLASS_ClearBar(LCD_BAR_1);
	BSP_LCD_GLASS_DisplayBar(LCD_BAR_2);
	HAL_Delay(300);
	BSP_LCD_GLASS_ClearBar(LCD_BAR_2);
	BSP_LCD_GLASS_DisplayBar(LCD_BAR_3);
	HAL_Delay(300);
	BSP_LCD_GLASS_ClearBar(LCD_BAR_3);
	HAL_Delay(300);
	BSP_LCD_GLASS_BarLevelConfig(BATTERYLEVEL_OFF);
	HAL_Delay(300);
	BSP_LCD_GLASS_BarLevelConfig(BATTERYLEVEL_1_4);
	HAL_Delay(300);
	BSP_LCD_GLASS_BarLevelConfig(BATTERYLEVEL_1_2);
	HAL_Delay(300);
	BSP_LCD_GLASS_BarLevelConfig(BATTERYLEVEL_3_4);
	HAL_Delay(300);
	BSP_LCD_GLASS_BarLevelConfig(BATTERYLEVEL_FULL);
	HAL_Delay(300);
	BSP_LCD_GLASS_BlinkConfig(LCD_BLINKMODE_ALLSEG_ALLCOM, LCD_BLINKFREQUENCY_DIV512);
	HAL_Delay(2000);
	BSP_LCD_GLASS_Clear();
	BSP_LCD_GLASS_BlinkConfig(LCD_BLINKMODE_OFF, LCD_BLINKFREQUENCY_DIV512);
	BSP_LCD_GLASS_Contrast(LCD_CONTRASTLEVEL_7);
	BSP_LCD_GLASS_ScrollSentence((uint8_t *)"      SET CONTRAST MAX", 1, SCROLL_SPEED_MEDIUM);
	HAL_Delay(1000);
	BSP_LCD_GLASS_Contrast(LCD_CONTRASTLEVEL_0);
	BSP_LCD_GLASS_ScrollSentence((uint8_t *)"      SET CONTRAST MIN", 1, SCROLL_SPEED_MEDIUM);
	HAL_Delay(1000);
}/*End of function test_LCD*/

/** @brief test_UART, send an AT command to the WIFI module
 * over UART4 and print response on the LCD display
@author  Daniel Gripenstedt
@return void */
void test_UART()
{
	BSP_LCD_GLASS_Init();
	uint8_t TX_buffer [] = "ATE\r\n";
	uint8_t TX_buffer2 [] ="AT+SYSRAM?\r\n";
	while(1)
	{
		uint8_t RX_buffer [20];
		uint8_t RX_buffer2 [100];
		HAL_UART_Transmit(&huart4, (uint8_t*)TX_buffer, 5, 1000);
		HAL_UART_Receive(&huart4, (uint8_t*)RX_buffer, 20, 1000);
		BSP_LCD_GLASS_ScrollSentence(RX_buffer, 1, SCROLL_SPEED_MEDIUM);
		HAL_UART_Transmit(&huart4, (uint8_t*)TX_buffer2, 12, 1000);
		HAL_UART_Receive(&huart4, (uint8_t*)RX_buffer2, 100, 1000);

		BSP_LCD_GLASS_ScrollSentence(RX_buffer2, 1, SCROLL_SPEED_MEDIUM);
		HAL_Delay(1000);
	}
}/*End of function test_UART*/

/** @brief test_usart_error_handler, error handler for the test of USART
@author  Daniel Gripenstedt
@return void */
void test_usart_error_handler()
{
	BSP_LCD_GLASS_ScrollSentence((uint8_t *)"      USART ERROR", 2, SCROLL_SPEED_MEDIUM);
	HAL_Delay(2000);
}/*End of function test_usart_error_handler*/

/** @brief test_wifi, connect to wifi
 * then check the ip adress of ESP
@author  Daniel Gripenstedt
@return void */
void test_wifi()
{
	BSP_LCD_GLASS_Init();
	uint8_t TX_buffer [] = "AT\r\n";	//test if esp is working
	uint8_t RX_buffer [40];
	HAL_UART_Transmit(&huart4, (uint8_t*)TX_buffer, (sizeof(TX_buffer) - 1), 1000);
	HAL_UART_Receive(&huart4, (uint8_t*)RX_buffer, 40, 1000);
	connect_WIFI();
	uint8_t TX_IP_OF [] = "AT+CIFSR\r\n";	//ip adress of esp
	static uint8_t RX_IP_OF [100];
	HAL_UART_Transmit(&huart4, (uint8_t*)TX_IP_OF, (sizeof TX_IP_OF) - 1, 50);
	HAL_UART_Receive(&huart4, (uint8_t*)RX_IP_OF, 100, 50);
}/*End of function test_wifi*/

/** @brief test_tcp, set up a tcp connection
 * 		get and print a message on the OLED
 * 		display
@author  Daniel Gripenstedt
@return void */
void test_tcp()
{
	ssd1306_Init();
	connect_WIFI();
	esp_as_tcp();
}/*End of function test_tcp*/

/** @brief test_clock, alternate LED4 and LED5
 * every second
@author  Daniel Gripenstedt
@return void */
void test_clock()
{
	BSP_LED_Init(LED4);
	BSP_LED_Init(LED5);
	BSP_LED_Toggle(LED4);
	BSP_LCD_GLASS_Init();
	HAL_RTC_GetTime(&hrtc,&sTime,RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc,&sDate,RTC_FORMAT_BIN);
	uint8_t hour = sTime.Hours;
	uint8_t minute = sTime.Minutes;
	uint8_t second = sTime.Seconds;

	while(1)
	{
		if(second != sTime.Seconds)	//fix bug where sTime.Hours get the value 24, reset back to 00:00:00
		{
			second = sTime.Seconds;
			BSP_LED_Toggle(LED4);
			BSP_LED_Toggle(LED5);
			if (second >= 10) {Large_number(second);}
			else{uint8_t time_buff = second; BSP_LCD_GLASS_DisplayString(time_buff);}
		}

		HAL_RTC_GetTime(&hrtc,&sTime,RTC_FORMAT_BIN);
		HAL_RTC_GetDate(&hrtc,&sDate,RTC_FORMAT_BIN);
	}
}/*End of function test_clock*/

/** @brief test_print_oled_message, test print_oled_message
 * by sending an array with content similar to what is expected to
 * be received from the TCP server
@author  Daniel Gripenstedt
@return void */
void test_print_oled_message()
{
	ssd1306_Init();
	ssd1306_Fill(Black);
	HAL_Delay(1000);
	while(1)
	{
		//__HAL_IWDG_RELOAD_COUNTER(&hiwdg);
		uint8_t message_array [] = "\r\nRecv 6 bytes\r\n\r\nSEND OK\r\n\r\n+IPD,19:CURRENTLY OUT, WILL BE BACK AT 15:00\0\0\0K\r\n\r\0\0\0\0\0\0\0\0\003\0\0ÿ\0\0\0\0À~\001 l\nd \0\0\0\0\0\0\0";
		ssd1306_Fill(Black);
		ssd1306_UpdateScreen();
		print_oled_message(&message_array, sizeof(message_array));
		HAL_Delay(5000);
	}
}/*End of test_print_oled_message*/

/** @brief test_esp_ok, print OK if a string has OK
 * otherwise go to esp_error_handler
@author  Daniel Gripenstedt
@return void */
void test_esp_ok()
{
	BSP_LCD_GLASS_Init();
	HAL_Delay(1000);	//wait for ESP to start
	ssd1306_Init();
	ssd1306_Fill(Black);
	uint8_t TX_buffer [] = "AT\r\n";	//test if esp is working
	uint8_t TX_IP_OF [] = "AT+CIFSR\r\n";	//ip adress of esp
	while(1)
	{
		if (esp_ok(&TX_buffer, sizeof(TX_buffer)) == true)
		{
			ssd1306_Fill(Black);
			ssd1306_UpdateScreen();
			ssd1306_SetCursor(2, 26);
			ssd1306_WriteString("OK", Font_16x26, White);
			ssd1306_UpdateScreen();
		}

		HAL_Delay(5000);

		if(esp_ok(&TX_IP_OF, sizeof(TX_IP_OF)) == false)
		{
			esp_error_handler();
		}

		HAL_Delay(5000);
	}
}/*End of test_esp_ok*/

/** @brief test_oled, run the test, test all function
 * of the OLED
@author  Daniel Gripenstedt
@return void */
void test_oled()
{
	uint8_t buffer[] = "Hello there";
	char cbuff [15];
	sprintf(cbuff, buffer);
	ssd1306_Init();
	ssd1306_Fill(Black);
	ssd1306_SetCursor(2, 26);
	ssd1306_WriteString(cbuff, Font_16x26, White);
	ssd1306_SetCursor(2, 26);
	ssd1306_WriteString("Hello there", Font_11x18, White);
	ssd1306_SetCursor(2, 26+18);
	ssd1306_WriteString("Hello there", Font_7x10, White);
	ssd1306_SetCursor(2, 26+18+10);
	ssd1306_SetCursor(2, 2);
	ssd1306_WriteString(cbuff, Font_6x8, White);
	ssd1306_UpdateScreen();
}/*End of function test_oled*/

/** @brief test_message_timer, test message timer function
 * by toggeling LEDs
@author  Daniel Gripenstedt */
void test_message_timer()
{
	BSP_LED_Init(LED4);
	BSP_LED_Init(LED5);
	uint8_t prev_second;
	HAL_RTC_GetTime(&hrtc,&sTime,RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc,&sDate,RTC_FORMAT_BIN);

	while(1)
	{
		if (message_timer(sTime.Seconds, prev_second) == true)
		{
			BSP_LED_Toggle(LED4);
			BSP_LED_Toggle(LED5);
		}

		prev_second = sTime.Seconds;
		HAL_RTC_GetTime(&hrtc,&sTime,RTC_FORMAT_BIN);
		HAL_RTC_GetDate(&hrtc,&sDate,RTC_FORMAT_BIN);

	}
}/*End of function test_message_timer*/

/** @brief test_systemReset, test the function HAL_NVIC_SystemReset()
@author  Daniel Gripenstedt */
void test_systemReset()
{
	BSP_LED_Init(LED4);
	BSP_LED_Init(LED5);
	BSP_LED_Toggle(LED4);

	HAL_Delay(2000);
	BSP_LED_Toggle(LED5);
	BSP_LED_Toggle(LED4);
	HAL_Delay(2000);

	HAL_NVIC_SystemReset();
}/*End of function test_systemReset*/

/** @brief test_esp_error_handler, test the esp error handler
@author  Daniel Gripenstedt */
void test_esp_error_handler()
{
	ssd1306_Init();
	ssd1306_Fill(Black);

	esp_error_handler();
}/*End of function test_esp_error_handler*/

/** @brief test_button, test the added pushbutton by
 * toggeling  two LED:s
@author  Daniel Gripenstedt */
void test_button()
{
	BSP_LED_Init(LED4);
		BSP_LED_Init(LED5);
		BSP_LED_Toggle(LED4);
		BSP_LED_Toggle(LED5);
		while(1)
		{
			if (HAL_GPIO_ReadPin (GPIOA, GPIO_PIN_3) == 1)
			{
				HAL_Delay(300);
				BSP_LED_Toggle(LED4);
				BSP_LED_Toggle(LED5);
			}
		}
}/*End of function test_button*/
