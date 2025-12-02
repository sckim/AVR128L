// this code sets up counter1 A output at 25% and B output at 75%
// using ICR1 as top (16bit), Fast PWM.

#include <avr/io.h>
#include <util/delay.h>

#define Normal 	0
#define PPWM8	1
#define PPWM9	2
#define PPWM10	3
#define CTC		4
#define FPWM8	5
#define FPWM9	6
#define FPWM10	7
#define FPWM_ICR1	14
#define FPWM_OCR1A	15

#define Normal 		0
#define Toggle		1
#define NonInvert	2
#define Invert		3

void Timer1Mode(unsigned char mode) {
	// WGM01 WMG00
	// 00: Normal
	// 01: PWM, Phase Correct
	// 10: CTC
	// 11: Fast PWM

	switch (mode) {
		case Normal:
		TCCR1B &= ~(1 << WGM13);
		TCCR1B &= ~(1 << WGM12);
		TCCR1A &= ~(1 << WGM11);
		TCCR1A &= ~(1 << WGM10);
		break;
		case PPWM8:
		TCCR1B &= ~(1 << WGM13);
		TCCR1B &= ~(1 << WGM12);
		TCCR1A &= ~(1 << WGM11);
		TCCR1A |= (1 << WGM10);
		break;
		case PPWM9:
		TCCR1B &= ~(1 << WGM13);
		TCCR1B &= ~(1 << WGM12);
		TCCR1A |= (1 << WGM11);
		TCCR1A &= ~(1 << WGM10);
		break;
		case PPWM10:
		TCCR1B &= ~(1 << WGM13);
		TCCR1B &= ~(1 << WGM12);
		TCCR1A |= (1 << WGM11);
		TCCR1A |= (1 << WGM10);
		break;
		case CTC:
		TCCR1B &= ~(1 << WGM13);
		TCCR1B |= (1 << WGM12);
		TCCR1A &= ~(1 << WGM11);
		TCCR1A &= ~(1 << WGM10);
		break;
		case FPWM8:
		TCCR1B &= ~(1 << WGM13);
		TCCR1B |= (1 << WGM12);
		TCCR1A &= ~(1 << WGM11);
		TCCR1A |= (1 << WGM10);
		break;
		case FPWM9:
		TCCR1B &= ~(1 << WGM13);
		TCCR1B |= (1 << WGM12);
		TCCR1A |= (1 << WGM11);
		TCCR1A &= ~(1 << WGM10);
		break;
		case FPWM10:
		TCCR1B &= ~(1 << WGM13);
		TCCR1B |= (1 << WGM12);
		TCCR1A |= (1 << WGM11);
		TCCR1A |= (1 << WGM10);
		break;
		case FPWM_ICR1:
		TCCR1B |= (1 << WGM13);
		TCCR1B |= (1 << WGM12);
		TCCR1A |= (1 << WGM11);
		TCCR1A &= ~(1 << WGM10);
		break;
		case FPWM_OCR1A:
		TCCR1B |= (1 << WGM13);
		TCCR1B |= (1 << WGM12);
		TCCR1A |= (1 << WGM11);
		TCCR1A |= (1 << WGM10);
		break;
	}
}

void Timer1OutputA(unsigned char mode) {
	//OC1A output
	DDRB |= (1 << PB1);

	// COM01 COM00
	// 00: Normal
	// 01: Toggle OC0 on compare match
	// 10: Clear OC0 on compare match
	// 11: Set OC0 on compare match

	switch (mode) {
		case Normal:
		TCCR1A &= ~(1 << COM1A1);
		TCCR1A &= ~(1 << COM1A0);
		break;
		case Toggle:
		TCCR1A &= ~(1 << COM1A1);
		TCCR1A |= (1 << COM1A0);
		break;
		case NonInvert:
		TCCR1A |= (1 << COM1A1);
		TCCR1A &= ~(1 << COM1A0);
		break;
		case Invert:
		TCCR1A |= (1 << COM1A1);
		TCCR1A |= (1 << COM1A0);
		break;
	}
}

void Timer1OutputB(unsigned char mode) {
	//OC1B output
	DDRB |= (1 << PB2);

	// COM01 COM00
	// 00: Normal
	// 01: Toggle OC0 on compare match
	// 10: Clear OC0 on compare match
	// 11: Set OC0 on compare match

	switch (mode) {
		case Normal:
		TCCR1A &= ~(1 << COM1B1);
		TCCR1A &= ~(1 << COM1B0);
		break;
		case Toggle:
		TCCR1A &= ~(1 << COM1B1);
		TCCR1A |= (1 << COM1B0);
		break;
		case NonInvert:
		TCCR1A |= (1 << COM1B1);
		TCCR1A &= ~(1 << COM1B0);
		break;
		case Invert:
		TCCR1A |= (1 << COM1B1);
		TCCR1A |= (1 << COM1B0);
		break;
	}
}

void Timer1Prescaler(unsigned int scale) {
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
		TCCR1B &= ~(1 << CS12);
		TCCR1B &= ~(1 << CS11);
		TCCR1B &= ~(1 << CS10);
		break;
		case 1:
		TCCR1B &= ~(1 << CS12);
		TCCR1B &= ~(1 << CS11);
		TCCR1B |= (1 << CS10);
		break;
		case 8:
		TCCR1B &= ~(1 << CS12);
		TCCR1B |= (1 << CS11);
		TCCR1B &= ~(1 << CS10);
		break;
		case 64:
		TCCR1B &= ~(1 << CS12);
		TCCR1B |= (1 << CS11);
		TCCR1B |= (1 << CS10);
		break;
		case 256:
		TCCR1B |= (1 << CS12);
		TCCR1B &= ~(1 << CS11);
		TCCR1B &= ~(1 << CS10);
		break;
		case 1024:
		TCCR1B |= (1 << CS12);
		TCCR1B &= ~(1 << CS11);
		TCCR1B |= (1 << CS10);
		break;
		default:
		TCCR1B &= ~(1 << CS12);
		TCCR1B &= ~(1 << CS11);
		TCCR1B |= (1 << CS10);
	}
}

int main(void) {
	int deg = 125;  // 0.5msec, duty ratio = 5%

	ICR1 = 2500;
	// set TOP to 16bit

	OCR1A = deg;
	OCR1B = deg;

	// set Fast PWM mode using ICR1 as TOP
	Timer1Mode(FPWM_ICR1);
	Timer1Prescaler(64);	 // 16MHz/64 => 1 step = 4us

	// set none-inverting mode
	Timer1OutputA(NonInvert);
	Timer1OutputB(NonInvert);

	int inc=1;
	while (1)
	{
		deg += inc;
		OCR1A = deg;
		OCR1B = deg;  // same direction
		//OCR1B = 625-deg+125; // opposite direction

		if( deg > 625 )  // 2.5msec
		inc = -1;
		if( deg < 125 )  // 0.5msec
		inc = +1;

		_delay_ms(5);
	}
}