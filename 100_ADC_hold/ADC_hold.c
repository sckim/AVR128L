/*
 * ADC_hold.c
 *
 *  Created on: 2016. 5. 25.
 *      Author: Soochan Kim
 */
#include <avr/io.h>
#include <util/delay.h>

void InitADC() {
	// For Aref=AVcc;
	ADMUX = (1 << REFS0);
	//Rrescalar div factor =128
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t ReadADC(uint8_t ch) {
	//Select ADC Channel ch must be 0-7
	ADMUX |= (ch & 0x07);

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
	int temp;

	DDRB = 0xFF;

	PORTB = 0;

	InitADC();

	while (1) {
		PORTB = 0x00;
		temp = ReadADC(0);

		temp /= 100;
		temp = (0xffff << temp);

		_delay_ms(100);
		PORTB = 0xFF;
		_delay_ms(100);
	}
}

