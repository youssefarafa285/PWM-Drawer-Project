/*
 * main.h
 *
 * Created: 11/30/2023 12:02:10 PM
 * Author : YOUSSEF ARAFA
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#include "CPU_Configurations.h"
#include "LED0_Private.h"
#include "LCD_Private.h"

void CLEAR_SCREEN(void);
void main_lines(void);
void data_display(void);
void fixed_vertival_lines(void);
void pwm_for_led(uint16_t read);
void first_section(void);
void second_section(void);
void third_section(void);
void forth_section(void);
uint8_t decimal_shift(uint8_t read);
void LCD_first_line (uint16_t read4);
void LCD_second_line (uint16_t read5);
uint8_t decimal_shift_h(uint8_t read);
uint8_t decimal_shift_back(uint8_t read8);
void LCD_third_line(uint16_t read5);
void LCD_forth_line (uint16_t read5);
void LCD_fifth_line (uint16_t read4);
void LCD_sixth_line (uint16_t read5);
void LCD_seventh_line(uint16_t read5);
void LCD_eight_line (uint16_t read5);




#endif /* MAIN_H_ */