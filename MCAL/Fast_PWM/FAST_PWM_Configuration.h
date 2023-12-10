/*
 * FAST_PWM_Configuration.h
 *
 * Created: 11/28/2023 11:27:10 AM
 * Author : YOUSSEF ARAFA
 */ 


#ifndef FAST_PWM_CONFIGURATION_H_
#define FAST_PWM_CONFIGURATION_H_

#include "CPU_Configurations.h"
#include "FAST_PWM_Address.h"

typedef enum
{
	FAST_OC0_Disconnected=0,
	FAST_OC0_RESERVED=1,
	FAST_OC0_NON_INVERTING=2,
	FAST_OC0_INVERTING=3
}FAST_Mode;

typedef enum
{
	FAST_No_clock_source=0,
	FAST_No_prescaling=1,
	FAST_From_prescaler8=2,
	FAST_From_prescaler64=3,
	FAST_From_prescaler256=4,
	FAST_From_prescaler1024=5,
}FAST_Prescaler;





#endif /* FAST_PWM_CONFIGURATION_H_ */