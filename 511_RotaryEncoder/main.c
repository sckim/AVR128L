/*
 * Measure distance using HC SR04 sensor
 * S.C. Kim
 *
 * 2017.11.28
 */
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

#define PortOutput          PORTD
#define PortInput       	PIND
#define PortDirection       DDRD

#define PinA               	PD2
#define PinB			   	PD3

/* http://www.ermicro.com/blog/?p=325 */
static FILE uart_output = FDEV_SETUP_STREAM(UART_putchar, NULL, _FDEV_SETUP_WRITE);

char str[80];

int main(void) {
	int RotPosition = 0;
	int pinA_Last, pinA_Current;

	// -------- Inits --------- //
	InitUART(9600L);
	stdout = &uart_output;

	// set PD2 as input
	cbi(PortDirection, PinA);
	cbi(PortDirection, PinB);

	pinA_Last = (PortInput & PinA);
	//pinA_Last = bit_is_set(PinIn,PD2);

	// ------ Event loop ------ //
	while (1) {
		pinA_Current = (PortInput & PinA);

		// PinA status is changed ?
		if (pinA_Current != pinA_Last) {
			if ((PortInput & PinB) != pinA_Current) {
				RotPosition++;
				printf("clockwise\r\n");
			} else {
				RotPosition--;
				printf("counterclockwise\r\n");
			}
			printf("Encoder RotPosition: %d", RotPosition);
		}
		pinA_Last = pinA_Current;
	} /* End event loop */

	return 0; /* This line is never reached */
}
