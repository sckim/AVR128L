/*
 * ADC on a LCD.c
 *
 *  Created on: 2016. 5. 5.
 *      Author: Soochan Kim
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include "lcd_lib.h"

#define strWelcome	"Welcome"
#define strWelcome1	"Microcontroller"

volatile char str[16];
float Index = 0;

void InitADC() {
	// For Aref=AVcc;
	ADMUX = (1 << REFS0);
	//Rrescalar div factor =128
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t ReadADC(uint8_t ch) {
	//Select ADC Channel ch must be 0-7
	 ADMUX |= (ch & 0x07);
	// Clear lower three bits and set them from chan
	//ADMUX = (ADMUX & 0xF8) | (ch & 7);

	//Start Single conversion
	ADCSRA |= (1 << ADSC);

	//Wait for conversion to complete
	while (!(ADCSRA & (1 << ADIF)))
		;

	//Clear ADIF by writing one to it
	//Note you may be wondering why we have write one to clear it
	//This is standard way of clearing bits in io as said in datasheets.
	//The code writes '1' but it result in setting bit to '0' !!!
	ADCSRA |= (1 << ADIF);

	return (ADC);
}

int main(void) {
	LCDinit();
	LCDcursorOn();
	LCDclr();

	InitADC();

	LCDstring((uint8_t*) strWelcome, strlen(strWelcome));

	while (1) {
		LCDGotoXY(0, 0);
		sprintf((char *) str, "Index = %4.2f", 5.0 * ReadADC(0) / 1023.0);
		LCDstring((uint8_t*) str, strlen((char *) str));

		LCDGotoXY(0, 1);
		sprintf((char *) str, "Index = %4.2f", 5.0 * ReadADC(1) / 1023.0);
		LCDstring((uint8_t*) str, strlen((char *) str));

		_delay_ms(100);
	}
}
