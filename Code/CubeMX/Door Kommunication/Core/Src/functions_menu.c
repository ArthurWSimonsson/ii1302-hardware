/*******************************************************************************
  * @file           : function_menu.c
  * @brief          : Functions for the menu
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
#include "QR_code.h"

#define Font_S (Font_6x8)
#define Font_M (Font_7x10)
#define Font_L (Font_11x18)
#define Font_XL (Font_16x26)

#define MAIN 		0
#define QR 			1
#define LOG 		2

void cursor_init(void) {
	BSP_JOY_Init(JOY_MODE_GPIO);
	ssd1306_SetCursor(32, 54);
	ssd1306_WriteString("<", Font_M, White);
	ssd1306_UpdateScreen();
}
uint8_t cursor(void) {
	uint8_t rows[] = { 32, 100 };
	uint8_t *p;
	p = rows;
	uint8_t selection = 0;
	while (1) {
		JOYState_TypeDef state = BSP_JOY_GetState();
		if (state == JOY_UP || state == JOY_DOWN) {
			if (selection == 0) {
				selection = 1;
				ssd1306_SetCursor(32, 54);
				ssd1306_WriteString(" ", Font_M, White);
				ssd1306_SetCursor(96, 54);
				ssd1306_WriteString("<", Font_M, White);
				ssd1306_UpdateScreen();
				HAL_Delay(200);

			} else {
				if (selection == 1) {
					selection = 0;
					ssd1306_SetCursor(32, 54);
					ssd1306_WriteString("<", Font_M, White);
					ssd1306_SetCursor(96, 54);
					ssd1306_WriteString(" ", Font_M, White);
					ssd1306_UpdateScreen();
					HAL_Delay(200);
				} else {
					selection = -1;
					return selection;
				}
			}
		}
		if (state == JOY_DOWN) {
			return selection;
		}

	}
}
uint8_t menu_log(void) {
	ssd1306_Fill(Black);
	ssd1306_SetCursor(2, 0);
	ssd1306_WriteString("MESSAGE 1", Font_M, White);
	ssd1306_SetCursor(2, 10);
	ssd1306_WriteString("MESSAGE 2", Font_M, White);
	ssd1306_SetCursor(2, 10 + 10);
	ssd1306_WriteString("MESSAGE 3", Font_M, White);

	ssd1306_SetCursor(2, 54);
	ssd1306_WriteString("BACK", Font_M, White);
	ssd1306_UpdateScreen();
	cursor_init();
	BSP_JOY_Init(JOY_MODE_GPIO);
	uint8_t selection = 0;
	while (1) {
		JOYState_TypeDef state = BSP_JOY_GetState();
		if (state == JOY_SEL) {
			return MAIN;
		}
	}

	HAL_Delay(100);
}

uint8_t menu_QR(void) {
	ssd1306_Fill(Black);
	draw_QR(line_QR);
	ssd1306_SetCursor(2, 54);
	ssd1306_WriteString("BACK", Font_M, White);
	ssd1306_UpdateScreen();
	/*cursor_init();
	BSP_JOY_Init(JOY_MODE_GPIO);
	uint8_t selection = 0;
	uint8_t value = 0xFF;

	while (1) {
		JOYState_TypeDef state = BSP_JOY_GetState();
		if (state == JOY_DOWN) {
			ssd1306_WriteCommand(0x81);
			ssd1306_WriteCommand(0xFF);
			return MAIN;
		}
<<<<<<< HEAD

		value = value - 4;
		ssd1306_WriteCommand(0x81);
		ssd1306_WriteCommand(value);
		HAL_Delay(100);
	}
=======
		HAL_Delay(100);*/
}

uint8_t menu_main(void) {
	ssd1306_Fill(Black);
	ssd1306_SetCursor(2, 0);
	//ssd1306_WriteString("ASHOKA TANO", Font_M, White);
	ssd1306_SetCursor(2, 54);
	ssd1306_WriteString("QR", Font_M, White);
	ssd1306_UpdateScreen();
	cursor_init();
	uint8_t selection = 0;
	while (1) {
		JOYState_TypeDef state = BSP_JOY_GetState();

		if (state == JOY_DOWN) {
			if (selection == 0)
				return QR;
		}
		project();
	}

	HAL_Delay(100);
}

void menu_state(void) {
	uint8_t state = 0;
	BSP_JOY_Init(JOY_MODE_GPIO);
	while (1) {
		switch (state) {
		case MAIN:
			state = menu_main();
			break;
		case QR:
			state = menu_QR();
			break;
		case LOG:
			state = menu_log();
			break;
		default:
			ssd1306_Fill(Black);
			ssd1306_SetCursor(2, 0);
			ssd1306_WriteString("ERROR", Font_M, White);
			ssd1306_UpdateScreen();
			break;
		}
	}
}

