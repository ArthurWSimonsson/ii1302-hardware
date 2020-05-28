/*******************************************************************************
  * @file           : QR_code.c
  * @brief          : functions for the QR code
  *
  ******************************************************************************
  * @author	Sebastian Thunberg
  ******************************************************************************
  */
#include <stdint.h>
#include "ssd1306.h"

void draw_QR(uint8_t lines[29][29]) {
	uint8_t i;
	uint8_t x = 60;
	uint8_t y = 3;
	uint8_t box[31] = { };
	draw_line(box, x, y-2);
	draw_line(box, x, y+58);
	draw_line_down(box, x-2, y-2);
	draw_line_down(box, x+58, y-2);

	for (i = 0; i < 29; i++) {
		draw_line(lines[i], x, y);
		y = y + 2;
	}
	ssd1306_UpdateScreen();
}
void draw_line_down(uint8_t line[29], uint8_t x, uint8_t y) {
	uint8_t i;
	for (i = 0; i < 31; i++) {
		if (line[i] == 0) {
			draw_square(x, y);

		}
		y = y + 2;
	}

}
void draw_line(uint8_t line[29], uint8_t x, uint8_t y) {
	uint8_t i;
	for (i = 0; i < 29; i++) {
		if (line[i] == 0) {
			draw_square(x, y);

		}
		x = x + 2;
	}

}
void draw_square(uint8_t x, uint8_t y) {
	uint8_t i = x;
	uint8_t j = y;
	uint8_t size = 2;
	while (i < (x + size)) {
		j = y;
		while (j < (y + size)) {
			ssd1306_DrawPixel(i, j, White);
			j++;
		}
		i++;
	}

}

