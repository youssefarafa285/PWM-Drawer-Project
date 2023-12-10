/*
 * FAST_PWM_Private.h
 *
 * Created: 11/28/2023 11:26:24 AM
 * Author : YOUSSEF ARAFA
 */ 


#ifndef FAST_PWM_PRIVATE_H_
#define FAST_PWM_PRIVATE_H_

#include "FAST_PWM_Configuration.h"

void FAST_PWM_intialization(FAST_Prescaler prescaler);
void FAST_PWM_set_duty(FAST_Mode mode , uint8_t duty_cycle);


#endif /* FAST_PWM_PRIVATE_H_ */