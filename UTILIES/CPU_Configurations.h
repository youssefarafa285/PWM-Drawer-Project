/*
 * CPU_Configurations.h
 *
 * Created: 11/21/2023 8:06:54 PM
 * Author : YOUSSEF ARAFA
 */ 


#ifndef CPU_CONFIGURATIONS_H_
#define CPU_CONFIGURATIONS_H_

//CPU Configurations
#undef F_CPU
#define F_CPU 16000000
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "BIT_Math.h"
#include "STD_Types.h"
#include "DIO_Private.h"

#include "ADC_Private.h"

#include "FAST_PWM_PRIVATE.h"


#endif /* CPU_CONFIGURATIONS_H_ */