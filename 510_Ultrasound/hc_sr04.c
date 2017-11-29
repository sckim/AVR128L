/*
 * Measure distance using HC SR04 sensor
 * S.C. Kim
 *
 * 2017.11.28
 */
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "uart.h"

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

#define LED_PORT                PORTB
#define LED_PIN                 PINB
#define LED_DDR                 DDRB

#define BUTTON_PORT             PORTD
#define BUTTON_PIN              PIND
#define BUTTON_DDR              DDRD
#define BUTTON                  PD2

static inline void initTimer1(void) {
	/* Clock Seclects bits
	 CS12	CS11	CS10	Mode Description
	 000: Stop Timer/Counter 1
	 001: No Prescaler (Timer Clock = System Clock)
	 010: divide clock by 8
	 011: divide clock by 64
	 100: divide clock by 256
	 101: divide clock by 1024
	 110: increment timer 1 on T1 Pin falling edge
	 111: increment timer 1 on T1 Pin rising edge
	 */
	 TCCR1B |= (1 << CS11) | (1 << CS10);
	 /* Clock speed: 16 MHz / 64,
	 each tick is 4 microseconds ~= 25 per ms  */
	/* No special output modes */
}

char str[80];

/* http://www.ermicro.com/blog/?p=325 */
static FILE uart_output = FDEV_SETUP_STREAM(UART_putchar, NULL, _FDEV_SETUP_WRITE);
//FILE uart_input = FDEV_SETUP_STREAM(NULL, UART_getchar, _FDEV_SETUP_READ);

int main(void) {
	uint16_t duration;
	double	distance;

	// -------- Inits --------- //

	InitUART(9600L);
	initTimer1();

	stdout = &uart_output;

	sbi(LED_DDR, PB5);			// Trigger
	cbi(BUTTON_DDR, BUTTON);	// Echo

	printf("\r\nGet Distance using HC_SR04\r\n");
	printf("---------------\r\n");

	// ------ Event loop ------ //
	while (1) {
		cbi(LED_PORT, PB5);
		_delay_us(100);
		sbi(LED_PORT, PB5);
		_delay_us(15);
		cbi(LED_PORT, PB5);

		//printf("\r\nloop_until_bit_is_set\r\n");
		loop_until_bit_is_set(BUTTON_PIN, BUTTON);

		TCNT1 = 0; /* reset counter */
		//printf("\r\nloop_until_bit_is_clear\r\n");
		loop_until_bit_is_clear(BUTTON_PIN, BUTTON);
		duration = TCNT1 << 2;

		// us / 58 = 1cm
		// 1cm = 58us
		// 1 cnt = 4us because 16MHz / 64 prescaler

		printf("Time: %d[usec]", duration );
		distance = (duration / 58.0);
		if (distance >= 400 || distance <= 2) {
			printf("\nOut of range\r\n");
		} else {
			printf(", Distance: %4.1f[cm]\n", distance);
		}

		_delay_ms(1000);

	} /* End event loop */
	return 0; /* This line is never reached */
}
