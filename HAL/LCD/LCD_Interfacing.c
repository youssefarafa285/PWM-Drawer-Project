/*
 * LCD_Interfacing.c
 *
 * Created: 11/23/2023 6:15:19 PM
 * Author : YOUSSEF ARAFA
 */ 

#include "LCD_Private.h"

void reverse(char* str, int len)
{
	int i = 0, j = len - 1, temp;
	while (i < j) {
		temp = str[i];
		str[i] = str[j];
		str[j] = temp;
		i++;
		j--;
	}
}
int intToStr(int x, char str[], int d)
{
	int i = 0;
	while (x) {
		str[i++] = (x % 10) + '0';
		x = x / 10;
	}
	
	// If number of digits required is more, then
	// add 0s at the beginning
	while (i < d)
	str[i++] = '0';
	
	reverse(str, i);
	str[i] = '\0';
	return i;
}
void ftoa(float n, char* res, int afterpoint)
{
	// Extract integer part
	int ipart = (int)n;
	
	// Extract floating part
	float fpart = n - (float)ipart;
	
	// convert integer part to string
	int i = intToStr(ipart, res, 0);
	
	// check for display option after point
	if (afterpoint != 0) {
		res[i] = '.'; // add dot
		
		// Get the value of fraction part upto given no.
		// of points after dot. The third parameter
		// is needed to handle cases like 233.007
		fpart = fpart * pow(10, afterpoint);
		
		intToStr((int)fpart, res + i + 1, afterpoint);
	}
}

void LCD_Initialize(void)
{
	/* Define direction of pins*/
	DIO_SetPin_Direction(LCD_CNTRL_PRT, LCD_RS, LCD_OUT);
	DIO_SetPin_Direction(LCD_CNTRL_PRT, LCD_RW, LCD_OUT);
	DIO_SetPin_Direction(DIO_PORTD, LCD_EN, LCD_OUT);
	DIO_SetPin_Direction(DIO_PORTD, LCD_reset, LCD_OUT);
	DIO_SetPin_Direction(DIO_PORTD, LCD_pcb , LCD_OUT);
	
	DIO_SetPin_Direction(DIO_PORTC, LCD_D0, LCD_OUT);
	DIO_SetPin_Direction(DIO_PORTC, LCD_D1, LCD_OUT);
	DIO_SetPin_Direction(DIO_PORTC, LCD_D2, LCD_OUT);
	DIO_SetPin_Direction(DIO_PORTC, LCD_D3, LCD_OUT);
	DIO_SetPin_Direction(LCD_DATA_PRT, LCD_D4, LCD_OUT);
	DIO_SetPin_Direction(LCD_DATA_PRT, LCD_D5, LCD_OUT);
	DIO_SetPin_Direction(LCD_DATA_PRT, LCD_D6, LCD_OUT);
	DIO_SetPin_Direction(LCD_DATA_PRT, LCD_D7, LCD_OUT);
	
	DIO_SetPin_Value(DIO_PORTD, LCD_reset, LCD_LOW);
	_delay_ms(40);
	DIO_SetPin_Value(DIO_PORTD, LCD_reset, LCD_HIGH);
	
	DIO_SetPin_Value(DIO_PORTD, LCD_pcb , LCD_HIGH);
	
	/* Send commands*/
	//LCD_Write_Command(0x33);
	LCD_Write_Command(0x33);
	LCD_Write_Command(0x32);
	LCD_Write_Command(0x01);
	LCD_Write_Command(0x02);
	LCD_Write_Command(0x0C);
	LCD_Write_Command(0x06);
}
void LCD_Write_Command(uint8_t command)
{
	/* Register select will select command register*/
	DIO_SetPin_Value(LCD_CNTRL_PRT, LCD_RS, LCD_LOW);
	/* Write on LCD*/
	DIO_SetPin_Value(LCD_CNTRL_PRT, LCD_RW, LCD_LOW);
	/* Set enable by low*/
	DIO_SetPin_Value(DIO_PORTD, LCD_EN, LCD_LOW);
	/* Send High Nibble of command*/
	LCD = (command & 0xF0);
	PORTC = ((command & 0x0F)<<3);
	/* Send high to low pulse of enable*/
	DIO_SetPin_Value(DIO_PORTD, LCD_EN, LCD_HIGH);
	_delay_ms(1);
	DIO_SetPin_Value(DIO_PORTD, LCD_EN, LCD_LOW);
	// Send low nibble of command
	//LCD = ((command & 0x0F) << 4);
	/* Send high to low pulse of enable*/
	//DIO_SetPin_Value(LCD_CNTRL_PRT, LCD_EN, LCD_HIGH);
	//_delay_ms(1);
	//DIO_SetPin_Value(LCD_CNTRL_PRT, LCD_EN, LCD_LOW);
	//_delay_ms(5);
}
void LCD_Write_Character(uint8_t character)
{
	/* Register select will select command register*/
	DIO_SetPin_Value(LCD_CNTRL_PRT, LCD_RS, LCD_HIGH);
	/* Write on LCD*/
	DIO_SetPin_Value(LCD_CNTRL_PRT, LCD_RW, LCD_LOW);
	/* Set enable by low*/
	DIO_SetPin_Value(DIO_PORTD, LCD_EN, LCD_LOW);
	/* Send High Nibble of character*/
	LCD = (character & 0xF0);
	PORTC = ((character & 0x0F)<<3);
	/* Send high to low pulse of enable*/
	DIO_SetPin_Value(DIO_PORTD, LCD_EN, LCD_HIGH);
	_delay_ms(1);
	DIO_SetPin_Value(DIO_PORTD, LCD_EN, LCD_LOW);
	/* Send low nibble of character*/
	//LCD = ((character & 0x0F) << 4);
	/* Send high to low pulse of enable*/
	//DIO_SetPin_Value(LCD_CNTRL_PRT, LCD_EN, LCD_HIGH);
	//_delay_ms(1);
	//DIO_SetPin_Value(LCD_CNTRL_PRT, LCD_EN, LCD_LOW);
	//_delay_ms(5);
}
void LCD_Write_string(uint8_t* str)
{
	while (*str != '\0')
	{
		LCD_Write_Character(*str);
		_delay_ms(10);
		str++;
	}
}
void LCD_Write_Number(uint32_t number)
{
	uint8_t num[10];
	ltoa(number, (char*)num, 10);
	LCD_Write_string(num);
}
void LCD_Write_Float(fint32_t Fnumber)
{
	uint8_t Fnum[10];
	ftoa(Fnumber, (char*)Fnum, 3);
	LCD_Write_string(Fnum);
}
void LCD_Location(uint8_t row, uint8_t column)
{
	uint8_t Loc_Row0 = 0x80;
	uint8_t Loc_Row1 = 0xC0;
	switch(row)
	{
		case 0:
		Loc_Row0 += column;
		LCD_Write_Command(Loc_Row0);
		break;
		case 1:
		Loc_Row1 += column;
		LCD_Write_Command(Loc_Row1);
		break;
		default:
		Loc_Row0 += column;
		LCD_Write_Command(Loc_Row0);
		break;
	}
}
void LCD_ClearScreen(void)
{
	LCD_Write_Command(0x01);
}
