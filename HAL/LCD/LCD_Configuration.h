/*
 * LCD_Configuration.h
 *
 * Created: 11/22/2023 9:11:25 PM
 * Author : YOUSSEF ARAFA
 */ 


#ifndef LCD_CONFIGURATION_H_
#define LCD_CONFIGURATION_H_

#include "CPU_Configurations.h"
// Data port
#define LCD            PORTA
// Ports
#define LCD_DATA_PRT   DIO_PORTA
#define LCD_CNTRL_PRT  DIO_PORTB
// Control pins
#define LCD_RS         DIO_PIN1
#define LCD_RW         DIO_PIN2
#define LCD_EN         DIO_PIN7
#define LCD_reset      DIO_PIN4
#define LCD_pcb        DIO_PIN5
// Data pins
#define LCD_D0         DIO_PIN3
#define LCD_D1         DIO_PIN4
#define LCD_D2         DIO_PIN5
#define LCD_D3         DIO_PIN6
#define LCD_D4         DIO_PIN4
#define LCD_D5         DIO_PIN5
#define LCD_D6         DIO_PIN6
#define LCD_D7         DIO_PIN7
// State
#define LCD_OUT        DIO_OUTPUT
// Status
#define LCD_LOW        DIO_LOW
#define LCD_HIGH       DIO_HIGH



#endif /* LCD_CONFIGURATION_H_ */