/*
 * textLCDLib.c
 *
 *  Created on: 2016. 5. 5.
 *      Author: Soochan Kim
 */
#define F_CPU	16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <string.h>
#include "lcd_lib.h"

#define strWelcome	"Welcome"
#define strWelcome1	"Microcontroller"

int main(void) {
	LCDinit();
	LCDcursorOn();
	LCDclr();

	// Add delay if LCDstring has a problem
	_delay_ms(1000);
	LCDstring((uint8_t*)strWelcome, strlen(strWelcome));
	LCDGotoXY(0, 1);
	LCDstring((uint8_t*)strWelcome1, strlen(strWelcome1));

	for (int i = 0; i < 5; i++) {
		LCDshiftLeft(1);
		_delay_ms(200);
	}

	for (int i = 0; i < 5; i++) {
		LCDblank();
		_delay_ms(200);
		LCDvisible();
		_delay_ms(200);
	}

	for (int i = 0; i < 5; i++) {
		LCDshiftRight(1);
		_delay_ms(200);
	}
}