/*
 * ADC_on_LCD_OCR.c
 *
 *  Created on: 2016. 5. 5.
 *      Author: Soochan Kim
 */

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>
#include <string.h>
#include <avr/interrupt.h>
#include "lcd_lib.h"

#define strWelcome	"Welcome"
#define strWelcome1	"Microcontroller"

#define cDelay 144

volatile char str[16];
float Index = 0;

volatile int sec = 0;
volatile int msec = 0;

uint16_t ReadADC(uint8_t ch);

//ISR (TIMER0_OVF_vect)
SIGNAL( TIMER0_COMP_vect) {
	msec++;
	if (msec == 10) {
		msec = 0;
		sprintf((char *) str, "Index1 = %4.2f", 5.0 * ReadADC(0) / 1023.0);
		LCDGotoXY(0, 1);
		LCDstring((uint8_t*) str, strlen((char *) str));
	}
//   TCNT0 = 0xFF-cDelay+1;    //초기값
}

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

void Timer0Init(void) {
	//TIMSK |= (1<<TOIE0);    // Timer0 오버플로 인터럽트 에이블
	TIMSK |= (1 << OCIE0);    // Output compare match interrupter

	// Normal, 1/1024 for 프리스케일
	TCCR0 |= (1 << CS02);
	TCCR0 |= (1 << CS01);
	TCCR0 |= (1 << CS00);

	TCCR0 |= (1 << WGM01);

	OCR0 = cDelay;    // 10msec
}
int main(void) {
	LCDinit();
	LCDcursorOn();
	LCDclr();

	InitADC();

	cli();
	Timer0Init();
	sei();
	//SRGE  = 0x80;

	LCDstring((uint8_t*) strWelcome, strlen(strWelcome));
	while (1) {
	}
}
