/*
 * Timer0.h
 *
 *  Created on: 2019. 7. 23.
 *      Author: Soochan Kim
 */

#ifndef TIMER0_H_
#define TIMER0_H_

#include <avr/interrupt.h>

#define Normal 	0
#define PWM		1
#define CTC		2
#define FPWM	3

#define Normal 		0
#define Toggle		1
#define NonInvert	2
#define Invert		3

void Timer0OutputMode(unsigned char mode) {
	// COM01 COM00
	// 00: Normal
	// 01: Toggle OC0 on compare match
	// 10: Clear OC0 on compare match
	// 11: Set OC0 on compare match

	switch (mode) {
	case Normal:
		TCCR0A &= ~(1 << COM0A1);
		TCCR0A &= ~(1 << COM0A0);
		break;
	case Toggle:
		TCCR0A &= ~(1 << COM0A1);
		TCCR0A |= (1 << COM0A0);
		break;
	case NonInvert:
		TCCR0A |= (1 << COM0A1);
		TCCR0A &= ~(1 << COM0A0);
		break;
	case Invert:
		TCCR0A |= (1 << COM0A1);
		TCCR0A |= (1 << COM0A0);
		break;
	}
}

void Timer0Mode(unsigned char mode) {
	// WGM01 WMG00
	// 00: Normal
	// 01: PWM, Phase Correct
	// 10: CTC
	// 11: Fast PWM

	switch (mode) {
	case Normal:
		TCCR0A &= ~(1 << WGM01);
		TCCR0A &= ~(1 << WGM00);
		break;
	case PWM:
		TCCR0A &= ~(1 << WGM01);
		TCCR0A |= (1 << WGM00);
		break;
	case CTC:
		TCCR0A |= (1 << WGM01);
		TCCR0A &= ~(1 << WGM00);
		break;
	case FPWM:
		TCCR0A |= (1 << WGM01);
		TCCR0A |= (1 << WGM00);
		break;
	}
}

void Timer0Prescaler(unsigned int scale) {
	// set prescaler to 8 and starts PWM
	// CS02 CS01 CS00
	// 000: No clock source
	// 001: No prescaling
	// 010: clk_IO/8
	// 011: clk_IO/64
	// 100: clk_IO/256
	// 101: clk_IO/1024
	switch (scale) {
	case 0:
		TCCR0B &= ~(1 << CS02);
		TCCR0B &= ~(1 << CS01);
		TCCR0B &= ~(1 << CS00);
		break;
	case 8:
		TCCR0B &= ~(1 << CS02);
		TCCR0B |= (1 << CS01);
		TCCR0B &= ~(1 << CS00);
		break;
	case 64:
		TCCR0B &= ~(1 << CS02);
		TCCR0B |= (1 << CS01);
		TCCR0B |= (1 << CS00);
		break;
	case 256:
		TCCR0B |= (1 << CS02);
		TCCR0B &= ~(1 << CS01);
		TCCR0B &= ~(1 << CS00);
		break;
	case 1024:
		TCCR0B |= (1 << CS02);
		TCCR0B &= ~(1 << CS01);
		TCCR0B |= (1 << CS00);
		break;
	default:
		TCCR0B &= ~(1 << CS02);
		TCCR0B &= ~(1 << CS01);
		TCCR0B |= (1 << CS00);
	}
}

#endif /* TIMER0_H_ */
