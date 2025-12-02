/*
 * gpio.c
 *
 *  Created on: 2019. 7. 2.
 *      Author: Soochan Kim
 */

#include <avr/interrupt.h>
#include <util/delay.h>
#include "pins.h"
#include "gpio.h"

const uint16_t PROGMEM port_to_mode_PGM[] = {
NOT_A_PORT,
NOT_A_PORT, (uint16_t) &DDRB, (uint16_t) &DDRC, (uint16_t) &DDRD, };

const uint16_t PROGMEM port_to_output_PGM[] = {
NOT_A_PORT,
NOT_A_PORT, (uint16_t) &PORTB, (uint16_t) &PORTC, (uint16_t) &PORTD, };

const uint16_t PROGMEM port_to_input_PGM[] = {
NOT_A_PORT,
NOT_A_PORT, (uint16_t) &PINB, (uint16_t) &PINC, (uint16_t) &PIND, };

const uint8_t PROGMEM digital_pin_to_port_PGM[] = {
PD, /* 0 */
PD,
PD,
PD,
PD,
PD,
PD,
PD,
PB, /* 8 */
PB,
PB,
PB,
PB,
PB,
PC, /* 14 */
PC,
PC,
PC,
PC,
PC, };

const uint8_t PROGMEM digital_pin_to_bit_mask_PGM[] = { _BV(0), /* 0, port D */
_BV(1), _BV(2), _BV(3), _BV(4), _BV(5), _BV(6), _BV(7), _BV(0), /* 8, port B */
_BV(1), _BV(2), _BV(3), _BV(4), _BV(5), _BV(0), /* 14, port C */
_BV(1), _BV(2), _BV(3), _BV(4), _BV(5), };

void pinMode(uint8_t pin, uint8_t mode) {
	uint8_t bit = digitalPinToBitMask(pin);
	uint8_t port = digitalPinToPort(pin);
	volatile uint8_t *reg, *out;

	if (port == NOT_A_PIN)
		return;

	// JWS: can I let the optimizer do this?
	reg = portModeRegister(port);
	out = portOutputRegister(port);

	if (mode == INPUT) {
		uint8_t oldSREG = SREG;
		cli();
		*reg &= ~bit;
		*out &= ~bit;
		SREG = oldSREG;
	} else if (mode == INPUT_PULLUP) {
		uint8_t oldSREG = SREG;
		cli();
		*reg &= ~bit;
		*out |= bit;
		SREG = oldSREG;
	} else {
		uint8_t oldSREG = SREG;
		cli();
		*reg |= bit;
		SREG = oldSREG;
	}
}

void digitalWrite(uint8_t pin, uint8_t val) {
//	uint8_t timer = digitalPinToTimer(pin);
	uint8_t bit = digitalPinToBitMask(pin);
	uint8_t port = digitalPinToPort(pin);
	volatile uint8_t *out;

	if (port == NOT_A_PIN)
		return;

	// If the pin that support PWM output, we need to turn it off
	// before doing a digital write.
//	if (timer != NOT_ON_TIMER)
//		turnOffPWM(timer);

	out = portOutputRegister(port);

	uint8_t oldSREG = SREG;
	cli();

	if (val == LOW) {
		*out &= ~bit;
	} else {
		*out |= bit;
	}

	SREG = oldSREG;
}

int digitalRead(uint8_t pin) {
//	uint8_t timer = digitalPinToTimer(pin);
	uint8_t bit = digitalPinToBitMask(pin);
	uint8_t port = digitalPinToPort(pin);

	if (port == NOT_A_PIN)
		return LOW;

	// If the pin that support PWM output, we need to turn it off
	// before getting a digital reading.
//	if (timer != NOT_ON_TIMER)
//		turnOffPWM(timer);

	if (*portInputRegister(port) & bit)
		return HIGH;
	return LOW;
}

void checkGPIO(void) {
	for (int i = 2; i <= 13; i++) {
		pinMode(i, OUTPUT);
		digitalWrite(i, HIGH);
		_delay_ms(100);
	}

	for (int i = 2; i <= 13; i++) {
		pinMode(i, OUTPUT);
		digitalWrite(i, LOW);
		_delay_ms(100);
	}
}

void shiftOut(uint8_t dataPin, uint8_t clockPin, uint8_t bitOrder, uint8_t val)
{
	uint8_t i;

	for (i = 0; i < 8; i++)  {
		if (bitOrder == LSBFIRST)
			digitalWrite(dataPin, !!(val & (1 << i)));
		else
			digitalWrite(dataPin, !!(val & (1 << (7 - i))));

		digitalWrite(clockPin, HIGH);
		digitalWrite(clockPin, LOW);
	}
}
