/*
 * DIO_Configuration.h
 *
 * Created: 11/21/2023 8:41:06 PM
 * Author : YOUSSEF ARAFA
 */ 


#ifndef DIO_CONFIGURATION_H_
#define DIO_CONFIGURATION_H_

#include "CPU_Configurations.h"
#include "DIO_Address.h"
//Renaming ports
typedef enum
{
	DIO_PORTA = 0,
	DIO_PORTB = 1,
	DIO_PORTC = 2,
	DIO_PORTD = 3
}DIO_Ports;
//Renaming pins
typedef enum
{
	DIO_PIN0 = 0,
	DIO_PIN1 = 1,
	DIO_PIN2 = 2,
	DIO_PIN3 = 3,
	DIO_PIN4 = 4,
	DIO_PIN5 = 5,
	DIO_PIN6 = 6,
	DIO_PIN7 = 7
}DIO_Pins;
//Renaming status
typedef enum
{
	DIO_INPUT = 0,
	DIO_OUTPUT = 1
}DIO_Status;
//Renaming state
typedef enum
{
	DIO_LOW = 0,
	DIO_HIGH = 1
}DIO_State;




#endif /* DIO_CONFIGURATION_H_ */