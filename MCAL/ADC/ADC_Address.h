/*
 * ADC_Address.h
 *
 * Created: 11/26/2023 9:25:10 AM
 * Author : YOUSSEF ARAFA
 */ 


#ifndef ADC_ADDRESS_H_
#define ADC_ADDRESS_H_

/*
#define ADMUX  (*(volatile uint8_t*)(0x27))
#define ADCSRA (*(volatile uint8_t*)(0x26))
#define ADCL   (*(volatile uint8_t*)(0x24))
#define ADCH   (*(volatile uint8_t*)(0x25))
#define SFIOR  (*(volatile uint8_t*)(0x))
*/
#define ADC_DT (*(volatile uint16_t*)(0x24))



#endif /* ADC_ADDRESS_H_ */