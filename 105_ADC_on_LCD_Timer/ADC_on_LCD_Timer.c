/*
 * ADC_on_LCD_Timer.c
 *
 *  Created on: 2016. 5. 5.
 *      Author: Soochan Kim
 */

#include <avr/io.h>
#include <string.h>
#include <stdio.h>
#include <avr/interrupt.h>

#include "lcd_lib.h"

// CLK: 14.7456MHz / 1024 = 14,400
// 144 = 0.01sec
// 72 = 0.005sec
#define TimerValue 144
#define cMaxChannel	4

typedef unsigned char Byte;

volatile char str[16];
volatile int adcValues[cMaxChannel];
volatile int cnt = 0;
volatile unsigned int bUpdated = 0;
volatile int cur_ch = 0;

void InitADC() {
	// For Aref=AVcc;
	ADMUX = (1 << REFS0);
	//Rrescalar div factor =128
	ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);
}

uint16_t ReadADC(uint8_t ch) {

	// Clear lower three bits and set them from chan
	ADMUX = (ADMUX & 0xF8) | (ch & 7);

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

SIGNAL(SIG_OVERFLOW0) {
	// prevent generating interrupter in this loop.
	cli();

	TCNT0 = 0x100 - TimerValue; //3. 초기값
	cnt++;
	if (cnt >= 100) {
		for (int i = 0; i < cMaxChannel; i++)
			adcValues[i] = ReadADC(i);
		bUpdated = 1;

		cnt = 0;
	}
	sei();
}

void Timer0_init(void) {
	//TIMSK=0x01;  //1. Timer0 오버플로 인터럽트 에이블 (TOIE0)
	TIMSK |= (1 << TOIE0);

	// 2. Normal, 1/1024 for 프리스케일
	TCCR0 = (1 << CS02) | (1 << CS01) | (1 << CS00);
	//TCCR0 = _BV(CS02) | _BV(CS01) | _BV(CS00);

	// 3. Set counter
	// 14.7456MHz / 1024 = 14,400
	// 144 = 0.01sec
	TCNT0 = 0x100 - TimerValue;
}

int main(void) {
	Byte SEG[10] =
			{ 0XC0, 0XF9, 0XA4, 0XB0, 0X99, 0X92, 0X82, 0XD8, 0X80, 0X90 };
	volatile unsigned char Index = 0;

	LCDinit();
	LCDcursorOn();
	LCDclr();

	InitADC();
	Timer0_init();

	DDRD = 0xFF;
	PORTD = SEG[Index];

	sei();
	while (1) {
		if (bUpdated) {
			bUpdated = 0;
			LCDGotoXY(0, 0);
			sprintf((char *)str, "0]=%1.2f,1]=%1.2f", adcValues[0] * 5.0 / 1024,
					adcValues[1] * 5.0 / 1024);
			LCDstring((uint8_t*) str, strlen((char *) str));

			LCDGotoXY(0, 1);
			sprintf((char *)str, "2]=%1.2f,3]=%1.2f", adcValues[2] * 5.0 / 1024,
					adcValues[3] * 5.0 / 1024);
			LCDstring((uint8_t*) str, strlen((char *) str));

			Index = (adcValues[0] * 5.0 / 1024) + 0.5;
			PORTD = ~SEG[Index];
			//PORTD = ~SEG[Index++];
		}
	}

}
