/*******************************************************************************
  * @file           : display_test.c
  * @brief          : test functions for the display
  *
  ******************************************************************************
  * @author	Sebastian Thunberg
  ******************************************************************************
  */

#include "stm32l4xx_hal.h"
#include "string.h"
#include <stdio.h>
#include "lcd.h"
#include "i2c.h"
#include "ssd1306_tests.h"
#include "ssd1306.h"
#include "functions_menu.h"
#include "usart.h"
#include "stm32l476g_discovery.h"
#include "QR_code.h"

#define Font_S (Font_6x8)
#define Font_M (Font_7x10)
#define Font_L (Font_11x18)
#define Font_XL (Font_16x26)

void test_wifi_uart(void) {
	uint8_t TX_buffer[] = "AT\r\n";	//test if esp is working
	uint8_t RX_AT[20];
	HAL_UART_Transmit(&huart4, (uint8_t*) TX_buffer, (sizeof(TX_buffer) - 1),
			50);
	HAL_UART_Receive(&huart4, (uint8_t*) RX_AT, 20, 50);
	ssd1306_Fill(Black);
	ssd1306_SetCursor(2, 0);
	ssd1306_WriteString(RX_AT, Font_S, White);
	ssd1306_UpdateScreen();

}
void test_contrast(void) {
	ssd1306_Fill(Black);
	ssd1306_SetCursor(2, 0);
	ssd1306_WriteString("TEST", Font_S, White);
	ssd1306_UpdateScreen();
	uint8_t value = 0xFF;
	while (1) {
		value = value - 16;
		ssd1306_WriteCommand(0x81);
		ssd1306_WriteCommand(value);
		HAL_Delay(100);
	}

}
void test_QR(void) {

//uint8_t lines[29][29] = line_QR;
//draw_QR(line_QR);
//uint8_t line[29] = { 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1 };
//draw_line(line);
//draw_square(5,5);
//
	test_button();
}
void test_menu(void) {
	ssd1306_Init();
	menu_state();
	cursor_init();
	while (1) {
		cursor();
	}
}
void test_joystick() {
	BSP_JOY_Init(JOY_MODE_GPIO);
	JOYState_TypeDef state = BSP_JOY_GetState();
	while (1) {

		JOYState_TypeDef state = BSP_JOY_GetState();
		if (state == JOY_SEL) {
			ssd1306_Fill(Black);
			ssd1306_SetCursor(2, 0);
			ssd1306_WriteString("SEL", Font_L, White);
			ssd1306_UpdateScreen();
		}
		if (state == JOY_NONE) {
			ssd1306_Fill(Black);
			ssd1306_SetCursor(2, 0);
			ssd1306_WriteString("NONE", Font_L, White);
			ssd1306_UpdateScreen();
		}
		if (state == JOY_RIGHT) {
			ssd1306_Fill(Black);
			ssd1306_SetCursor(2, 0);
			ssd1306_WriteString("RIGHT", Font_L, White);
			ssd1306_UpdateScreen();
		}
		if (state == JOY_LEFT) {
			ssd1306_Fill(Black);
			ssd1306_SetCursor(2, 0);
			ssd1306_WriteString("LEFT", Font_L, White);
			ssd1306_UpdateScreen();
		}
		if (state == JOY_UP) {
			ssd1306_Fill(Black);
			ssd1306_SetCursor(2, 0);
			ssd1306_WriteString("UP", Font_L, White);
			ssd1306_UpdateScreen();
		}
		if (state == JOY_DOWN) {
			ssd1306_Fill(Black);
			ssd1306_SetCursor(2, 0);
			ssd1306_WriteString("DOWN", Font_L, White);
			ssd1306_UpdateScreen();
		}

	}
}
void test_OLED() {
	while (1) {
		ssd1306_Fill(Black);
		ssd1306_SetCursor(2, 0);
		ssd1306_WriteString("Hello World", Font_S, White);
		ssd1306_UpdateScreen();
		HAL_Delay(1000);
		ssd1306_Fill(Black);
		ssd1306_SetCursor(2, 0);
		ssd1306_WriteString("Hello World", Font_M, White);
		ssd1306_UpdateScreen();
		HAL_Delay(1000);
		ssd1306_Fill(Black);
		ssd1306_SetCursor(2, 0);
		ssd1306_WriteString("Hello World", Font_L, White);
		ssd1306_UpdateScreen();
		HAL_Delay(1000);
		ssd1306_Fill(Black);
		ssd1306_SetCursor(2, 0);
		ssd1306_WriteString("Hello World", Font_XL, White);
		ssd1306_UpdateScreen();
		HAL_Delay(1000);
	}
}
void test_inbyggd() {
	char buffer[50];
	sprintf(buffer, "HELLO WORLD ");
	char buffer2[50];
	sprintf(buffer2, "Yao");
	BSP_LCD_GLASS_Init();
	while (1) {
		BSP_LCD_GLASS_DisplayString(buffer);
		HAL_Delay(5000);
		BSP_LCD_GLASS_ScrollSentence(buffer, 2, 400);
		HAL_Delay(1000);
	}
}
void I2C_Scan() {

	char info[] = "Scanning I2C bus...\r\n";
//HAL_UART_Transmit(&huart5, (uint8_t*) info, strlen(info), HAL_MAX_DELAY);
	inb_disp_write(info);
	HAL_StatusTypeDef res;
	for (uint16_t i = 0; i < 128; i++) {
		res = HAL_I2C_IsDeviceReady(&hi2c1, i << 1, 1, 10);
		if (res == HAL_OK) {
			char msg[64];
			snprintf(msg, sizeof(msg), "0x%02X", i);
			//HAL_UART_Transmit(&huart5, (uint8_t*) msg, strlen(msg), HAL_MAX_DELAY);
			inb_disp_clear();
			inb_disp_write(msg);
		} else {
			//HAL_UART_Transmit(&huart2, (uint8_t*) ".", 1, HAL_MAX_DELAY);

		}
	}
//HAL_UART_Transmit(&huart2, (uint8_t*) "\r\n", 2, HAL_MAX_DELAY);
	HAL_Delay(10000);
	inb_disp_clear();
	inb_disp_write("end");
}
void test_disp(void) {
	ssd1306_Init();test_menu();
	test_OLED();
	//I2C_Scan();
	//test_wifi_uart();
	//test_joystick();
	//test_QR();
	//test_contrast();
	//test_button();
}
