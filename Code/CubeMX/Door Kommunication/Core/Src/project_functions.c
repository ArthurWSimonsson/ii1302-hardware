/*******************************************************************************
  * @file           : project_functions.c
  * @brief          : This file contains the functions for the project
  *
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
#include <stdbool.h>
#include "ssd1306_fonts.h"
#include "ssd1306.h"
//static RTC_TimeTypeDef sTime;
//static RTC_DateTypeDef sDate;

/** @brief connect_WIFI, conect to wifi
@author  Daniel Gripenstedt
@return void */
void connect_WIFI()
{
	/*uint8_t TX_RST [] = "AT+RST\r\n";	//reset esp
	uint8_t RX_RST [20];
	HAL_UART_Transmit(&huart4, (uint8_t*)TX_RST, (sizeof (TX_RST) - 1), 10000);
	HAL_UART_Receive(&huart4, (uint8_t*)RX_RST, 20, 10000);
	HAL_Delay(1000);*/

	uint8_t TX_buffer [] = "AT\r\n";	//test if esp is working
	uint8_t RX_buffer [20];
	HAL_UART_Transmit(&huart4, (uint8_t*)TX_buffer, (sizeof (TX_buffer) - 1), 50);
	HAL_UART_Receive(&huart4, (uint8_t*)RX_buffer, 20, 50);

	uint8_t TX_STATION [] = "AT+CWMODE=3\r\n";	//enter station mode
	uint8_t RX_STATION [20];
	HAL_UART_Transmit(&huart4, (uint8_t*)TX_STATION, (sizeof (TX_STATION) - 1), 50);
	HAL_UART_Receive(&huart4, (uint8_t*)RX_STATION, 20, 50);

	uint8_t TX_ASK_MODE [] = "AT+CWMODE?\r\n";	//check which mode
	uint8_t RX_ASK_MODE [40];
	HAL_UART_Transmit(&huart4, (uint8_t*)TX_ASK_MODE, (sizeof (TX_ASK_MODE) - 1), 50);
	HAL_UART_Receive(&huart4, (uint8_t*)RX_ASK_MODE, (sizeof (RX_ASK_MODE) - 1), 50);

	/*int8_t TX_LIST_AP [] = "AT+CWLAP\r\n";	//list AP:s
	uint8_t RX_LIST_AP [1000];
	HAL_UART_Transmit(&huart4, (uint8_t*)TX_LIST_AP, (sizeof TX_LIST_AP) - 1, 20000);
	HAL_UART_Receive(&huart4, (uint8_t*)RX_LIST_AP, 1000, 20000);*/

	uint8_t TX_CONNECT_WIFI [] = {"Username and Pasword"};
	uint8_t RX_CONNECTWIFI [100];
	HAL_UART_Transmit(&huart4, (uint8_t*)TX_CONNECT_WIFI, sizeof (TX_CONNECT_WIFI), 1000);
	HAL_UART_Receive(&huart4, (uint8_t*)RX_CONNECTWIFI, 100, 20000);
	HAL_Delay(1000);
}/*End of function connect_WIFI*/

/** @brief esp_as_server, configure esp as a server
@author  Daniel Gripenstedt
@return void */
void esp_as_server()
{
	uint8_t TX_IP_OF [] = "AT+CIFSR\r\n";	//ip adress of esp
	uint8_t RX_IP_OF [100];
	HAL_UART_Transmit(&huart4, (uint8_t*)TX_IP_OF, (sizeof (TX_IP_OF) - 1), 50);
	HAL_UART_Receive(&huart4, (uint8_t*)RX_IP_OF, 100, 50);

	uint8_t TX_EN_CON [] = "AT+CIPMUX=1\r\n";	//enable multiple connections
	uint8_t RX_EN_CON [100];
	HAL_UART_Transmit(&huart4, (uint8_t*)TX_EN_CON, (sizeof (TX_EN_CON) - 1), 50);
	HAL_UART_Receive(&huart4, (uint8_t*)RX_EN_CON, 100, 50);
	HAL_Delay(5000);

	uint8_t TX_START_SERVER [] = "AT+CIPSERVER=1,80\r\n";	//start server on port 80
	uint8_t RX_START_SERVER [100];
	HAL_UART_Transmit(&huart4, (uint8_t*)TX_START_SERVER, (sizeof (TX_START_SERVER) - 1), 50);
	HAL_UART_Receive(&huart4, (uint8_t*)RX_START_SERVER, 100, 50);
	HAL_Delay(5000);

	uint8_t TX_SEND_INIT [] = "AT+CIPSEND=0,5\r\n";	//start server on port 80
	uint8_t RX_RECIVE_SERVER1 [100];
	//HAL_UART_Transmit(&huart4, (uint8_t*)TX_SEND_INIT, (sizeof TX_SEND_INIT) - 1, 500);
	HAL_Delay(1000);
	HAL_UART_Receive(&huart4, (uint8_t*)RX_RECIVE_SERVER1, 200, 10000);


	/*uint8_t TX_SEND_SERVER [] = "hello\n";	//start server on port 80
	uint8_t RX_RECIVE_SERVER [100];
	HAL_UART_Transmit(&huart4, (uint8_t*)TX_SEND_SERVER, (sizeof TX_SEND_SERVER) - 1, 10000);
	HAL_UART_Receive(&huart4, (uint8_t*)RX_RECIVE_SERVER, 100, 10000);
	HAL_Delay(1000);*/

	uint8_t TX_CLOSE_SEND [] = "AT+CIPCLOSE=0\r\n";	//start server on port 80
	uint8_t RX_CLOSE_SEND [100];
	HAL_UART_Transmit(&huart4, (uint8_t*)TX_CLOSE_SEND, (sizeof (TX_CLOSE_SEND) - 1), 5000);
	HAL_UART_Receive(&huart4, (uint8_t*)RX_CLOSE_SEND, 100, 5000);
}/*End of function esp_as_server*/

/** @brief esp_as_TCP, configure esp with a TCP
 * connection to a server
@author  Daniel Gripenstedt, Arthur Simonsson, Botan Cosar
@return void */
void esp_as_TCP()
{
	uint8_t TX_DOMAIN_NAME [] = "AT+CIPSTART=\"TCP\",\"213.114.145.242\",3001\r\n";
	uint8_t RX_DOMAIN_NAME [100];
	HAL_UART_Transmit(&huart4, (uint8_t*)TX_DOMAIN_NAME, sizeof (TX_DOMAIN_NAME), 500);	//set up TCP connection
	HAL_UART_Receive(&huart4, (uint8_t*)RX_DOMAIN_NAME, 100, 5000);

	uint8_t TX_SEND [] = "AT+CIPSEND=9\r\n";
	uint8_t TX_M [] = "welcome\r\n";
	uint8_t RX_SEND [50];
	uint8_t RX_M [200];
	HAL_UART_Transmit(&huart4, (uint8_t*)TX_SEND, (sizeof (TX_SEND) - 1), 1000);	//prepare to send data over TCP
	HAL_UART_Receive(&huart4, (uint8_t*)RX_SEND, 50, 5000);
	HAL_UART_Transmit(&huart4, (uint8_t*)TX_M, (sizeof (TX_M) - 1), 1000);	//Send data over TCP
	HAL_UART_Receive(&huart4, (uint8_t*)RX_M, 200, 5000);

	uint8_t TX_END_TCP [] = "AT+CIPCLOSE\r\n";
	uint8_t RX_END_TCP [60];
	HAL_UART_Transmit(&huart4, (uint8_t*)TX_END_TCP, (sizeof (TX_END_TCP) - 1), 1000);	//Close TCP connection
	HAL_UART_Receive(&huart4, (uint8_t*)RX_END_TCP, 60, 5000);
	HAL_Delay(100);

	print_oled_message(&RX_M, sizeof(RX_M));
}/*End of function esp_as_TCP*/

/** @brief get_IP, get the IP adress of the esp
@author  Daniel Gripenstedt
@return uint8_t RX_IP_OF */
int *get_IP ()
{
	uint8_t TX_IP_OF [] = "AT+CIFSR\r\n";	//ip adress of esp
	static uint8_t RX_IP_OF [100];
	HAL_UART_Transmit(&huart4, (uint8_t*)TX_IP_OF, (sizeof TX_IP_OF) - 1, 50);
	HAL_UART_Receive(&huart4, (uint8_t*)RX_IP_OF, 100, 50);
	return RX_IP_OF;
}/*End of function get_IP*/

/** @brief get_message, get the message from the array
 * returned by the server
@author  Daniel Gripenstedt
@return uint8_t RX_IP_OF */
void print_oled_message (uint8_t *arr, uint8_t size)
{
	/*uint8_t message_array [size - 1];
	for (uint8_t pos = 0; pos < (size - 1); pos++)
	{
		message_array [pos] = *(arr + pos);
	}*/
	uint8_t count = -1;	//how many characters of the message
		uint8_t i;
		for (i = 30; i < (size - 1); i++)	//find number of characters
		{
			if (*(arr + i) == ':') {break;}
		}

		for (uint8_t j = (i + 1); j < (size - 1); j++)	//find number of characters
			{
				count++;
				if (*(arr + j) == '\0') {break;}
			}
		uint8_t message [count];	//new message

		for (uint8_t k = 0; k < sizeof(message); k++)
		{
			message [k] = (*(arr + i + 1));
			i++;
		}

		if (sizeof(message) <= 20)
		{
			char cbuff [20];
			sprintf(cbuff, message);
			ssd1306_SetCursor(2, 2);
			ssd1306_WriteString(cbuff, Font_6x8, White);
			ssd1306_UpdateScreen();
		}
		if ((sizeof(message) > 20) && (sizeof(message) < 40))
		{
			uint8_t m_row1 [20];
			char c_row1 [20];

			for (uint8_t k = 0; k < sizeof(message); k++)
				m_row1[k] = (message[k]);
			sprintf(c_row1, m_row1);
			ssd1306_SetCursor(2, 2);
			ssd1306_WriteString(c_row1, Font_6x8, White);

			uint8_t m_row2 [21];
			char c_row2 [21];
			uint8_t pos2 = 21;
			for (uint8_t k = 0; k < sizeof(message); k++)
				m_row2[k] = (message[pos2++]);
			sprintf(c_row2, m_row2);
			ssd1306_SetCursor(2, 12);
			ssd1306_WriteString(c_row2,Font_6x8, White);
			ssd1306_UpdateScreen();
		}

		if (sizeof(message) > 40)
		{
			uint8_t m_row1 [20];
			char c_row1 [20];

			for (uint8_t k = 0; k < sizeof(message); k++)
			m_row1[k] = (message[k]);
			sprintf(c_row1, m_row1);
			ssd1306_SetCursor(2, 2);
			ssd1306_WriteString(c_row1, Font_6x8, White);

			uint8_t m_row2 [20];
			char c_row2 [20];
			uint8_t pos2 = 21;
			for (uint8_t k = 0; k < sizeof(message); k++)
			m_row2[k] = (message[pos2++]);
				sprintf(c_row2, m_row2);
			ssd1306_SetCursor(2, 12);
			ssd1306_WriteString(c_row2,Font_6x8, White);

			uint8_t m_row3 [20];
			char c_row3 [20];
			uint8_t pos3 = 41;
			for (uint8_t k = 0; k < sizeof(message); k++)
				m_row3[k] = (message[pos3++]);
			sprintf(c_row3, m_row3);
			ssd1306_SetCursor(2, 22);
			ssd1306_WriteString(c_row3,Font_6x8, White);
			ssd1306_UpdateScreen();
		}

}/*End of function print_oled_message*/

/** @brief esp_ok, check for ok status
@author  Daniel Gripenstedt
@return uint8_t RX_IP_OF */
bool esp_ok ()
{
	uint8_t ok[] = "OK";
	uint8_t not_ok[] = "ERROR";

	uint8_t TX_buffer [] = "AT\r\n";	//test if esp is working
	uint8_t RX_AT [20];
	HAL_UART_Transmit(&huart4, (uint8_t*)TX_buffer, (sizeof (TX_buffer) - 1), 50);
	HAL_UART_Receive(&huart4, (uint8_t*)RX_AT, 20, 50);


	for (uint8_t i = 0; i < (sizeof(RX_AT) - 1); i++)
	{
		if ((RX_AT[i] == 'O') && (RX_AT[i + 1] == 'K'))
		{
			/*BSP_LCD_GLASS_DisplayString(ok);
			HAL_Delay(1000);
			BSP_LCD_GLASS_Clear();*/
			return true;
		}
	}

		/*uint8_t TX_RST [] = "AT+RST\r\n";	//reset esp
		uint8_t RX_RST [20];
		HAL_UART_Transmit(&huart4, (uint8_t*)TX_RST, (sizeof (TX_RST) - 1), 50);
		HAL_UART_Receive(&huart4, (uint8_t*)RX_RST, 20, 1000);
		BSP_LCD_GLASS_DisplayString(not_ok);
		HAL_Delay(5000);
		BSP_LCD_GLASS_Clear();*/
		return false;
}/*End of function esp_ok*/

/** @brief message_timer, check if it is time
 * to request a message
@author  Daniel Gripenstedt
@return bool*/
bool massege_timer (uint8_t second, uint8_t prev_second)
{

	if(second != prev_second)
	{
		return true;
	}

	else
	{
		return false;
	}

}/*End of function esp_ok*/

/** @brief esp_error_handler, handle esp error
 * to request a message
@author  Daniel Gripenstedt
@return uint8_t RX_IP_OF */
void esp_error_handler()
{
	while(1)	//infinity loop
	{
		BSP_LCD_GLASS_ScrollSentence("      ESP ERROR HANDLER", 1, SCROLL_SPEED_MEDIUM);
	}
}/*End of function esp_error_handler*/
