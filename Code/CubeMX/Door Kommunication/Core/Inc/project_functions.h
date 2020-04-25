/*******************************************************************************
  * @file           : project_functions.h
  * @brief          : Header for project_functions.c
  *
  ******************************************************************************
  * @author	Daniel Gripenstedt
  ******************************************************************************
  */

//First includes
#include <stdio.h>
#include <main.h>
#include "string.h"

//Project functions decelerations
void connect_WIFI(void);
void esp_as_server(void);
void esp_as_TCP(void);
int get_IP(int);
void print_oled_message(*int, int);
bool esp_ok(void);
void Large_number (int);
void esp_error_handler(void);
bool message_timer(int, int);
