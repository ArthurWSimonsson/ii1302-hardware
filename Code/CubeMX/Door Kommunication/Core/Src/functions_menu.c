#include "stm32l4xx_hal.h"
#include "string.h"
#include <stdio.h>
#include "lcd.h"
#include "i2c.h"
#include "ssd1306_tests.h"
#include "ssd1306.h"

#define Font_S (Font_6x8)
#define Font_M (Font_7x10)
#define Font_L (Font_11x18)
#define Font_XL (Font_16x26)

void menu_main(void) {
	ssd1306_Fill(Black);
	ssd1306_SetCursor(2, 0);
	ssd1306_WriteString("Main Menu", Font_L, White);
	ssd1306_SetCursor(2, 18);
	ssd1306_WriteString("Option 1", Font_M, White);
	ssd1306_SetCursor(2, 18 + 10);
	ssd1306_WriteString("Option 2", Font_M, White);
	ssd1306_SetCursor(2, 18 + 10 + 10);
	ssd1306_WriteString("Option 3", Font_M, White);
	ssd1306_SetCursor(2, 18 + 10 + 10 + 10);
	ssd1306_WriteString("Option 4", Font_M, White);
	ssd1306_UpdateScreen();
}
