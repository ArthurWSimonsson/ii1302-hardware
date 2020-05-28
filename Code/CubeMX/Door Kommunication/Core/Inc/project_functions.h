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
uint8_t *esp_as_TCP();
int get_IP(int);
void print_oled_message(*uint8_t, uint8_t);
bool esp_ok(void);
bool esp_find_ok(*uint8_t, uint8_t);
void Large_number (int);
void esp_error_handler(void);
bool message_timer(int, int);
void Large_number (uint8_t Large_number);
void get_time (void);
void print_time(*uint8_t);
void process_time (*uint8_t, *uint8_t, *uint8_t, *uint8_t);
void init_stuff(void);
