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
	test_esp_ok();
	//test_oled();
	//test_message_timer();
}/*End of function Test_program*/

/** @brief Test_display, print something on the display
@author  Daniel Gripenstedt
@return void */
void test_display()
{

}/*End of function test_display*/


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
	/*while(1)
	{
		BSP_LCD_GLASS_DisplayString(buffer2);
		HAL_Delay(500);
		BSP_LCD_GLASS_ScrollSentence(buffer, 2, 400);
		HAL_Delay(1000);
	}*/
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
 * over UART4
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

/** @brief test_wifi, test wifi functions
@author  Daniel Gripenstedt
@return void */
void test_wifi()
{
	BSP_LCD_GLASS_Init();
	/*uint8_t TX_RST [] = "AT+RST\r\n";	//reset esp
	uint8_t RX_RST [20];
	HAL_UART_Transmit(&huart4, (uint8_t*)TX_RST, (sizeof (TX_RST) - 1), 10000);
	HAL_UART_Receive(&huart4, (uint8_t*)RX_RST, 20, 10000);
	HAL_Delay(10000);*/
	//HAL_Delay(5000);
	uint8_t TX_buffer [] = "AT\r\n";	//test if esp is working
	uint8_t RX_buffer [40];
	HAL_UART_Transmit(&huart4, (uint8_t*)TX_buffer, (sizeof(TX_buffer) - 1), 1000);
	HAL_UART_Receive(&huart4, (uint8_t*)RX_buffer, 40, 1000);
	//connect_WIFI();
	//uint8_t *esp_IP = get_IP();
	//esp_as_server();
	/*uint8_t TX_IP_OF [] = "AT+CIFSR\r\n";	//ip adress of esp
	uint8_t RX_IP_OF [200];
	HAL_UART_Transmit(&huart4, (uint8_t*)TX_IP_OF, (sizeof (TX_IP_OF) - 1), 50);
	HAL_UART_Receive(&huart4, (uint8_t*)RX_IP_OF, 100, 50);
	HAL_Delay(100);*/
	/*while(1)
	{
		esp_as_TCP();
		HAL_Delay(5000);
	}*/
	while(1)
	{
		uint8_t test_array [] = "\r\nRecv 6 bytes\r\n\r\nSEND OK\r\n\r\n+IPD,19:office hours closed04:30\0\0\0K\r\n\r\0\0\0\0\0\0\0\0\003\0\0ÿ\0\0\0\0À~\001 l\nd \0\0\0\0\0\0\0";	//test array
		uint8_t *ptr;
		ptr = test_array;
		get_message(ptr, sizeof(test_array));
	}
}/*End of function test_wifi*/

/** @brief test_tcp, set up a tcp connection
 * 		and make a http get request
@author  Daniel Gripenstedt
@return void */
void test_tcp()
{
	/*uint8_t TX_RST [] = "AT+RST\r\n";	//reset esp
	uint8_t RX_RST [20];
	HAL_UART_Transmit(&huart4, (uint8_t*)TX_RST, (sizeof TX_RST) - 1, 1000);
	HAL_UART_Receive(&huart4, (uint8_t*)RX_RST, 20, 10000);
	HAL_Delay(1000);*/
	uint8_t TX_buffer [] = "AT\r\n";	//test if esp is working
	uint8_t RX_buffer [40];
	HAL_UART_Transmit(&huart4, (uint8_t*)TX_buffer, (sizeof TX_buffer) - 1, 1000);
	HAL_UART_Receive(&huart4, (uint8_t*)RX_buffer, 40, 1000);
	HAL_Delay(50);
	connect_WIFI();
	int8_t TX_TCP [] = {'A', 'T' , '+' , 'C', 'I', 'P', 'S' , 'T', 'A', 'R', 'T', '=', '"', 'T', 'C', 'P', '"', ',', '"', 'w', 'w', 'w', '.', 'g', 'o', 'o', 'g', 'l', 'e', '.', 'c', 'o' ,'m', '"', ',', '8', '0', '\r', '\n'};	//reset esp
	uint8_t RX_TCP [300];
	HAL_UART_Transmit(&huart4, (uint8_t*)TX_TCP, (sizeof TX_TCP), 1000);
	HAL_UART_Receive(&huart4, (uint8_t*)RX_TCP, 300, 10000);

	uint8_t TX_SEND [] = "AT+CIPSEND=52\r\n";
	uint8_t TX_M [] = "GET /index.html HTTP/1.1\n";
	uint8_t TX_M2[] ="Host: www.google.com\n";
	uint8_t RX_M [300];
	uint8_t RX_SEND [300];
	HAL_UART_Transmit(&huart4, (uint8_t*)TX_SEND, (sizeof TX_SEND) - 1, 10000);
	HAL_Delay(5000);
	HAL_UART_Transmit(&huart4, (uint8_t*)TX_M, (sizeof TX_M) - 1, 1000);
	HAL_Delay(5000);
	HAL_UART_Transmit(&huart4, (uint8_t*)TX_M2, (sizeof TX_M2) - 1, 1000);
	HAL_UART_Receive(&huart4, (uint8_t*)RX_SEND, 300, 10000);
	HAL_Delay(5000);
	HAL_UART_Receive(&huart4, (uint8_t*)RX_M, 300, 10000);
	HAL_Delay(5000);
	uint8_t TX_END_TCP [] = "AT+CIPCLOSE";
	uint8_t RX_END_TCP [100];
	HAL_UART_Transmit(&huart4, (uint8_t*)TX_END_TCP, (sizeof TX_END_TCP) - 1, 1000);
	HAL_UART_Receive(&huart4, (uint8_t*)RX_END_TCP, 100, 10000);

	while(1){};
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
	//uint time_buffer[7];
	//time_buffer[2] =':';
	//time_buffer[5] = ':';

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
@author  Daniel Gripenstedt
@return void */
void test_print_oled_message()
{
	ssd1306_Init();
	ssd1306_Fill(Black);
	HAL_Delay(1000);
	while(1)
	{
		uint8_t message_array [] = "\r\nRecv 6 bytes\r\n\r\nSEND OK\r\n\r\n+IPD,19:JAS-GRIPEN is the strongest and coolest man on this planet\0\0\0K\r\n\r\0\0\0\0\0\0\0\0\003\0\0ÿ\0\0\0\0À~\001 l\nd \0\0\0\0\0\0\0";
		ssd1306_Fill(Black);
		ssd1306_UpdateScreen();
		HAL_Delay(1000);
		print_oled_message(&message_array, sizeof(message_array));
	}
}/*End of test_print_oled_message*/

/** @brief test_esp_ok, print OK if a string has OK
 * otherwise print ERROR
@author  Daniel Gripenstedt
@return void */
void test_esp_ok()
{
	BSP_LCD_GLASS_Init();
	HAL_Delay(10000);	//wait for ESP to start
	ssd1306_Init();
	ssd1306_Fill(Black);
	while(1)
	{
		if (esp_ok() == true)
		{
			ssd1306_Fill(Black);
			ssd1306_UpdateScreen();
			ssd1306_SetCursor(2, 26);
			ssd1306_WriteString("OK", Font_16x26, White);
			ssd1306_UpdateScreen();
		}
		if(esp_ok() == false)
		{
			ssd1306_Fill(Black);
			ssd1306_UpdateScreen();
			ssd1306_SetCursor(2, 26);
			ssd1306_WriteString("ERROR", Font_16x26, White);
			ssd1306_UpdateScreen();
		}
		HAL_Delay(5000);
	}
}/*End of test_esp_ok*/

/** @brief find_ok
 * otherwise print ERROR
@author  Daniel Gripenstedt
@return void */
/*void test_find_ok()
{
	BSP_LCD_GLASS_Init();
	while(1)
	{
		uint8_t message_array [] = "\r\nRecv 6 bytes\r\n\r\nSEND OK\r\n\r\n+IPD,19:office hours closed04:30\0\0\0K\r\n\r\0\0\0\0\0\0\0\0\003\0\0ÿ\0\0\0\0À~\001 l\nd \0\0\0\0\0\0\0";
		test_find_ok(&message_array, sizeof(message_array)); //not created yet

	}
}End of find_ok*/

/** @brief test_oled, run the test all function
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
	   //ssd1306_SetCursor(2, 26);
	    //ssd1306_WriteString(cbuff, Font_16x26, White);
	   // ssd1306_SetCursor(2, 26);
	   // ssd1306_WriteString("Hello there", Font_11x18, White);
	   // ssd1306_SetCursor(2, 26+18);
	    //ssd1306_WriteString("Hello there", Font_7x10, White);
	    //ssd1306_SetCursor(2, 26+18+10);
		ssd1306_SetCursor(2, 2);
	    ssd1306_WriteString(cbuff, Font_6x8, White);
	    ssd1306_UpdateScreen();
}/*End of function test_oled*/

/** @brief test_message_timer, test message timer function
 * otherwise print ERROR
@author  Daniel Gripenstedt */
void test_message_timer()
{
	ssd1306_Init();
	ssd1306_Fill(Black);
	HAL_RTC_GetTime(&hrtc,&sTime,RTC_FORMAT_BIN);
	HAL_RTC_GetDate(&hrtc,&sDate,RTC_FORMAT_BIN);
	//uint8_t hour = sTime.Hours;
	//uint8_t minute = sTime.Minutes;
	uint8_t prev_second = sTime.Seconds;
	uint8_t count = 0;
	char cbuff [2];

	while(1)
	{
		if (message_timer(sTime.Seconds, prev_second) == true)
		{
			ssd1306_Fill(Black);
			ssd1306_UpdateScreen();
			count++;
			sprintf(cbuff, count);
			ssd1306_SetCursor(2, 2);
			ssd1306_WriteString(cbuff, Font_6x8, White);
			ssd1306_UpdateScreen();
			cbuff[0] = '/0';
			cbuff[1] = '/0';
		}

		HAL_RTC_GetTime(&hrtc,&sTime,RTC_FORMAT_BIN);
		HAL_RTC_GetDate(&hrtc,&sDate,RTC_FORMAT_BIN);

		prev_second = sTime.Seconds;
	}


}/*End of function test_message_timer*/
