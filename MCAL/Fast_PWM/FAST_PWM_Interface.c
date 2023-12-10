/*
 * FAST_PWM_Interface.c
 *
 * Created: 11/28/2023 11:27:24 AM
 * Author : YOUSSEF ARAFA
 */ 


#include "FAST_PWM_Private.h"


void FAST_PWM_intialization(FAST_Prescaler prescaler){
	SET_BIT(TCCR0,WGM01); SET_BIT(TCCR0,WGM00);// CHoose mode as fast pwm
	SET_BIT(DDRB,3);   //set pin output PORT B BIN 3
	switch(prescaler)
	{
		case FAST_No_clock_source:
		CLR_BIT(TCCR0,CS02); CLR_BIT(TCCR0,CS01); CLR_BIT(TCCR0,CS00);
		break;
		case FAST_No_prescaling:
		CLR_BIT(TCCR0,CS02); CLR_BIT(TCCR0,CS01); SET_BIT(TCCR0,CS00);
		break;
		case FAST_From_prescaler8:
		CLR_BIT(TCCR0,CS02); SET_BIT(TCCR0,CS01); CLR_BIT(TCCR0,CS00);
		break;
		case FAST_From_prescaler64:
		CLR_BIT(TCCR0,CS02); SET_BIT(TCCR0,CS01); SET_BIT(TCCR0,CS00);
		break;
		case FAST_From_prescaler256:
		SET_BIT(TCCR0,CS02); CLR_BIT(TCCR0,CS01); CLR_BIT(TCCR0,CS00);
		break;
		case FAST_From_prescaler1024:
		SET_BIT(TCCR0,CS02); CLR_BIT(TCCR0,CS01); SET_BIT(TCCR0,CS00);
		break;
		
	}
	
}
void FAST_PWM_set_duty(FAST_Mode mode , uint8_t duty_cycle){

	switch(mode)
	{
		case FAST_OC0_Disconnected:
		CLR_BIT(TCCR0,COM01) ; CLR_BIT(TCCR0,COM00) ;
		break;
		case FAST_OC0_RESERVED:
		CLR_BIT(TCCR0,COM01) ; SET_BIT(TCCR0,COM00) ;
		break;

		case FAST_OC0_NON_INVERTING:{
			SET_BIT(TCCR0,COM01) ; CLR_BIT(TCCR0,COM00) ;
			OCR0=((256-1)*duty_cycle);
		}
		break;
		case FAST_OC0_INVERTING:
		{
			SET_BIT(TCCR0,COM01) ; SET_BIT(TCCR0,COM00) ;
			OCR0=(256-1)-(((256-duty_cycle)/100)-1);
		}
		break;
	}
}
