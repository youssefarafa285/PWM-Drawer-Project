/*
 * DIO_Private.h
 *
 * Created: 11/21/2023 8:40:05 PM
 * Author : YOUSSEF ARAFA
 */ 


#ifndef DIO_PRIVATE_H_
#define DIO_PRIVATE_H_

#include "DIO_Configuration.h"

void DIO_SetPin_Direction(DIO_Ports port, DIO_Pins pin, DIO_Status status);
void DIO_SetPin_Value(DIO_Ports port, DIO_Pins pin, DIO_State state);
uint8_t DIO_ReadPin_Value(DIO_Ports port, DIO_Pins pin);
void DIO_TogglePin_Value(DIO_Ports port, DIO_Pins pin);
void DIO_SetPin_PullUp(DIO_Ports port, DIO_Pins pin);




#endif /* DIO_PRIVATE_H_ */