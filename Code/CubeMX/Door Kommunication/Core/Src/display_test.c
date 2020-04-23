#include "stm32l4xx_hal.h"
#include "string.h"
#include <stdio.h>
#include "lcd.h"
#include "i2c.h"
#include "ssd1306_tests.h"
#include "ssd1306.h"
#include "functions_menu.h"

#define Font_S (Font_6x8)
#define Font_M (Font_7x10)
#define Font_L (Font_11x18)
#define Font_XL (Font_16x26)

void test_disp(void) {
	ssd1306_Init();
	test_joystick();
	//I2C_Scan();
}
void test_menu(void) {
	menu_main();
}

void test_joystick() {
	//GPIO_TypeDef SEL_JOY_GPIO_PORT;
	while (1) {
		uint8_t state = (HAL_GPIO_ReadPin(RIGHT_JOY_GPIO_PORT, RIGHT_JOY_PIN) == GPIO_PIN_SET);
		{
			ssd1306_SetCursor(2, 0);
			ssd1306_WriteString("no", Font_S, White);
			ssd1306_UpdateScreen();

		}
	}
	ssd1306_Fill(Black);
	ssd1306_SetCursor(2, 0);
	ssd1306_WriteString("yes", Font_S, White);
	ssd1306_UpdateScreen();
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
