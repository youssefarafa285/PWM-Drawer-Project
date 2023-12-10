/*
 * ADC_Private.h
 *
 * Created: 11/26/2023 9:26:40 AM
 * Author : YOUSSEF ARAFA
 */ 


#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

#include "ADC_Configuration.h"

void ADC_Initialization(ADC_Vref vref, ADC_Prescaler prescaler);
uint16_t ADC_Read(ADC_Channel channel);



#endif /* ADC_PRIVATE_H_ */