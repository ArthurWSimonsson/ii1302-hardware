/*******************************************************************************
  * @file           : project_functions.c
  * @brief          : This file contains the functions for the project
  *
  ******************************************************************************
  * @author	Daniel Gripenstedt
  ******************************************************************************
  */
#include "test.h"
#include "project.h"
#include "stm32l4xx_hal.h"
#include <stdio.h>
#include "lcd.h"
#include "usart.h"
#include "rtc.h"
#include <stdbool.h>
#include "ssd1306_fonts.h"
#include "ssd1306.h"

/** @brief connect_WIFI, connect to wifi
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

	uint8_t TX_CONNECT_WIFI [] = {'A','T','+','C','W','J','A','P','=','"','U','N','"',',','"','P','W','"','\r','\n'};
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
}/*End of function esp_as_server*/

/** @brief esp_as_TCP, set up a tcp connection
 * connection to a server
@author  Daniel Gripenstedt, Arthur Simonsson, Botan Cosar
@return void */
uint8_t *esp_as_TCP()
{
	uint8_t TX_DOMAIN_NAME [] = "AT+CIPSTART=\"TCP\",\"35.228.147.153\",8080\r\n";
	uint8_t RX_DOMAIN_NAME [100];
	HAL_UART_Transmit(&huart4, (uint8_t*)TX_DOMAIN_NAME, sizeof (TX_DOMAIN_NAME), 100);	//set up TCP connection
	HAL_UART_Receive(&huart4, (uint8_t*)RX_DOMAIN_NAME, 100, 1000);

	uint8_t TX_SEND [] = "AT+CIPSEND=9\r\n";
	uint8_t TX_M [] = "welcome\r\n";
	uint8_t RX_SEND [50];
	uint8_t RX_M [100];
	HAL_UART_Transmit(&huart4, (uint8_t*)TX_SEND, (sizeof (TX_SEND) - 1), 100);	//prepare to send data over TCP
	HAL_UART_Receive(&huart4, (uint8_t*)RX_SEND, 50, 100);
	HAL_UART_Transmit(&huart4, (uint8_t*)TX_M, (sizeof (TX_M) - 1), 100);	//Send data over TCP
	HAL_UART_Receive(&huart4, (uint8_t*)RX_M, 100, 1000);

	uint8_t TX_END_TCP [] = "AT+CIPCLOSE\r\n";
	uint8_t RX_END_TCP [60];
	HAL_UART_Transmit(&huart4, (uint8_t*)TX_END_TCP, (sizeof (TX_END_TCP) - 1), 500);	//Close TCP connection
	HAL_UART_Receive(&huart4, (uint8_t*)RX_END_TCP, 60, 1000);
	HAL_Delay(100);

	static uint8_t old_M [100];
	//static uint8_t *p_old_M;
	for (uint8_t i = 0; i < 100; i++)
	{
		old_M[i] = RX_M[i];
	}
	print_oled_message(&RX_M, sizeof(RX_M));
	//p_old_M = &old_M;
	return &old_M;
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
 * @param uint8_t *arr, uint8_t size
@author  Daniel Gripenstedt
@return uint8_t RX_IP_OF */
void print_oled_message (uint8_t *arr, uint8_t size)
{
	ssd1306_Fill(Black); //reset screen
	uint8_t count = -1;	//how many characters of the message
	uint8_t extra_char = 0;
		uint8_t i;
		for (i = 30; i < (size - 1); i++)	//find number of characters
		{
			if (*(arr + i) == ':') {break;}
		}

		for (uint8_t j = (i + 1); j < (size - 1); j++)	//find number of characters
			{
				count++;
				if (*(arr + j) == '~') {break;}
			}
		uint8_t message [count];	//new message

		for (uint8_t k = 0; k < sizeof(message); k++)
		{
			message [k] = (*(arr + i + 1));
			i++;
		}

		uint8_t message_size = sizeof(message);
		if (sizeof(message) <= 21)
		{
			char cbuff [21];
			sprintf(cbuff, message);

			for (uint8_t i = sizeof(message); i <= 21; i++)
			{
				cbuff[i] = ' ';
			}
			ssd1306_SetCursor(2, 2);
			ssd1306_WriteString(cbuff, Font_6x8, White);
			ssd1306_UpdateScreen();
		}
		if ((sizeof(message) > 21) && (sizeof(message) <= 41))
		{
			uint8_t m_row1 [20];
			char c_row1 [20];
			uint8_t m_row2 [20];
			char c_row2 [20];
			uint8_t space = 0;
			uint8_t pos1 = 0;
			uint8_t pos2 = 0;
			uint8_t k;

			for (k = 0; k <= 20; k++)
			{
				m_row1[k] = (message[k]);
				if (message[k] == ' ')
					space = k;
			}

			if (message[k - 1] != ' ' && message[k] != ' ')
			{
				k = 20 - space;
				for(uint8_t i = space; i < 20; i++)
				{
					m_row2[pos1++] = m_row1[space + 1];
					m_row1[space++] = ' ';
					message_size++;
				}
				m_row1[space++] = ' ';
				pos2 = 21;
			}
			else
			{
				k = 0;
				pos2 = 22;
			}
			sprintf(c_row1, m_row1);
			ssd1306_SetCursor(2, 2);
			ssd1306_WriteString(c_row1, Font_6x8, White);

			for (k = k; k <= message_size - 21; k++)
				m_row2[k] = (message[pos2++]);

			sprintf(c_row2, m_row2);

			if (message[21] == ' ')
				message_size--;

			for (uint8_t i = message_size - 21; i <= 20; i++)
					c_row2[i] = ' ';

			ssd1306_SetCursor(2, 12);
			ssd1306_WriteString(c_row2,Font_6x8, White);
			ssd1306_UpdateScreen();
		}

		if (message_size >= 43)
		{
			uint8_t m_row1 [21];
			char c_row1 [21];
			uint8_t m_row2 [21];
			uint8_t m_row3 [21];
			char c_row2 [21];
			uint8_t space = 0;
			uint8_t pos1 = 0;
			uint8_t pos2 = 0;
			uint8_t pos3 = 0;
			uint8_t k;
			uint8_t space2 = 0;

			for (k = 0; k <= 20; k++)
			{
				m_row1[k] = (message[k]);
				if (message[k] == ' ')
				space = k;
			}

			if ((message[k - 1] != ' ') && (message[k] != ' '))
			{
				k = 20 - space;
				for(uint8_t i = space + 1; i <= 20; i++)
				{
					m_row2[pos1++] = m_row1[space + 1];
					m_row1[space++] = ' ';
					extra_char++;
					message_size++;
				}
				m_row1[space++] = ' ';
				pos2 = 21;
			}
			else
			{
				k = 0;
				pos2 = 21;
			}
			if (message[21] == ' ')
			{
				message_size--;
				pos2++;
			}


			sprintf(c_row1, m_row1);
			ssd1306_SetCursor(2, 2);
			ssd1306_WriteString(c_row1, Font_6x8, White);

			for (k = k; k <= 20; k++)
			{
				m_row2[k] = (message[pos2++]);
				if (m_row2[k] == ' ')
				space = k;
			}

			sprintf(c_row2, m_row2);

			if ((m_row2[k - 1] != ' ') && (message[21 + k - extra_char] != ' '))
			{
				space2 = 20 - space;
				pos3 = pos2 - space2;
			}

			else
			{
				k = 0;
				pos3 = pos2;
			}

			if ((m_row2[20] != ' ') && (message[42 - extra_char] != ' '))
			{
				k = space2;
				for(uint8_t i = space; i <= 20; i++)
				{
					c_row2[space] = ' ';
					space++;
					message_size++;
					extra_char++;
				}
				message_size--;
			}

			if (message[42 - extra_char] == ' ')
			{
				pos3++;
				message_size--;
				extra_char--;
			}
				ssd1306_SetCursor(2, 12);
				ssd1306_WriteString(c_row2,Font_6x8, White);

			char c_row3 [20];
			for (k = 0; k <= 20; k++)
				m_row3[k] = message[pos3++];
			sprintf(c_row3, m_row3);

			for (uint8_t i = message_size - 42; i <= 20; i++)
				c_row3[i] = ' ';

			ssd1306_SetCursor(2, 22);
			ssd1306_WriteString(c_row3,Font_6x8, White);
			ssd1306_UpdateScreen();
		}

}/*End of function print_oled_message*/

/** @brief esp_ok, test so the esp is working
@author  Daniel Gripenstedt
@return uint8_t bool*/
bool esp_ok ()
{
	uint8_t RX_Recive [20];
	uint8_t AT_OK [] = "AT\r\r\n\r\nOK";
	uint8_t AT [] = "AT\r\n";
	HAL_UART_Transmit(&huart4, (uint8_t*)AT, 4, 100);
	HAL_UART_Receive(&huart4, (uint8_t*)RX_Recive, 20, 1000);

	for (uint8_t i = 0; i < 9; i++)
	{
		if (RX_Recive[i] != AT_OK[i])
		{
			break;
		}
		if ((RX_Recive[0] == 'A') && (RX_Recive[1] == 'T') && (RX_Recive[7] == 'O') && (RX_Recive[8] == 'K'))
		{
			return true;
		}
	}
		return false;
}/*End of function esp_ok*/

/** @brief esp_ok, check for ok status
 * @param uint8_t *TX_buffer, uint8_t size
@author  Daniel Gripenstedt
@return uint8_t bool*/
bool esp_find_ok (uint8_t *TX_buffer, uint8_t size)
{
	uint8_t RX_Recive [200];
	HAL_UART_Transmit(&huart4, (uint8_t*)TX_buffer, (size - 1), 100);
	HAL_UART_Receive(&huart4, (uint8_t*)RX_Recive, 200, 1000);

	for (uint8_t i = 0; i < 9; i++)
	{
		if ((RX_Recive[i] == 'O') && (RX_Recive[i + 1] == 'K'))
		{
			return true;
		}
	}
		return false;
}/*End of function esp_find_ok*/

/** @brief message_timer, check if it is time
 * to request a message
 * @param uint8_t second, uint8_t prev_second
@author  Daniel Gripenstedt
@return bool*/
bool message_timer (uint8_t second, uint8_t prev_second)
{

	if(second != prev_second)
	{
		return true;
	}

	else
	{
		return false;
	}

}/*End of function message_timer*/

/** @brief esp_error_handler, handle esp error
 * by writing ESP ERROR on the OLED and then reset the MCU
@author  Daniel Gripenstedt
@return void */
void esp_error_handler()
{
	ssd1306_Fill(Black);
	ssd1306_SetCursor(2, 26);
	ssd1306_WriteString("ESP ERROR", Font_11x18, White);
	ssd1306_UpdateScreen();

	HAL_Delay(1000);
	HAL_NVIC_SystemReset();
}/*End of function esp_error_handler*/

/** @brief Large_number, if the number has 2 digits
 * then split it into to numbers, digit 1 and digit 2.
 * @param Large_number
@author  Daniel Gripenstedt
@return void */
void Large_number (uint8_t Large_number)
{
	double temp_num = Large_number / 10;	//first number

	uint8_t first_num = floor(temp_num);	//make temp_num into an uint8_t

	temp_num = Large_number;
	int modulo_num = Large_number % 10;	//modulos can not be made on uint8_t
	uint8_t second_num = modulo_num;
}/*End of function Large_number*/

/** @brief get_time, get the time from the server
 * then set the time for the MCU
@author  Daniel Gripenstedt
@return uint8_t  */
void get_time(uint8_t *time)
{
	uint8_t TX_DOMAIN_NAME [] = "AT+CIPSTART=\"TCP\",\"35.228.147.153\",8080\r\n";
	uint8_t RX_DOMAIN_NAME [100];
	HAL_UART_Transmit(&huart4, (uint8_t*)TX_DOMAIN_NAME, sizeof (TX_DOMAIN_NAME), 100);	//set up TCP connection
	HAL_UART_Receive(&huart4, (uint8_t*)RX_DOMAIN_NAME, 100, 100);

	uint8_t TX_SEND [] = "AT+CIPSEND=6\r\n";
	uint8_t TX_M [] = "time\r\n";
	uint8_t RX_SEND [50];
	uint8_t RX_M [200];
	HAL_UART_Transmit(&huart4, (uint8_t*)TX_SEND, (sizeof (TX_SEND) - 1), 50);	//prepare to send data over TCP
	HAL_UART_Receive(&huart4, (uint8_t*)RX_SEND, 50, 100);
	HAL_UART_Transmit(&huart4, (uint8_t*)TX_M, (sizeof (TX_M) - 1), 100);	//Send data over TCP
	HAL_UART_Receive(&huart4, (uint8_t*)RX_M, 200, 500);

	uint8_t TX_END_TCP [] = "AT+CIPCLOSE\r\n";
	uint8_t RX_END_TCP [60];
	HAL_UART_Transmit(&huart4, (uint8_t*)TX_END_TCP, (sizeof (TX_END_TCP) - 1), 100);	//Close TCP connection
	HAL_UART_Receive(&huart4, (uint8_t*)RX_END_TCP, 60, 100);
	HAL_Delay(100);


			uint8_t i;
			for (i = 30; i < 200; i++)	//find number of characters
			{
				if (RX_M[i] == ':') {break;}
			}

			for (uint8_t k = 0; k < 8; k++)
			{
				*(time + k) = (RX_M[k + 48]);
				i++;
			}
	/*char c [5];

	sprintf(c, message);
	ssd1306_SetCursor(2, 34);
	ssd1306_WriteString(c,Font_6x8, White);
	ssd1306_UpdateScreen();*/
}

/** @brief print_time, print the current time
@author  Daniel Gripenstedt
@return uint8_t  */
void print_time(uint8_t *time)
{
	*(time + 5) = ' ';
	*(time + 6) = ' ';
	*(time + 7) = ' ';
	char c_time [5];
	sprintf(c_time, time);
	ssd1306_SetCursor(2, 34);
	ssd1306_WriteString(c_time,Font_6x8, White);
	ssd1306_UpdateScreen();
}/*End of function print_time*/

/** @brief print_time, print the current time
@author  Daniel Gripenstedt
@return uint8_t  */
void process_time(uint8_t *time, uint8_t *hour, uint8_t *minute, uint8_t *second)
{
	if (*time == '0')
	{
		*hour = *(time + 1);
	}
	else
	{
		*hour = ((*time) * 10) + *(time + 1);
	}

	if (*(time + 3) == '0')
	{
		*minute = *(time + 4);
	}
	else
	{
		*minute = (*(time + 3) * 10) + *(time + 4);
	}

	if (*(time + 5) == '0')
	{
		*second = *(time + 7);
	}
	else
	{
		*second = (*(time + 6) * 10) + *(time + 7);
	}
}/*End of function process_time*/

void init_stuff()
{
	BSP_LCD_GLASS_Init();
		BSP_LED_Init(LED4);
		BSP_LED_Init(LED5);
		ssd1306_Init();
		menu_state();
		cursor_init();
}
