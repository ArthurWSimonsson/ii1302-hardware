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
#include "string.h"
#include <stdio.h>
#include "lcd.h"
#include "i2c.h"

/** @brief Test_program, test functions to be used in the project
 * and some extra functions to better understand how different commands
 * and hardware works.
@author  Daniel Gripenstedt
@return void */
void Test_program(void)
{
	//test_led();
	//test_LCD();
}/*End of function Test_program*/

/** @brief Test_display, print something on the display
@author  Daniel Gripenstedt
@return void */
void disp_ON(){

}
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
