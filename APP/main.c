/*
 * PWM_project.c
 *
 * Created: 11/30/2023 12:02:32 PM
 * Author : YOUSSEF ARAFA
 */ 

#include "main.h"


uint16_t read2=0;


int main(void)
{

	FAST_PWM_intialization(FAST_From_prescaler1024);
	LED0_Initialize();
	LCD_Initialize();
	LCD_ClearScreen();
	ADC_Initialization(AVCC,ADC_PRE128);
	uint16_t read=0;
	
	
	//Set graphical mode ON
	LCD_Write_Command(0x34);
	_delay_ms(100);
	LCD_Write_Command(0x36);
	_delay_ms(500);

	//CLEAR SCREEN from pervious data display
	CLEAR_SCREEN();


	main_lines();  //draw the main lines of PWM time cycle on graphical lcd

	_delay_ms(20);

	data_display(); //graphical mode off and display main date on LCD (frequency, duty cycle and time)

	while (1)
	{
		read = ADC_Read(ADC_CH1);  //read from ADC (the POT value)
		
		pwm_for_led(read); //change duty cycle due to read from POT
		
		
		read = read/(float)10.24;   // read = read * (100/1024) to change range from 0-100;
		
		if(read !=0){
			LCD_Write_Command(0x96); //go to location on LCD (page2 with shift by 6 blocks)
			LCD_Write_Number(read);  // display read value as a duty cycle percent
			read2 = read*(float)0.64;
			
			LCD_Write_Command(0x36);  //graphical mode On again to draw
			
			fixed_vertival_lines();  //to draw the boundary lines for PWM wave shape
			
			first_section();  //for draw the first block at line 3 with changing by POT
			
			if(read2 >= 16)  //to draw the second block when duty cycle >= 25%
			second_section();
			
			if(read2 >= 32)  //to draw the third block when duty cycle >= 50%
			third_section();
			
			if(read2 >= 48)  //to draw the forth block when duty cycle >= 75%
			forth_section();
			
		}                //While end
		read=0;          // make read from ADC equal zero
		_delay_ms(20);
	}
	return 0;
}

void first_section(void){
	LCD_first_line(read2);
	LCD_fifth_line (read2);
}

void second_section(void){
	uint16_t m1 = read2 - 16;
	LCD_second_line(m1);
	LCD_sixth_line (m1);
}

void third_section(void){
	uint16_t m2 = read2 - 32;
	LCD_third_line(m2);
	LCD_seventh_line(m2);
}

void forth_section(void){
	uint16_t m3 = read2 - 48;
	LCD_forth_line(m3);
	LCD_eight_line (m3);
}

void fixed_vertival_lines(void){
	
	uint8_t y;
	
	for(y=0;y<16;y++){    //FIRST LINE VERTICAL
		LCD_Write_Command(0x80 | y);
		LCD_Write_Command(0x88 | 0);
		LCD_Write_Character(0b11000000);
		LCD_Write_Character(0x00);
	}
	
	for(y=0;y<16;y++){    //FIRST LINE VERTICAL
		LCD_Write_Command(0x80 | y);
		LCD_Write_Command(0x88 | 4);
		LCD_Write_Character(0xC0);
		LCD_Write_Character(0x00);
	}
}

void pwm_for_led(uint16_t read){
	
	SET_BIT(TCCR0,COM01) ; CLR_BIT(TCCR0,COM00);
	uint16_t op=read*(float)0.249;
	OCR0= op;
	_delay_ms(5);
}

void data_display(void){
	
	LCD_Write_Command(0x30);
	
	LCD_Write_Command(0x80);
	LCD_Write_string("Frequency: ");
	
	LCD_Write_Command(0x85);
	
	LCD_Write_string("61 Hz");
	
	
	LCD_Write_Command(0x90);
	LCD_Write_string("duty cycle: ");
	
	LCD_Write_Command(0x97);
	LCD_Write_string("%");
	
	
	LCD_Write_Command(0x98);
	LCD_Write_string("< time >");
}

void main_lines(void){

	uint8_t x,y;

	for(x=2;(x>=2)&(x<4);x++){   //SECOND LINE HORIZONTAL
		for(y=14;y<16;y++){
			LCD_Write_Command(0x80 | y);
			LCD_Write_Command(0x88 | x);
			LCD_Write_Character(0xFF);
			LCD_Write_Character(0xFF);
		}

	}

	for(y=0;y<16;y++){  //THIRD LINE VERTICAL
		LCD_Write_Command(0x80 | y);
		LCD_Write_Command(0x88 | 4);
		LCD_Write_Character(0xC0);
		LCD_Write_Character(0x00);
	}
	

	for(y=0;y<16;y++){     //FIFTH LINE VERTICAL
		LCD_Write_Command(0x80 | y);
		LCD_Write_Command(0x88 | 7);
		LCD_Write_Character(0x00);
		LCD_Write_Character(0x03);
	}
	
	for(x=6;(x>=6)&(x<8);x++){    //FORTH LINE HORIZONTAL
		for(y=14;y<16;y++){
			LCD_Write_Command(0x80 | y);
			LCD_Write_Command(0x88 | x);
			LCD_Write_Character(0xFF);
			LCD_Write_Character(0xFF);
		}

	}
}

void CLEAR_SCREEN(void){

	uint8_t x,y;

	for(x=0;x<32;x++){
		for(y=0;y<32;y++){
			LCD_Write_Command(0x80 | y);
			LCD_Write_Command(0x80 | x);
			LCD_Write_Character(0x00);
			LCD_Write_Character(0x00);
		}}

	}

	uint8_t decimal_shift(uint8_t read){
		
		uint8_t bin=0b00000000;
		
		switch(read){
			
			case 0:
			bin=0b00000000;
			break;
			
			case 1:
			bin=0b10000000;
			break;
			
			case 2:
			bin=0b11000000;
			break;
			
			case 3:
			bin=0b11100000;
			break;
			
			case 4:
			bin=0b11110000;
			break;
			
			case 5:
			bin=0b11111000;
			break;
			
			case 6:
			bin=0b11111100;
			break;
			
			case 7:
			bin=0b11111110;
			break;
			
			case 8:
			bin=0b11111111;
			break;
		}
		return bin;
	}

	uint8_t decimal_shift_back(uint8_t read8){
		
		uint8_t bin=0b00000000;
		
		switch(read8){
			
			case 0:
			bin=0b11111111;
			break;
			
			case 1:
			bin=0b01111111;
			break;
			
			case 2:
			bin=0b00111111;
			break;
			
			case 3:
			bin=0b00011111;
			break;
			
			case 4:
			bin=0b00001111;
			break;
			
			case 5:
			bin=0b00000111;
			break;
			
			case 6:
			bin=0b00000011;
			break;
			
			case 7:
			bin=0b00000001;
			break;
			
			case 8:
			bin=0b00000000;
			break;
		}
		return bin;
	}

	void LCD_first_line (uint16_t read4){
		
		if(read4>16)
		read4=16;
		
		uint8_t y;
		LCD_Write_Command(0x36);
		if(read2<17){
			for(y=0;y<16;y++){                                 //first LINE VERTICAL
				LCD_Write_Command(0x80 | y);
				LCD_Write_Command(0x88 | 0);
				if(read4>7){
					
					uint8_t d5 =read4-8;
					uint8_t d6 = decimal_shift_h(d5);
					LCD_Write_Character(0x00);
					LCD_Write_Character(0x00 | d6 );
					
				}
				else{
					uint8_t d7 = decimal_shift_h(read4);
					LCD_Write_Character(0x00 | d7);
					LCD_Write_Character(0x00);
				}
			}
			
			for(y=0;y<16;y++){                                //SECOND LINE VERTICAL
				LCD_Write_Command(0x80 | y);
				LCD_Write_Command(0x88 | 1);
				LCD_Write_Character(0x00);
				LCD_Write_Character(0x00);
			}
		}

		for(y=0;y<2;y++){      //FIRST LINE HORIZONTAL
			
			LCD_Write_Command(0x80 | y);
			LCD_Write_Command(0x88 | 0);
			if(read4>7){
				uint8_t d1 =read4-8;
				uint8_t d2 = decimal_shift(d1);
				LCD_Write_Character(0xFF);
				LCD_Write_Character(0x00 | d2 );
			}
			else{
				uint8_t d3 = decimal_shift(read4);
				LCD_Write_Character(0x00 | d3);
			}
		}
		
		//SECOND LINE HORIZONTAL
		for(y=14;y<16;y++){
			LCD_Write_Command(0x80 | y);
			LCD_Write_Command(0x88 | 0);
			if(read4>7){
				uint8_t d8 =read4-8;
				uint8_t d9 = decimal_shift_back(d8);
				LCD_Write_Character(0x00);
				LCD_Write_Character(0x00 | d9 );
			}
			else{
				uint8_t d10 = decimal_shift_back(read4);
				LCD_Write_Character(0x00 | d10);
				LCD_Write_Character(0xFF);
			}
		}
		
		if(read2<17){
			for(y=14;y<16;y++){
				LCD_Write_Command(0x80 | y);
				LCD_Write_Command(0x88 | 1);
				LCD_Write_Character(0xFF);
				LCD_Write_Character(0xFF);
			}
		}
		LCD_Write_Command(0x30);  //close graphical mode

	}

	void LCD_second_line (uint16_t read5){
		
		if(read5>16)
		read5=16;
		
		
		uint8_t y;
		LCD_Write_Command(0x36);
		if(read2 < 33){
			for(y=0;y<16;y++){                      //SECOND LINE VERTICAL
				LCD_Write_Command(0x80 | y);
				LCD_Write_Command(0x88 | 1);
				if(read5>7){
					
					uint8_t d5 =read5-8;
					uint8_t d6 = decimal_shift_h(d5);
					LCD_Write_Character(0x00);
					LCD_Write_Character(0x00 | d6 );
				}
				else{
					uint8_t d7 = decimal_shift_h(read5);
					LCD_Write_Character(0x00 | d7);
					LCD_Write_Character(0x00);
				}
			}
			

			for(y=0;y<16;y++){ //SECOND LINE VERTICAL
				LCD_Write_Command(0x80 | y);
				LCD_Write_Command(0x88 | 2);
				LCD_Write_Character(0x00);
				LCD_Write_Character(0x00);
				//LCD_Write_Character(0x00);
			}
		}
		
		for(y=0;y<2;y++){           //second line horizontal
			
			LCD_Write_Command(0x80 | y);
			LCD_Write_Command(0x88 | 1);
			if(read5>7){
				uint8_t d1 =read5-8;
				uint8_t d2 = decimal_shift(d1);
				LCD_Write_Character(0xFF);
				LCD_Write_Character(0x00 | d2 );
			}
			else{
				uint8_t d3 = decimal_shift(read5);
				LCD_Write_Character(0x00 | d3);
			}
		}
		
		for(y=14;y<16;y++){                 //bottom line horizontal
			LCD_Write_Command(0x80 | y);
			LCD_Write_Command(0x88 | 1);
			if(read5>7){
				uint8_t d8 =read5-8;
				uint8_t d9 = decimal_shift_back(d8);
				LCD_Write_Character(0x00);
				LCD_Write_Character(0x00 | d9 );
			}
			else{
				uint8_t d10 = decimal_shift_back(read5);
				LCD_Write_Character(0x00 | d10);
				LCD_Write_Character(0xFF);
			}
		}
		
		if(read2<33){                     //third bottom line
			for(y=14;y<16;y++){
				LCD_Write_Command(0x80 | y);
				LCD_Write_Command(0x88 | 2);
				LCD_Write_Character(0xFF);
				LCD_Write_Character(0xFF);
			}
		}
		
		LCD_Write_Command(0x30);
		//read=0;
	}

	void LCD_third_line(uint16_t read5){
		
		uint8_t y;
		LCD_Write_Command(0x36);
		if(read2 > 32){
			for(y=0;y<16;y++){                          //third LINE VERTICAL
				LCD_Write_Command(0x80 | y);
				LCD_Write_Command(0x88 | 2);
				if(read5>7){
					
					uint8_t d5 =read5-8;
					uint8_t d6 = decimal_shift_h(d5);
					LCD_Write_Character(0x00);
					LCD_Write_Character(0x00 | d6 );
					
				}
				else{
					uint8_t d7 = decimal_shift_h(read5);
					LCD_Write_Character(0x00 | d7);
					LCD_Write_Character(0x00);
				}
			}
			
			for(y=0;y<16;y++){                         //SECOND LINE VERTICAL
				LCD_Write_Command(0x80 | y);
				LCD_Write_Command(0x88 | 1);
				LCD_Write_Character(0x00);
				LCD_Write_Character(0x00);
				//LCD_Write_Character(0x00);
			}
			
		}

		if(read2 < 48){
			for(y=0;y<16;y++){                     //forth LINE VERTICAL
				LCD_Write_Command(0x80 | y);
				LCD_Write_Command(0x88 | 3);
				LCD_Write_Character(0x00);
				LCD_Write_Character(0x00);
				//LCD_Write_Character(0x00);
			}
			for(y=14;y<16;y++){
				LCD_Write_Command(0x80 | y);
				LCD_Write_Command(0x88 | 3);
				LCD_Write_Character(0xFF);
				LCD_Write_Character(0xFF);
			}
		}


		//third LINE HORIZONTAL
		
		for(y=0;y<2;y++){
			
			LCD_Write_Command(0x80 | y);
			LCD_Write_Command(0x88 | 2);
			if(read5>7){
				uint8_t d1 =read5-8;
				uint8_t d2 = decimal_shift(d1);
				LCD_Write_Character(0xFF);
				LCD_Write_Character(0x00 | d2 );
			}
			else{
				uint8_t d3 = decimal_shift(read5);
				LCD_Write_Character(0x00 | d3);
			}
		}
		
		for(y=14;y<16;y++){                   //bottom line
			LCD_Write_Command(0x80 | y);
			LCD_Write_Command(0x88 | 2);
			if(read5>7){
				uint8_t d8 =read5-8;
				uint8_t d9 = decimal_shift_back(d8);
				LCD_Write_Character(0x00);
				LCD_Write_Character(0x00 | d9 );
			}
			else{
				uint8_t d10 = decimal_shift_back(read5);
				LCD_Write_Character(0x00 | d10);
				LCD_Write_Character(0xFF);
			}
		}
		
		if(read2>32){                          //second line horizontal full
			for(y=0;y<2;y++){
				LCD_Write_Command(0x80 | y);
				LCD_Write_Command(0x88 | 1);
				LCD_Write_Character(0xFF);
				LCD_Write_Character(0xFF);
			}
		}
		
		LCD_Write_Command(0x30);
		//read=0;
		
	}

	void LCD_forth_line (uint16_t read5){
		
		if(read5>48)
		read5=16;
		
		
		uint8_t y;
		LCD_Write_Command(0x36);
		if(read2 > 48){
			for(y=0;y<16;y++){                   //forth LINE VERTICAL
				LCD_Write_Command(0x80 | y);
				LCD_Write_Command(0x88 | 3);
				if(read5>7){
					
					uint8_t d5 =read5-8;
					uint8_t d6 = decimal_shift_h(d5);
					LCD_Write_Character(0x00);
					LCD_Write_Character(0x00 | d6 );
					
				}
				else{
					uint8_t d7 = decimal_shift_h(read5);
					LCD_Write_Character(0x00 | d7);
					LCD_Write_Character(0x00);
				}
			}
			
			
			
		}
		
		for(y=0;y<2;y++){                //forth line horizontal
			
			LCD_Write_Command(0x80 | y);
			LCD_Write_Command(0x88 | 3);
			if(read5>7){
				uint8_t d1 =read5-8;
				uint8_t d2 = decimal_shift(d1);
				LCD_Write_Character(0xFF);
				LCD_Write_Character(0x00 | d2 );
			}
			else{
				uint8_t d3 = decimal_shift(read5);
				LCD_Write_Character(0x00 | d3);
			}
		}
		
		for(y=14;y<16;y++){                  //bottom line
			LCD_Write_Command(0x80 | y);
			LCD_Write_Command(0x88 | 3);
			if(read5>7){
				uint8_t d8 =read5-8;
				uint8_t d9 = decimal_shift_back(d8);
				LCD_Write_Character(0x00);
				LCD_Write_Character(0x00 | d9 );
			}
			else{
				uint8_t d10 = decimal_shift_back(read5);
				LCD_Write_Character(0x00 | d10);
				LCD_Write_Character(0xFF);
			}
		}
		
		if(read2>48){
			for(y=0;y<2;y++){
				LCD_Write_Command(0x80 | y);
				LCD_Write_Command(0x88 | 2);
				LCD_Write_Character(0xFF);
				LCD_Write_Character(0xFF);
			}
		}
		
		LCD_Write_Command(0x30);
		//read=0;
	}

	void LCD_fifth_line (uint16_t read4){
		
		if(read4>16)
		read4=16;
		
		uint8_t y;
		LCD_Write_Command(0x36);
		if(read2<17){
			for(y=0;y<16;y++){                                 //SECOND LINE VERTICAL
				LCD_Write_Command(0x80 | y);
				LCD_Write_Command(0x88 | 4);
				if(read4>7){
					
					uint8_t d5 =read4-8;
					uint8_t d6 = decimal_shift_h(d5);
					LCD_Write_Character(0x00);
					LCD_Write_Character(0x00 | d6 );
					//LCD_Write_Character(0x00);
				}
				else{
					uint8_t d7 = decimal_shift_h(read4);
					LCD_Write_Character(0x00 | d7);
					LCD_Write_Character(0x00);
				}
			}
			
			for(y=0;y<16;y++){                                //SECOND LINE VERTICAL
				LCD_Write_Command(0x80 | y);
				LCD_Write_Command(0x88 | 5);
				LCD_Write_Character(0x00);
				LCD_Write_Character(0x00);
				//LCD_Write_Character(0x00);
			}
		}
		

		//for(x=0;x<1;x++){                               //FIRST LINE HORIZONTAL
		
		for(y=0;y<2;y++){
			
			LCD_Write_Command(0x80 | y);
			LCD_Write_Command(0x88 | 4);
			if(read4>7){
				uint8_t d1 =read4-8;
				uint8_t d2 = decimal_shift(d1);
				LCD_Write_Character(0xFF);
				LCD_Write_Character(0x00 | d2 );
			}
			else{
				uint8_t d3 = decimal_shift(read4);
				LCD_Write_Character(0x00 | d3);
			}
		}
		
		//for(x=2;(x>=2)&(x<4);x++){   //SECOND LINE HORIZONTAL
		for(y=14;y<16;y++){
			LCD_Write_Command(0x80 | y);
			LCD_Write_Command(0x88 | 4);
			if(read4>7){
				uint8_t d8 =read4-8;
				uint8_t d9 = decimal_shift_back(d8);
				LCD_Write_Character(0x00);
				LCD_Write_Character(0x00 | d9 );
			}
			else{
				uint8_t d10 = decimal_shift_back(read4);
				LCD_Write_Character(0x00 | d10);
				LCD_Write_Character(0xFF);
			}
		}
		if(read2<17){
			for(y=14;y<16;y++){
				LCD_Write_Command(0x80 | y);
				LCD_Write_Command(0x88 | 5);
				LCD_Write_Character(0xFF);
				LCD_Write_Character(0xFF);
			}
		}
		LCD_Write_Command(0x30);

		//read=0;
	}

	void LCD_sixth_line (uint16_t read5){
		
		if(read5>16)
		read5=16;
		
		
		uint8_t y;
		LCD_Write_Command(0x36);
		if(read2 < 33){
			for(y=0;y<16;y++){ //SECOND LINE VERTICAL
				LCD_Write_Command(0x80 | y);
				LCD_Write_Command(0x88 | 5);
				if(read5>7){
					
					uint8_t d5 =read5-8;
					uint8_t d6 = decimal_shift_h(d5);
					LCD_Write_Character(0x00);
					LCD_Write_Character(0x00 | d6 );
					//LCD_Write_Character(0x00);
				}
				else{
					uint8_t d7 = decimal_shift_h(read5);
					LCD_Write_Character(0x00 | d7);
					LCD_Write_Character(0x00);
				}
			}
			
			//}
			
			
			for(y=0;y<16;y++){ //SECOND LINE VERTICAL
				LCD_Write_Command(0x80 | y);
				LCD_Write_Command(0x88 | 6);
				LCD_Write_Character(0x00);
				LCD_Write_Character(0x00);
				//LCD_Write_Character(0x00);
			}
			for(y=0;y<16;y++){ //SECOND LINE VERTICAL
				LCD_Write_Command(0x80 | y);
				LCD_Write_Command(0x88 | 4);
				LCD_Write_Character(0x00);
				LCD_Write_Character(0x00);
				//LCD_Write_Character(0x00);
			}
		}
		for(y=0;y<2;y++){
			
			LCD_Write_Command(0x80 | y);
			LCD_Write_Command(0x88 | 5);
			if(read5>7){
				uint8_t d1 =read5-8;
				uint8_t d2 = decimal_shift(d1);
				LCD_Write_Character(0xFF);
				LCD_Write_Character(0x00 | d2 );
			}
			else{
				uint8_t d3 = decimal_shift(read5);
				LCD_Write_Character(0x00 | d3);
			}
		}
		
		for(y=14;y<16;y++){
			LCD_Write_Command(0x80 | y);
			LCD_Write_Command(0x88 | 5);
			if(read5>7){
				uint8_t d8 =read5-8;
				uint8_t d9 = decimal_shift_back(d8);
				LCD_Write_Character(0x00);
				LCD_Write_Character(0x00 | d9 );
			}
			else{
				uint8_t d10 = decimal_shift_back(read5);
				LCD_Write_Character(0x00 | d10);
				LCD_Write_Character(0xFF);
			}
		}
		
		if(read2<33){
			for(y=14;y<16;y++){
				LCD_Write_Command(0x80 | y);
				LCD_Write_Command(0x88 | 6);
				LCD_Write_Character(0xFF);
				LCD_Write_Character(0xFF);
			}
		}
		
		LCD_Write_Command(0x30);
		//read=0;
	}

	void LCD_seventh_line(uint16_t read5){
		
		uint8_t y;
		LCD_Write_Command(0x36);
		if(read2 > 32){
			for(y=0;y<16;y++){ //SECOND LINE VERTICAL
				LCD_Write_Command(0x80 | y);
				LCD_Write_Command(0x88 | 6);
				if(read5>7){
					
					uint8_t d5 =read5-8;
					uint8_t d6 = decimal_shift_h(d5);
					LCD_Write_Character(0x00);
					LCD_Write_Character(0x00 | d6 );
					//LCD_Write_Character(0x00);
				}
				else{
					uint8_t d7 = decimal_shift_h(read5);
					LCD_Write_Character(0x00 | d7);
					LCD_Write_Character(0x00);
				}
			}
			
			for(y=0;y<16;y++){ //SECOND LINE VERTICAL
				LCD_Write_Command(0x80 | y);
				LCD_Write_Command(0x88 | 5);
				LCD_Write_Character(0x00);
				LCD_Write_Character(0x00);
				//LCD_Write_Character(0x00);
			}
			
		}

		if(read2 < 48){
			for(y=0;y<16;y++){ //SECOND LINE VERTICAL
				LCD_Write_Command(0x80 | y);
				LCD_Write_Command(0x88 | 7);
				LCD_Write_Character(0x00);
				LCD_Write_Character(0x00);
				//LCD_Write_Character(0x00);
			}
			for(y=14;y<16;y++){
				LCD_Write_Command(0x80 | y);
				LCD_Write_Command(0x88 | 7);
				LCD_Write_Character(0xFF);
				LCD_Write_Character(0xFF);
			}
		}


		
		//FIRST LINE HORIZONTAL
		
		for(y=0;y<2;y++){
			
			LCD_Write_Command(0x80 | y);
			LCD_Write_Command(0x88 | 6);
			if(read5>7){
				uint8_t d1 =read5-8;
				uint8_t d2 = decimal_shift(d1);
				LCD_Write_Character(0xFF);
				LCD_Write_Character(0x00 | d2 );
			}
			else{
				uint8_t d3 = decimal_shift(read5);
				LCD_Write_Character(0x00 | d3);
			}
		}
		
		for(y=14;y<16;y++){
			LCD_Write_Command(0x80 | y);
			LCD_Write_Command(0x88 | 6);
			if(read5>7){
				uint8_t d8 =read5-8;
				uint8_t d9 = decimal_shift_back(d8);
				LCD_Write_Character(0x00);
				LCD_Write_Character(0x00 | d9 );
			}
			else{
				uint8_t d10 = decimal_shift_back(read5);
				LCD_Write_Character(0x00 | d10);
				LCD_Write_Character(0xFF);
			}
		}
		
		if(read2>32){
			for(y=0;y<2;y++){
				LCD_Write_Command(0x80 | y);
				LCD_Write_Command(0x88 | 5);
				LCD_Write_Character(0xFF);
				LCD_Write_Character(0xFF);
			}
		}
		
		LCD_Write_Command(0x30);
		//read=0;
		
	}

	void LCD_eight_line (uint16_t read5){
		
		if(read5>48)
		read5=16;
		
		
		uint8_t y;
		LCD_Write_Command(0x36);
		if(read2 > 48){
			for(y=0;y<16;y++){ //SECOND LINE VERTICAL
				LCD_Write_Command(0x80 | y);
				LCD_Write_Command(0x88 | 7);
				if(read5>7){
					
					uint8_t d5 =read5-8;
					uint8_t d6 = decimal_shift_h(d5);
					LCD_Write_Character(0x00);
					LCD_Write_Character(0x00 | d6 );
					//LCD_Write_Character(0x00);
				}
				else{
					uint8_t d7 = decimal_shift_h(read5);
					LCD_Write_Character(0x00 | d7);
					LCD_Write_Character(0x00);
				}
			}
			
			//}
			
		}
		
		for(y=0;y<2;y++){
			
			LCD_Write_Command(0x80 | y);
			LCD_Write_Command(0x88 | 7);
			if(read5>7){
				uint8_t d1 =read5-8;
				uint8_t d2 = decimal_shift(d1);
				LCD_Write_Character(0xFF);
				LCD_Write_Character(0x00 | d2 );
			}
			else{
				uint8_t d3 = decimal_shift(read5);
				LCD_Write_Character(0x00 | d3);
			}
		}
		
		for(y=14;y<16;y++){
			LCD_Write_Command(0x80 | y);
			LCD_Write_Command(0x88 | 7);
			if(read5>7){
				uint8_t d8 =read5-8;
				uint8_t d9 = decimal_shift_back(d8);
				LCD_Write_Character(0x00);
				LCD_Write_Character(0x00 | d9 );
			}
			else{
				uint8_t d10 = decimal_shift_back(read5);
				LCD_Write_Character(0x00 | d10);
				LCD_Write_Character(0xFF);
			}
		}
		
		if(read2<49){
			for(y=14;y<16;y++){
				LCD_Write_Command(0x80 | y);
				LCD_Write_Command(0x88 | 7);
				LCD_Write_Character(0xFF);
				LCD_Write_Character(0xFF);
			}
		}
		
		if(read2>48){
			for(y=0;y<2;y++){
				LCD_Write_Command(0x80 | y);
				LCD_Write_Command(0x88 | 6);
				LCD_Write_Character(0xFF);
				LCD_Write_Character(0xFF);
			}
		}
		
		LCD_Write_Command(0x30);
		//read=0;
	}

	uint8_t decimal_shift_h(uint8_t read){
		
		uint8_t bin=0b00000000;
		
		switch(read){
			
			case 0:
			bin=0b11000000;
			break;
			
			case 1:
			bin=0b11000000;
			break;
			
			case 2:
			bin=0b01100000;
			break;
			
			case 3:
			bin=0b00110000;
			break;
			
			case 4:
			bin=0b00011000;
			break;
			
			case 5:
			bin=0b00001100;
			break;
			
			case 6:
			bin=0b00000110;
			break;
			
			case 7:
			bin=0b00000011;
			break;
			
			case 8:
			bin=0b00000011;
			break;
		}
		return bin;
	}

